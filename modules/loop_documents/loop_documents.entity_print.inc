<?php

/**
 * @file
 * Implementation of entity_print hooks.
 */

/**
 * Implements hook_entity_print_css().
 */
function loop_documents_entity_print_css($entity_type, $entity) {
  if ($entity_type === 'node' && $entity->type === 'loop_documents_collection') {
    $path = drupal_get_path('theme', 'loop');
    entity_print_add_css($path . '/css/styles.css');
    entity_print_add_css($path . '/css/pdf.css');
  }
}

/**
 * Implements hook_entity_print_pdf_alter().
 */
function loop_documents_entity_print_pdf_alter(WkHtmlToPdf $pdf, $entity_type, $entity) {
  if ($entity_type === 'node' && $entity->type === 'loop_documents_collection') {
    $options = loop_documents_get_wkhtmltopdf_options(TRUE, $entity);
    if ($options) {
      $pdf->setOptions($options);
    }
  }
}
