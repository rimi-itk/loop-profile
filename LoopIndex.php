<?php

class LoopIndex {
  private $children;

  public function __construct($children) {
    $this->children = $children;
  }

  public function getChildren() {
    return $this->children;
  }
} 
