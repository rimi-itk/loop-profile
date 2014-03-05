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
   * Removes all attributes from element.
   *
   * @param DOMElement $element
   */
  private function removeAttributes(DOMElement $element) {
    $attributes = $element->attributes;
    while ($attributes->length) {
      $element->removeAttribute($attributes->item(0)->name);
    }
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
    $arrayMaxIndex = count($pathArray);
    // Assemble to string
    foreach ($pathArray as $part) {
      $i++;

      $resultPath = $resultPath . $part;

      if ($i < $arrayMaxIndex) {
        $resultPath = $resultPath . '/';
      }
    }

    return $resultPath;
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
   * @param $indexNodeID
   * @param $objectReferences
   * @param $xrefReferences
   * @return Leaf|null|Tree
   */
  private function traverseNode($node, $pathToDirectory, $indexNodeID, &$objectReferences, &$xrefReferences) {
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
        // Split conref into file path and variable name
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

        $dir = 'public://external_data/' . $indexNodeID;
        file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
        $file = file_save_data($fileContent, $dir . '/' . $fileName, FILE_EXISTS_RENAME);
        $filePath = file_create_url($file->uri);

        $image->removeAttribute('href');
        $image->setAttribute('src', $filePath);
        $this->renameTag($image, 'img');
      }

      // Replace references
      foreach ($xpath->query('//xref') as $xref) {
        $scope = $xref->getAttribute('scope');

        if ($scope != 'external') {
          $xhref = dirname($href) . '/' . $this->danishChars($xref->getAttribute('href'));
          $nextIndex = count($xrefReferences);

          $xhref = explode('#', $xhref);
          $xrefReferences[$this->collapsePath($xhref[0])] = $nextIndex;

          $xref->setAttribute('href', $nextIndex);
        } else {
          $xref->setAttribute('target',  '_blank');
        }

        $this->renameTag($xref, 'a');
      }

      // Handle tables.
      // Remove colspec nodes.
      foreach ($xpath->query('//table//colspec') as $tableColspec) {
        $tableColspec->parentNode->removeChild($tableColspec);
      }
      // Move content out of tgroup to table.
      foreach ($xpath->query('//table//tgroup') as $tableTgroup) {
        foreach($tableTgroup->childNodes as $child) {
          $tableTgroup->parentNode->appendChild($child->cloneNode(true));
        }
        $tableTgroup->parentNode->removeChild($tableTgroup);
      }
      // Rename title to caption.
      foreach ($xpath->query('//table//title') as $tableTitle) {
        $this->renameTag($tableTitle, 'caption');
      }
      // Rename row to tr.
      foreach ($xpath->query('//table//row') as $tableRow) {
        $this->renameTag($tableRow, 'tr');
      }
      // Rename tbody//entry to td.
      foreach ($xpath->query('//table//tbody//entry') as $tableEntry) {
        $this->renameTag($tableEntry, 'td');
      }
      // Rename thead//entry to th.
      foreach ($xpath->query('//table//thead//entry') as $tableEntry) {
        $this->renameTag($tableEntry, 'th');
      }
      // Remove all attributes from table elements
      foreach ($xpath->query('//*[self::table or self::thead or self::tbody or self::tr or self::td or self::th]') as $child) {
        $this->removeAttributes($child);
      }

      // Wrap all table elements in a div with the class table-wrapper.
      foreach($xpath->query('//table') as $table) {
        $div = $dom->createElement('div');
        $div->setAttribute('class', 'table-wrapper');
        $div->appendChild($table->cloneNode(true));
        $table->parentNode->replaceChild($div, $table);
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
        $children[] = $this->traverseNode($child, $pathToDirectory, $indexNodeID, $objectReferences, $xrefReferences);
      }

      $tree = new Tree($node['navtitle'], $children);
      return $tree;
    }
    return null;
  }

  /**
   * Merges the arrays $objectReferences and $xrefReferences into a new array,
   * that from referenceIndex => Leaf object.
   *
   * @param $objectReferences
   * @param $xrefReferences
   *
   * @return array
   */
  private function replaceReferences($objectReferences, $xrefReferences) {
    $indexReferences = array();

    foreach ($xrefReferences as $ref=>$index) {
      $object = $objectReferences[$ref];
      $indexReferences[$index] = $object;
    }

    return $indexReferences;
  }

  /**
   * Processes a DITA folder.
   *
   * @param $pathToDirectory
   * @param $indexNodeID
   * @throws Exception
   *
   * @return Index
   *  The index root node
   */
  public function process($pathToDirectory, $indexNodeID = '0') {
    // Load the table of references
    $xml = simplexml_load_file($pathToDirectory . '/' . 'Ditamap.ditamap');

    $children = array();
    $objectReferences = array();
    $xrefReferences = array();

    // Process each child and add to Index as children
    foreach ($xml->children() as $child) {
      $nodeType = $child->getName();

      if ($nodeType == 'topichead') {
        $children[] = $this->traverseNode($child, $pathToDirectory, $indexNodeID, $objectReferences, $xrefReferences);
      }
    }

    // Merge references into reference overview.
    $indexReferences = $this->replaceReferences($objectReferences, $xrefReferences);

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
