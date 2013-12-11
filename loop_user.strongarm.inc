<?php
/**
 * @file
 * loop_user.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function loop_user_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pcp_enabled_fields';
  $strongarm->value = array(
    0 => 5,
    1 => 8,
    2 => 9,
    3 => 10,
    4 => 11,
    5 => 12,
  );
  $export['pcp_enabled_fields'] = $strongarm;

  return $export;
}
