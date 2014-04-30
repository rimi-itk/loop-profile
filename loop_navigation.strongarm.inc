<?php
/**
 * @file
 * loop_navigation.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function loop_navigation_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_block_ids';
  $strongarm->value = array(
    0 => 1,
    1 => 2,
  );
  $export['menu_block_ids'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_expanded';
  $strongarm->value = array(
    0 => 'management',
  );
  $export['menu_expanded'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_masks';
  $strongarm->value = array(
    0 => 501,
    1 => 493,
    2 => 250,
    3 => 247,
    4 => 246,
    5 => 245,
    6 => 241,
    7 => 125,
    8 => 124,
    9 => 123,
    10 => 122,
    11 => 121,
    12 => 117,
    13 => 63,
    14 => 62,
    15 => 61,
    16 => 60,
    17 => 59,
    18 => 58,
    19 => 56,
    20 => 44,
    21 => 31,
    22 => 30,
    23 => 29,
    24 => 24,
    25 => 23,
    26 => 21,
    27 => 15,
    28 => 14,
    29 => 13,
    30 => 11,
    31 => 8,
    32 => 7,
    33 => 6,
    34 => 5,
    35 => 3,
    36 => 2,
    37 => 1,
  );
  $export['menu_masks'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'special_menu_items_nolink_tag';
  $strongarm->value = '<a href="#">';
  $export['special_menu_items_nolink_tag'] = $strongarm;

  return $export;
}
