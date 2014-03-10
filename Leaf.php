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
  private $leafID;
  private $drupalNID;

  public function __construct($title, $body, $leafID) {
    parent::__construct($title);
    $this->body = $body;
    $this->leafID = $leafID;
    $this->drupalNID = -1;
  }

  public function getBody() {
    return $this->body;
  }

  public function setBody($body) {
    $this->body = $body;
  }

  public function getLeafID() {
    return $this->leafID;
  }

  public function getDrupalNID() {
    return $this->drupalNID;
  }

  public function setDrupalNID($drupalNID) {
    $this->drupalNID = $drupalNID;
  }
} 
