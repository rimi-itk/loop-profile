<?php
/**
 * @file
 * loop_notification.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function loop_notification_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_messages:user/1/messages
  $menu_links['main-menu_messages:user/1/messages'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'user/1/messages',
    'router_path' => 'user/%/messages',
    'link_title' => 'Messages',
    'options' => array(
      'menu_token_link_path' => 'user/[current-user:uid]/messages',
      'menu_token_data' => array(),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'alter' => TRUE,
      'identifier' => 'main-menu_messages:user/1/messages',
      'attributes' => array(
        'rel' => 'nav-mail-icon',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Messages');


  return $menu_links;
}
