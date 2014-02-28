<?php

include_once 'tree.php';

class Index {
  private $children;

  public function __construct($children) {
    $this->children = $children;
  }

  public function getChildren() {
    return $this->children;
  }
} 