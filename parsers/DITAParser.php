<?php

include_once 'iParser.inc';

class DITAParser implements iParser {
  /**
   * Print a number of whitespaces
   *
   * @param $number
   */
  private function printLines($number) {
    for ($i = 0; $i < $number; $i++) {
      printf('&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;');
    }
  }

  /**
   * Prints a topichead, and handles child nodes
   *
   * @param $node
   * @param $nesting
   */
  private function printList($node, $nesting) {
    $this->printLines($nesting);
    printf('<b>' . $node['navtitle'] . '</b><br/>');
    foreach ($node->children() as $child) {
      $this->traverseNode($child, $nesting + 1);
    }
  }

  /**
   * Prints a topicref node
   *
   * @param $node
   * @param $nesting
   */
  private function printReference($node, $nesting) {
    $this->printLines($nesting);
    printf('' . $node['navtitle'] . ': <a href="' . $node['href'] . '">'. $node['href'] .'</a>');
    printf('<br/>');
  }

  private function getReference($node) {
    $node['href'];
  }


  /**
   * Traverses a topichead node
   *
   * @param $node
   * @param $nesting
   */
  private function traverseNode($node, $nesting) {
    $nodeType = $node->getName();
    if ($nodeType == 'topicref') {
      $this->printReference($node, $nesting);

      $this->getReference($node);
    } else {
      $this->printList($node, $nesting);
    }
  }

  /**
   * Processes a Dita zip file
   *
   * @param $pathToDirectory
   * @throws Exception
   */
  public function process($pathToDirectory) {
    $entries = scandir($pathToDirectory);

    print_r($entries);
/*
    foreach ($entries as $entry) {
      if (is_dir($entry)) {
        printf(dirname($entry));
      }
    }
*/
    //$xml = simplexml_load_file($filename);

    //foreach ($xml->children() as $child) {
    //  $this->traverseNode($child, 0);
    //}
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