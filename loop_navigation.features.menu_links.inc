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

  // Exported menu link: main-menu_menu:<front>
  $menu_links['main-menu_menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Menu',
    'options' => array(
      'identifier' => 'main-menu_menu:<front>',
      'attributes' => array(
        'class' => array(
          0 => 'nav--toggle-mobile-nav',
          1 => 'js-toggle-mobile-nav',
        ),
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Menu');


  return $menu_links;
}
