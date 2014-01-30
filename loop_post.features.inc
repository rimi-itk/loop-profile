<?php
/**
 * @file
 * loop_post.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_post_ctools_plugin_api($module = NULL, $api = NULL) {
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
function loop_post_node_info() {
  $items = array(
    'post' => array(
      'name' => t('Indlæg'),
      'base' => 'node_content',
      'description' => t('A post, question or observation, which can be answered.'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'help' => '',
    ),
  );
  return $items;
}
