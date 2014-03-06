<?php
/**
 * @file
 * A part of the loop_external_data module.
 */

class LoopIndex {
  private $children;
  private $references;

  public function __construct($children, $references) {
    $this->children = $children;
    $this->references = $references;
  }

  public function getChildren() {
    return $this->children;
  }

  public function getReferences() {
    return $this->references;
  }
}
