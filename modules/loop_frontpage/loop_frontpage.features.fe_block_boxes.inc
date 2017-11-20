<?php
/**
 * @file
 * loop_frontpage.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function loop_frontpage_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Velkomst til sitet';
  $fe_block_boxes->format = 'html';
  $fe_block_boxes->machine_name = 'welcome';
  $fe_block_boxes->body = 'Velkommen til Loop';

  $export['welcome'] = $fe_block_boxes;

  return $export;
}
