<?php
/**
 * @file
 * loop_external_data.features.inc
 */

/**
 * Implements hook_node_info().
 */
function loop_external_data_node_info() {
  $items = array(
    'index' => array(
      'name' => t('Index'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'leaf' => array(
      'name' => t('Leaf'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'tree' => array(
      'name' => t('Tree'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
