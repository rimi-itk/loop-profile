<?php
/**
 * @file
 * A part of the loop_external_data module.
 */

/**
 * Class NoParserFoundException
 */
class NoParserFoundException extends Exception {}

/**
 * Class Parser
 *
 * Standard parser class. Selects relevant parser when calling parse().
 */
class Parser {
  /**
   * Parses a zip file.
   *
   * @param $filename
   *  The name of the zip file.
   * @param $pathToDirectory
   *  The path to the directory to unzip into.
   * @param $indexNodeID
   *  The id of the Index node added to Drupal.
   *
   * @throws NoParserFoundException
   *
   * @returns $data
   *  The data formatted as XML.
   */
  public function parse($filename, $pathToDirectory, $indexNodeID = '0') {
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
            $data = $parser->process($pathToDirectory . '/' . $directory, $indexNodeID);

            return $data;
          }
        }
      }
    }
  }

  /**
   * Convert from CP865 to UTF8 characters in $text to UTF-8.
   *
   * @param $text
   * @return mixed
   */
  private function convertCP865ToUTF8($text) {
    $text = iconv("CP865", "UTF-8", rawurldecode($text));

    return $text;
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
    file_prepare_directory($pathToDirectory, FILE_CREATE_DIRECTORY);

    $za = new ZipArchive();

    $za->open($filename);

    for( $i = 0; $i < $za->numFiles; $i++ ){
      $stat = $za->statIndex( $i );
      $entryname = $this->convertCP865ToUTF8($stat['name']);
      // if getFromIndex returns false it is a directory
      if ($content = $za->getFromIndex($i)) {
        file_put_contents($pathToDirectory . '/' . $entryname, $content);
      } else {
        $path = $pathToDirectory . '/' . $entryname;
        file_prepare_directory($path, FILE_CREATE_DIRECTORY);
      }
    }
    $za->close();

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
