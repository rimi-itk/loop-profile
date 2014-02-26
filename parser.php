<?php

class DITAParser {
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
   * @param $filename
   * @throws Exception
   */
  public function process($filename) {
    $xml = simplexml_load_file($filename);

    foreach ($xml->children() as $child) {
      $this->traverseNode($child, 0);
    }
  }
}

class Parser {
  public function parse($filename, $pathToDirectory) {
    if ($this->extractZip($filename, $pathToDirectory)) {
      // Zip file extracted. Search for correct parser.
      list($parserName, $filename) = $this->search($pathToDirectory);
      $parser = new $parserName();
      $parser->process($filename);
    }
  }

  /**
   * Extracts a zip file to a directory.
   *
   * @param $filename
   * @param $pathToDirectory
   * @return bool
   */
  private function extractZip($filename, $pathToDirectory) {
    $zip = new ZipArchive;
    $res = $zip->open($filename);
    if ($res === TRUE) {
      // extract it to the path we determined above
      $zip->extractTo($pathToDirectory);
      $zip->close();
    } else {
      return false;
    }
    return true;
  }

  /**
   * Search $pathToDirectory that our registered parsers know of.
   *
   * @param $pathToDirectory
   *   Path to extracted files.
   *
   * @return string
   *   Parser name.
   */
  private function search($pathToDirectory) {
    // TODO: We need a little more logic here.
    return array('DITAParser', $pathToDirectory . '/DITA/Ditamap.ditamap');
  }
}
