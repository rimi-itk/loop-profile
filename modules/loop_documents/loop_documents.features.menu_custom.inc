<?php

/**
 * @file
 * loop_documents.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function loop_documents_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-document-author-management.
  $menus['menu-document-author-management'] = array(
    'menu_name' => 'menu-document-author-management',
    'title' => 'Document author management',
    'description' => '',
    'language' => 'und',
    'i18n_mode' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Document author management');

  return $menus;
}
