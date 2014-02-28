<?php

include_once 'node.php';

class Tree extends Node {
  private $children;

  public function __construct($title, $children) {
    parent::__construct($title);
    $this->children = $children;
  }

  public function getChildren() {
    return $this->children;
  }
}