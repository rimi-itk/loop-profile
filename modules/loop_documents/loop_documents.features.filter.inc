<?php
/**
 * @file
 * loop_documents.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function loop_documents_filter_default_formats() {
  $formats = array();

  // Exported format: Loop documents.
  $formats['loop_documents'] = array(
    'format' => 'loop_documents',
    'name' => 'Loop documents',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'ckeditor_link_filter' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'media_filter' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
