<?php

class ZipParsingException extends Exception {}
class NoParserFoundException extends Exception {}

/**
 * Class Parser
 *
 */
class Parser {
  /**
   * Parses a zip file.
   *
   * @param $filename
   *  The name of the zip file
   * @param $pathToDirectory
   *  The path to the directory to unzip into.
   *
   * @throws ZipExtractionException
   * @throws NoParserFoundException
   *
   * @returns $data
   *  The data formatted as XML.
   */
  public function parse($filename, $pathToDirectory) {
    if ($this->extractZip($filename, $pathToDirectory)) {
      // Zip file extracted. Find folder.
      if ( (is_dir($pathToDirectory)) && ($dh = opendir($pathToDirectory)) ) {
        while (($directory = readdir($dh)) !== FALSE) {
          if (is_readable($pathToDirectory . '/' . $directory) && is_dir($pathToDirectory . '/' . $directory) && (!in_array($directory, array('.', '..')))) {
            $parser = $this->search($pathToDirectory . '/' . $directory);

            if (is_null($parser)) {
              throw new NoParserFoundException();
            }

            // Get output data.
            $data = $parser->process($pathToDirectory . '/' . $directory);

            return $data;
          }
        }
      }
    }
  }

  /**
   * Extracts a zip file to a directory.
   *
   * @param $filename
   * @param $pathToDirectory
   * @return bool
   *  Did the extraction succeed?
   */
  private function extractZip($filename, $pathToDirectory) {
    $zip = new ZipArchive();
    $res = $zip->open($filename);
    if ($res === TRUE) {
      $zip->extractTo($pathToDirectory);
      $zip->close();
    } else {
      return false;
    }
    return true;
  }

  /**
   * Search $pathToDirectory for a match with known parsers.
   *
   * @param $pathToDirectory
   *   Path to extracted files.
   *
   * @return parser
   */
  private function search($pathToDirectory) {
    $parser = null;

    $path = drupal_get_path('module', 'loop_external_data');
    $path .= '/parsers/';

    if ( (is_dir($path)) && ($dh = opendir($path)) ) {
      while (($file = readdir($dh)) !== FALSE) {
        if (fnmatch("*.php", $file) && is_readable($path . $file)) {
          include $path . $file;

          $className = basename($file, '.php');

          $testParser = new $className();

          if ($testParser->identifyFormat($pathToDirectory)) {
            $parser = $testParser;
            break;
          }
        }
      }
    }
    return $parser;
  }
}
