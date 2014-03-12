<?php

/**
 * Class DITAParser
 *
 * For passing a DITA folder.
 */
class DITAParser implements iParser {
  /**
   * Rename a DOMElement.
   *
   * @param $oldTag
   * @param $newTagName
   * @return DOMElement
   */
  private function renameTag($oldTag, $newTagName ) {
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
   * @param $element
   */
  private function removeAttributes($element) {
    $attributes = $element->attributes;
    while ($attributes->length) {
      $element->removeAttribute($attributes->item(0)->name);
    }
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

    // Iterate through parts and assemble new path array.
    // Pop the top element when ".." is encountered.
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
    // Assemble the new path array to a string
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
    // Get the type of the given node.
    $nodeType = $node->getName();

    if ($nodeType == 'topicref') {
      // Get the reference to the topicref file.
      $href = $node['href'];

      // Load body of topic into DOM.
      $body = simplexml_load_file($pathToDirectory . '/' . $href)->body;
      $domnode = dom_import_simplexml($body);
      $dom = new DOMDocument();
      $domnode = $dom->importNode($domnode, true);
      $dom->appendChild($domnode);

      // Setup XPath for DOM.
      $xpath = new DOMXPath($dom);

      // Replace conrefs
      // From these cases: http://docs.oasis-open.org/dita/v1.1/OS/langspec/common/theconrefattribute.html
      // Only implemented "Using conref to refer to an element within a topic"
      foreach ($xpath->query('//*[@conref]') as $conrefElement) {
        $conref = $conrefElement->getAttribute('conref');
        $conrefSplit = explode('#', $conref);

        $countConrefSplit = count($conrefSplit);

        $filePath = $conrefSplit[0];
        $varXML = simplexml_load_file($pathToDirectory . '/' . dirname($href) . '/' . $filePath);
        if (!$varXML) {
          $msg = array(
            "message" => "import error: file not found",
            "ref" => $pathToDirectory . '/' . dirname($href) . '/' . $filePath
          );
          watchdog('loop_external_data', print_r($msg, 1));
          continue;
        }


        if ($countConrefSplit == 2) {
          $idArray = explode('/', $conrefSplit[1]);
          $id = $idArray[1];
          $containId = $idArray[0];

          // TODO: This is not complete correct, but matches the Flare Dita output
          // Correct syntax - $sxml = $varXML->xpath('(//*[@id="' . $containId . '"]//*[@id="' . $id . '"])[last()]');
          $sxml = $varXML->xpath('(//topic//*[@id="' . $id . '"])[last()]');
          if (!$sxml) {
            $msg = array(
              "message" => "import error: entry not found",
              "conref" => '"' . $conref . '"',
              "ref" => '"' . $pathToDirectory . '/' . dirname($href) . '/' . $filePath . '"',
              "containerid" => '"' . $containId . '"',
              "id" =>  '"' . $id . '"');
            watchdog('loop_external_data', print_r($msg, 1));
            continue;
          }

          $xml = dom_import_simplexml($sxml[0]);

          $domXML = $dom->importNode($xml, true);

          // Replace with neutral html element
          $newElement = $dom->createElement('span');
          foreach ($domXML->childNodes as $child) {
            $newElement->appendChild($child);
          }

          $conrefElement->parentNode->replaceChild($newElement, $conrefElement);
        }
      }

      // Replace image paths.
      foreach ($xpath->query('//image') as $image) {
        // Contruct path to image file.
        $ref = $pathToDirectory . '/' . dirname($href) . '/' . $image->getAttribute('href');

        // Read file from  disk.
        $fileName = basename($image->getAttribute('href'));
        $fileContent = file_get_contents($ref);

        // Save file into Drupal.
        $dir = 'public://external_data/' . $indexNodeID;
        file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
        $file = file_save_data($fileContent, $dir . '/' . $fileName, FILE_EXISTS_RENAME);
        $filePath = file_create_url($file->uri);

        // Set up new image html element.
        $image->removeAttribute('href');
        $image->setAttribute('src', $filePath);
        $this->renameTag($image, 'img');
      }

      // Replace references
      foreach ($xpath->query('//xref') as $xref) {
        // External links have the scope attribute set to external
        $scope = $xref->getAttribute('scope');

        if ($scope != 'external') {
          $xhref = dirname($href) . '/' . $xref->getAttribute('href');
          $nextIndex = count($xrefReferences);

          $xhref = explode('#', $xhref);
          $xrefReferences[$this->collapsePath($xhref[0])] = $nextIndex;

          // Check for empty content, insert title from references topic as text.
          if ($xref->nodeValue === '') {
            $refXML = simplexml_load_file($pathToDirectory . '/' . $xhref[0]);

            foreach ($refXML->xpath("//topic/title") as $title) {
              $xref->nodeValue = (string)$title;
              break;
            }
          }
          $xref->setAttribute('href', $nextIndex);
        } else {
          $xref->setAttribute('target',  '_blank');
        }

        // Change name of node to a
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

      // Rename body to div
      foreach($xpath->query('//body') as $b) {
        $b->setAttribute('class', 'external-content');
        $this->renameTag($b, 'div');
      }

      // Convert dom to html.
      $body = $dom->saveHTML();

      // Get next leaf id
      $nextLeafID = count($objectReferences);

      // Make leaf from title of the node and the body.
      $leaf = new Leaf((string)$node['navtitle'], $body, $nextLeafID);

      // Save href to leaf reference.
      $objectReferences[$href] = $nextLeafID;

      return $leaf;
    } else if ($nodeType == 'topichead') {
      $children = array();

      // Iterate through children, and add the result of traversing each.
      foreach ($node->children() as $child) {
        $children[] = $this->traverseNode($child, $pathToDirectory, $indexNodeID, $objectReferences, $xrefReferences);
      }

      $tree = new Tree((string)$node['navtitle'], $children);
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
      $leafID = $objectReferences[$ref];
      $arr = array(
        'leafID'=>$leafID,
        'nid'=>-1
      );
      $indexReferences[$index] = $arr;
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
      $children[] = $this->traverseNode($child, $pathToDirectory, $indexNodeID, $objectReferences, $xrefReferences);
    }

    // Merge references into reference overview.
    $indexReferences = $this->replaceReferences($objectReferences, $xrefReferences);

    $index = new LoopIndex($children, $indexReferences);
    return $index;
  }


  /**
   * Identify if this is a DITA folder
   * Look through the folder for a Ditamap.ditamap file.
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
