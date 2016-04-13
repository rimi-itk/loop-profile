<?php
/**
 * @file
 * Provides search field as a Panels content type.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Search node - results'),
  'description' => t('Search results for search node.'),
  'category' => t('Search'),
  'edit form' => 'search_node_page_search_result_content_type_edit_form',
  'render callback' => 'search_node_page_search_result_content_type_render',
  'admin info' => 'search_node_page_search_result_pane_admin_info',
  'defaults' => array(),
  'all contexts' => TRUE,
);

/**
 * Return the pane contents.
 */
function search_node_page_search_result_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();


  $block->content = search_node_page_block_view('search_node_search_result');

  return $block;
}

/**
 * Return the pane titles.
 */
function search_node_page_search_result_content_type_admin_title($subtype, $conf, $context) {
  return t('Search results');
}

/**
 * Returns an edit form for the content type.
 */
function search_node_page_search_result_content_type_edit_form($form, &$form_state) {
  return $form;
}

function search_node_page_search_result_content_type_edit_form_submit(&$form, &$form_state) {

}

/**
 * 'admin info' callback for panel pane.
 */
function search_node_page_search_result_pane_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = t('Search node - results');
    $block->content = '';

    return $block;
  }
}
