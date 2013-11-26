<?php
/**
 * @file
 * loop_question.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_question_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function loop_question_node_info() {
  $items = array(
    'question' => array(
      'name' => t('Question'),
      'base' => 'node_content',
      'description' => t('Et indlæg, spørgsmål eller observation, hvortil der kan svares.'),
      'has_title' => '1',
      'title_label' => t('Question'),
      'help' => '',
    ),
  );
  return $items;
}
