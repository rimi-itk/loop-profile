<?php
/**
 * @file
 * A part of the loop_external_data module.
 */

/**
 * Class LoopNode
 *
 * Represents a node of external data.
 */
class LoopNode {
  private $title;

  public function __construct($title) {
    $this->title = $title;
  }

  public function getTitle() {
    return $this->title;
  }
}
