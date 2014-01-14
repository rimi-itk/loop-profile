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
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_menu:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 50,
    'customized' => 1,
  );
  // Exported menu link: menu-loop-primary-menu_another-example-menu-item:<front>
  $menu_links['menu-loop-primary-menu_another-example-menu-item:<front>'] = array(
    'menu_name' => 'menu-loop-primary-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Another example menu item',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-loop-primary-menu_another-example-menu-item:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-loop-primary-menu_example-menu-item:<front>
  $menu_links['menu-loop-primary-menu_example-menu-item:<front>'] = array(
    'menu_name' => 'menu-loop-primary-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Example menu item',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-loop-primary-menu_example-menu-item:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Another example menu item');
  t('Example menu item');
  t('Menu');


  return $menu_links;
}
