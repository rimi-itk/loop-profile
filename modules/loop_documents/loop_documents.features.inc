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
  if ($module == "page_manager" && $api == "pages_default") {
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
      'name' => t('Dokumentsamling'),
      'base' => 'node_content',
      'description' => t('En samling af dokumenter'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
    'loop_documents_document' => array(
      'name' => t('Dokument'),
      'base' => 'node_content',
      'description' => t('Et dokument der kan puttes i en samling'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
