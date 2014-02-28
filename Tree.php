<?php

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
