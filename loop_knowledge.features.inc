<?php
/**
 * @file
 * loop_knowledge.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_knowledge_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index_alter().
 */
function loop_knowledge_default_search_api_index_alter(&$data) {
  if (isset($data['post'])) {
    $data['post']->options['data_alter_callbacks']['search_api_alter_bundle_filter']['settings']['bundles']['page'] = 'page'; /* WAS: '' */
    $data['post']->options['data_alter_callbacks']['search_api_alter_bundle_filter']['settings']['bundles']['vejledning'] = 'vejledning'; /* WAS: '' */
    $data['post']->options['data_alter_callbacks']['search_api_alter_language_control'] = array(
      'status' => 0,
      'weight' => 0,
      'settings' => array(
        'lang_field' => '',
        'languages' => array(),
      ),
    ); /* WAS: '' */
    $data['post']->options['fields']['body:value'] = array(
      'type' => 'text',
    ); /* WAS: '' */
    $data['post']->options['fields']['title'] = array(
      'type' => 'text',
    ); /* WAS: '' */
    unset($data['post']->options['data_alter_callbacks']['search_api_alter_bundle_filter']['settings']['bundles']['external_sources']);
    unset($data['post']->options['data_alter_callbacks']['search_api_alter_bundle_filter']['settings']['bundles']['leaf']);
  }
}

/**
 * Implements hook_node_info().
 */
function loop_knowledge_node_info() {
  $items = array(
    'instruction' => array(
      'name' => t('Instruction'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
