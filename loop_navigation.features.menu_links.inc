<?php
/**
 * @file
 * loop_navigation.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function loop_navigation_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_administration:admin
  $menu_links['management_administration:admin'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin',
    'router_path' => 'admin',
    'link_title' => 'Administration',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'management_administration:admin',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 9,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Administration');


  return $menu_links;
}
