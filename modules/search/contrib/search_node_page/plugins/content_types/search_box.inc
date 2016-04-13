<?php
/**
 * @file
 * Provides search field as a Panels content type.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Search node - search field'),
  'description' => t('Search field and filters for search node.'),
  'category' => t('Search'),
  'edit form' => 'search_node_page_search_box_content_type_edit_form',
  'render callback' => 'search_node_page_search_box_content_type_render',
  'admin info' => 'search_node_page_search_box_pane_admin_info',
  'defaults' => array(
    'search_node' => '',
  ),
  'all contexts' => TRUE,
);

/**
 * Return the pane contents.
 */
function search_node_page_search_box_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();


  $block->content = search_node_page_build_search_box($conf['search_node']);

  return $block;
}

/**
 * Return the pane titles.
 */
function search_node_page_search_box_content_type_admin_title($subtype, $conf, $context) {
  return t('Search box');
}

/**
 * Returns an edit form for the content type.
 */
function search_node_page_search_box_content_type_edit_form($form, &$form_state) {
  $form += search_node_page_configuration_form($form, $form_state, $form_state['conf']['search_node']);

  return $form;
}

function search_node_page_search_box_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * 'admin info' callback for panel pane.
 */
function search_node_page_search_box_pane_admin_info($subtype, $conf, $contexts) {
  if (!empty($conf)) {
    $block = new stdClass;
    $block->title = $conf['search_node']['server'] . ' - ' . $conf['search_node']['index'];
    /**
     * @TODO: Make overview based on configuration.
     */
    $block->content = 'Make pretty overview of settings';

    return $block;
  }
}
