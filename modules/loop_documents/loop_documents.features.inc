<?php
/**
 * @file
 * loop_documents.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_documents_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function loop_documents_node_info() {
  $items = array(
    'loop_documents_collection' => array(
      'name' => t('Document collection'),
      'base' => 'node_content',
      'description' => t('A collection of documents'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'loop_documents_document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('A document that can be put into a document collection'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
