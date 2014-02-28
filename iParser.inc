<?php


/**
 * Interface iParser
 *
 * Specifies the functions a Parser must contain.
 */
interface iParser {
  /**
   * Identifies whether a directory matches the format of the parser.
   *
   * @param $pathToDirectory
   *  path to the directory
   *
   * @return bool
   *  true if directory identified, false otherwise.
   */
  public function identifyFormat($pathToDirectory);

  /**
   * Processes the directory.
   *
   * @param $pathToDirectory
   */
  public function process($pathToDirectory);
}