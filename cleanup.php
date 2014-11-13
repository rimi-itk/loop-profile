#!/usr/bin/env drush
<?php

/**
 * @file Cleanup flagging.
 */

// Delete every flagged message.
db_delete('flagging')
  ->condition('entity_type', 'message')
  ->execute();

// Delete every flagged nodes.
db_delete('flagging')
  ->condition('entity_type', 'node')
  ->execute();

// Delete all messages.
db_delete('message')
  ->execute();

// Get post nodes.
$nodes = db_select('node', 'n')
  ->fields('n', array('nid'))
  ->condition('type', 'post')
  ->condition('status', 1)
  ->execute()
  ->fetchAllAssoc('nid');

// Get every user.
$users = db_select('users', 'u')
  ->fields('u', array('uid'))
  ->condition('status', 1)
  ->execute()
  ->fetchAllAssoc('uid');

// Insert flagging according to nodes and users.
foreach (array_keys($nodes) as $node) {
  foreach (array_keys($users) as $user) {
    db_insert('flagging')
      ->fields(array(
        'fid' => 3,
        'entity_type' => 'node',
        'entity_id' => $node,
        'uid' => $user,
        'sid' => 0,
        'timestamp' => REQUEST_TIME,
      ))
      ->execute();
  }
}
