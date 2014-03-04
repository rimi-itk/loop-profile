<?php

/**
 * Class DITAParser
 *
 * For passing a DITA folder.
 */
class DITAParser implements iParser {
  /**
   * Rename a DOMElement
   *
   * @param DOMElement $oldTag
   * @param $newTagName
   * @return DOMElement
   */
  private function renameTag( DOMElement $oldTag, $newTagName ) {
    $document = $oldTag->ownerDocument;

    $newTag = $document->createElement($newTagName);
    $oldTag->parentNode->replaceChild($newTag, $oldTag);

    foreach ($oldTag->attributes as $attribute) {
      $newTag->setAttribute($attribute->name, $attribute->value);
    }
    foreach (iterator_to_array($oldTag->childNodes) as $child) {
      $newTag->appendChild($oldTag->removeChild($child));
    }
    return $newTag;
  }

  /**
   * Replaces danish characters
   *
   * @param $text
   * @return mixed
   */
  private function danishChars($text) {
    $text = preg_replace('/å/', '%86', $text);
    $text = preg_replace('/Å/', '%87', $text);
    $text = preg_replace('/æ/', '%91', $text);
    $text = preg_replace('/Æ/', '%92', $text);
    $text = preg_replace('/ø/', '%9B', $text);
    $text = preg_replace('/Ø/', '%9C', $text);
    return $text;
  }

  /**
   * Collapses ../ in paths
   *
   * @param $path
   * @return string
   */
  private function collapsePath($path) {
    $pathArray = array();

    // Split $path at /
    $split = preg_split('/\//', $path);

    foreach ($split as $part) {
      if ($part == '..') {
        array_pop($pathArray);
      } else {
        array_push($pathArray, $part);
      }
    }

    $resultPath = '';
    $i = 0;
    // Assemble to string
    foreach ($pathArray as $part) {
      $i++;


    }

    return $path;
  }

  /**
   * Traverses a DITA node.
   * If leaf: Processes the referred reference.
   *          Inserts conrefs
   *          Replaces xrefs
   *          Inserts images in Drupal and changes image paths
   * If tree: Adds children to tree (after traversing each)
   *
   * @param $node
   * @param $pathToDirectory
   * @param $objectReferences
   * @param $xrefReferences
   * @return Leaf|null|Tree
   */
  private function traverseNode($node, $pathToDirectory, &$objectReferences, &$xrefReferences) {
    $nodeType = $node->getName();

    if ($nodeType == 'topicref') {
      $href = $this->danishChars($node['href']);

      $body = simplexml_load_file($pathToDirectory . '/' . $href)->body;
      $domnode = dom_import_simplexml($body);
      $dom = new DOMDocument();
      $domnode = $dom->importNode($domnode, true);
      $dom->appendChild($domnode);

      $xpath = new DOMXPath($dom);

      // Replace all ph with the referenced
      foreach ($xpath->query('//ph') as $ph) {
        $conref = explode('#', $ph->getAttribute('conref'));

        $file = $conref[0];

        $id = explode('/', $conref[1]);
        $id = $id[count($id) - 1];

        $varXML = simplexml_load_file($pathToDirectory . '/' . dirname($href) . '/' . $file);
        $phText = $varXML->xpath('//ph[@id="' . $id . '"]');

        $phText = $dom->createTextNode($phText[0]);

        $ph->parentNode->replaceChild($phText, $ph);
      }

      // Replace image paths
      foreach ($xpath->query('//image') as $image) {
        $ref = $pathToDirectory . '/' . dirname($href) . '/' . $this->danishChars($image->getAttribute('href'));

        // Save file
        $fileName = basename($image->getAttribute('href'));
        $fileContent = file_get_contents($ref);
        $file = file_save_data($fileContent, 'public://' . $fileName, FILE_EXISTS_RENAME);
        $filePath = file_create_url($file->uri);

        $image->removeAttribute('href');
        $image->setAttribute('src', $filePath);
        $this->renameTag($image, 'img');
      }

      foreach ($xpath->query('//xref') as $xref) {
        $xhref = dirname($href) . '/' . $this->danishChars($xref->getAttribute('href'));
        $nextIndex = count($xrefReferences);

        $xhref = explode('#', $xhref);
        $xrefReferences[$this->collapsePath($xhref[0])] = $nextIndex;

        $xref->setAttribute('href', $nextIndex);
        $this->renameTag($xref, 'a');
      }

      $body = $dom->saveHTML();

      $body = preg_replace('/<body>/', '', $body);
      $body = preg_replace('/<\/body>/', '', $body);

      $leaf = new Leaf($node['navtitle'], $body);

      $objectReferences[$href] = $leaf;

      return $leaf;
    } else if ($nodeType == 'topichead') {
      $children = array();
      foreach ($node->children() as $child) {
        $children[] = $this->traverseNode($child, $pathToDirectory, $objectReferences, $xrefReferences);
      }

      $tree = new Tree($node['navtitle'], $children);
      return $tree;
    }
    return null;
  }

  private function replaceReferences($objectReferences, $xrefReferences, &$indexReferences) {
    foreach ($objectReferences as $ref=>$obj) {
      $id = $xrefReferences[$ref];
      $indexReferences[$id] = $obj;
    }
  }

  /**
   * Processes a DITA folder
   *
   * @param $pathToDirectory
   * @throws Exception
   *
   * @returns Index
   *  The index root node
   */
  public function process($pathToDirectory) {
    $xml = simplexml_load_file($pathToDirectory . '/' . 'Ditamap.ditamap');

    $children = array();
    $objectReferences = array();
    $xrefReferences = array();
    $indexReferences = array();

    foreach ($xml->children() as $child) {
      $nodeType = $child->getName();

      if ($nodeType == 'topichead') {
        $children[] = $this->traverseNode($child, $pathToDirectory, $objectReferences, $xrefReferences);
      }
    }

    watchdog('xrefRefs: ', print_r($xrefReferences, 1));
    watchdog('objRefs: ', print_r($objectReferences, 1));

    //$this->replaceReferences($objectReferences, $xrefReferences, $indexReferences);

    //watchdog('refs: ', print_r($indexReferences, 1));

    $index = new LoopIndex($children, $indexReferences);

    return $index;
  }

  /**
   * Identify if this is a DITA folder
   *
   * @param $pathToDirectory
   * @return bool
   */
  public function identifyFormat($pathToDirectory) {
    $entries = scandir($pathToDirectory);
    foreach ($entries as $entry) {
      if ($entry == 'Ditamap.ditamap') {
        return true;
      }
    }
    return false;
  }
}





// Adds reference to $references
/*foreach ($xpath->query('//xref') as $xref) {
  $xhref = $pathToDirectory . '/' . dirname($href) . '/' . $this->danishChars(basename($xref->getAttribute('href')));
  $id = count($references);
  $references[$id] = $xhref;
}*/
/*
// Replace xrefs
foreach ($xpath->query('//xref') as $xhref) {
  $refToXref = $pathToDirectory . '/' . dirname($href) . '/' . basename($xhref->getAttribute('href'));
  $refToXrefSplit = explode('#', $this->danishChars($refToXref));
  $refToXref = $refToXrefSplit[0];
  $xhref->setAttribute('href', $refToXref);
  $xhref = $this->renameTag($xhref, 'a');
}
*/
