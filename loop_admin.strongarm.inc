<?php
/**
 * @file
 * loop_admin.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function loop_admin_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_defaults';
  $strongarm->value = array(
    'subscribe_node' => TRUE,
    'subscribe_taxonomy_term' => TRUE,
    'subscribe_user' => TRUE,
    'message' => TRUE,
    'user_messages' => FALSE,
  );
  $export['views_defaults'] = $strongarm;

  return $export;
}
