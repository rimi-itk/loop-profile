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
   * Processes a Dita zip file
   *
   * @param $filename
   * @throws Exception
   */
  public function processDitaZip($filename) {
    $path = pathinfo(realpath($filename . '.zip'), PATHINFO_DIRNAME);
    $pathToDirectory = $path . '/zip-extracts/' . $filename;

    if (!$this->extractZip($filename . '.zip', $pathToDirectory)) {
      throw new Exception("Unzip failed!");
    }

    $xml = simplexml_load_file($pathToDirectory . '/' . $filename . '/Ditamap.ditamap');

    foreach ($xml->children() as $child) {
      $this->traverseNode($child, 0);
    }
  }
}

$parser = new DITAParser();

header("Content-Type: text/html; charset=UTF-8");

$parser->processDitaZip('DITA');

