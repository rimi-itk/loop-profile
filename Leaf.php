<?php
/**
 * @file
 * A part of the loop_external_data module.
 */

/**
 * Class Leaf
 */
class Leaf extends LoopNode {
  private $body;

  public function __construct($title, $body) {
    parent::__construct($title);
    $this->body = $body;
  }

  public function getBody() {
    return $this->body;
  }

  public function setBody($body) {
    $this->body = $body;
  }
} 
