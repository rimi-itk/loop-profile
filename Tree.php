<?php
/**
 * @file
 * A part of the loop_external_data module.
 */

/**
 * Class Tree
 *
 * Represents a tree in external data.
 */
class Tree extends LoopNode {
  private $children;

  public function __construct($title, $children) {
    parent::__construct($title);
    $this->children = $children;
  }

  public function getChildren() {
    return $this->children;
  }
}
