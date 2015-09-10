<?php
/**
 * @file
 * loop_knowledge.features.inc
 */

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
    unset($data['post']->options['fields']['type']);
  }
}
