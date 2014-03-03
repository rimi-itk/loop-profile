<?php

class DITAParser implements iParser {
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

  private function danishChars($text) {
    $text = preg_replace('/å/', '%86', $text);
    $text = preg_replace('/Å/', '%87', $text);
    $text = preg_replace('/æ/', '%91', $text);
    $text = preg_replace('/Æ/', '%92', $text);
    $text = preg_replace('/ø/', '%9B', $text);
    $text = preg_replace('/Ø/', '%9C', $text);
    return $text;
  }

  private function traverseNode($node, $pathToDirectory, $references) {
    $nodeType = $node->getName();

    if ($nodeType == 'topicref') {
      $href = $this->danishChars($node['href']);

      // Get the reference
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

      // Replace image paths
      foreach ($xpath->query('//image') as $image) {
        $ref = $pathToDirectory . '/' . dirname($href) . '/' . $image->getAttribute('href');

        // Save file
        $fileName = basename($image->getAttribute('href'));
        $fileContent = file_get_contents($ref);
        $file = file_save_data($fileContent, 'public://' . $fileName, FILE_EXISTS_RENAME);
        $filePath = file_create_url($file->uri);

        $image->removeAttribute('href');
        $image->setAttribute('src', $filePath);
        $this->renameTag($image, 'img');
      }

      $body = $dom->saveHTML();

      $body = preg_replace('/<body>/', '', $body);
      $body = preg_replace('/<\/body>/', '', $body);

      $leaf = new Leaf($node['navtitle'], $body);
      return $leaf;
    } else if ($nodeType == 'topichead') {
      $children = array();
      foreach ($node->children() as $child) {
        $children[] = $this->traverseNode($child, $pathToDirectory, $references);
      }

      $tree = new Tree($node['navtitle'], $children);
      return $tree;
    }
    return null;
  }

  /**
   * Processes a Dita zip file
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
    $references = array();

    foreach ($xml->children() as $child) {
      $nodeType = $child->getName();

      if ($nodeType == 'topichead') {
        $children[] = $this->traverseNode($child, $pathToDirectory, $references);
      }
    }

    $index = new LoopIndex($children);

    return $index;
  }

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
