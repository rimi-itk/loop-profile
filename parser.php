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
    $pathToExtractedDirectory = $pathToDirectory . '/' . basename($filename, '.zip');

    if ($this->extractZip($filename, $pathToDirectory)) {
      // Zip file extracted. Search for correct parser.
      $parser = $this->search($pathToExtractedDirectory);

      if (is_null($parser)) {
        throw new NoParserFoundException();
      }

      // Get output data.
      $data = $parser->process($pathToExtractedDirectory);

      return $data;
    } else {
      throw new ZipExtractionException();
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

    foreach (glob("parsers/*.php") as $filename) {
      include_once $filename;

      $className = basename($filename, '.php');

      $testParser = new $className();

      if ($testParser->identifyFormat($pathToDirectory)) {
        $parser = $testParser;
        break;
      }
    }

    return $parser;
  }
}


/*
// TEST
header('Content-Type: text/xhtml; charset=utf-8');
$filename = 'DITA.zip';
$path = pathinfo(realpath($filename), PATHINFO_DIRNAME);
$pathToDirectory = $path . '/test';

$parser = new Parser();
$xml = $parser->parse($filename, $pathToDirectory);
print_r($xml);
*/
