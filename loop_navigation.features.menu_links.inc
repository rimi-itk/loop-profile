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

  // Exported menu link: main-menu_menu:<nolink>
  $menu_links['main-menu_menu:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Menu',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'main-menu_menu:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Menu');


  return $menu_links;
}
