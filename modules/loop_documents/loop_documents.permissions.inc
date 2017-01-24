<?php

/**
 * @file
 * Permission settings for the loop_documents module.
 */

/**
 * Implements hook_permissions().
 *
 * Add permission to restrict access to certain admin paths.
 */
function loop_documents_permission() {
  $permissions = array();

  $paths = array(
    'admin',
    'admin/content',
  );

  foreach ($paths as $path) {
    $permissions['access path ' . $path] = array(
      'title' => t('Access path %path', array('%path' => $path)),
      'description' => t('Access path %path', array('%path' => $path)),
    );
  }

  return $permissions;
}

/**
 * Implements hook_permissions_secure_permissions_roles().
 */
function loop_documents_secure_permissions_roles() {
  return array(
    'document author',
    'document collection editor',
  );
}

/**
 * Implements hook_secure_permissions().
 */
function loop_documents_secure_permissions($role) {
  $permissions = array(
    'authenticated user' => array(
      'entity print access bundle loop_documents_collection',
      'view files',
    ),
    'document author' => array(
      'access administration pages',

      // Allow access to some admin paths.
      'access path admin',
      'access path admin/content',

      'access content overview',
      'view the administration theme',

      'access media browser',
      'access ckeditor link',
      'create files',
      'create loop_documents_document content',
      'edit own loop_documents_document content',
      'download any image files',
      'use media wysiwyg',
      'use text format loop_documents',
    ),
  );

  $permissions['document collection editor'] = array_merge(
    $permissions['document author'],
    array(
      'administer menu',
      'create loop_documents_collection content',
      'edit any loop_documents_collection content',
      'edit any loop_documents_document content',
      'view any unpublished loop_documents_collection content',
      'view any unpublished loop_documents_document content',
      'delete any image files',
      'delete any loop_documents_collection content',
      'delete any loop_documents_document content',
      'edit any image files',
      'menu view unpublished',
    ));

  $permissions['administrator'] = $permissions['document collection editor'];

  return isset($permissions[$role]) ? $permissions[$role] : NULL;
}

/**
 * Implements hook_menu_alter().
 *
 * See http://stackoverflow.com/a/5125994.
 */
function loop_documents_menu_alter(&$items) {
  foreach ($items as $path => &$item) {
    if ($path === 'admin' || strpos($path, 'admin/') === 0) {
      if (isset($item['access arguments'])) {
        $item['access arguments'][] = isset($item['access callback']) ? $item['access callback'] : 'user_access';
      }
      else {
        $item['access arguments'] = array();
      }
      $item['access arguments'][] = $path;
      $item['access callback'] = 'loop_documents_menu_access';
    }
  }
}

/**
 * Menu access callback.
 */
function loop_documents_menu_access() {
  $args = func_get_args();
  $path = array_pop($args);
  $access_callback = array_pop($args);

  if (is_callable($access_callback) && count($args) > 0 && !call_user_func_array($access_callback, $args)) {
    return FALSE;
  }

  // Check admin access for 'document author' and 'document collection editor'.
  $user_role_names = array_flip($GLOBALS['user']->roles);
  if (isset($user_role_names['document author']) || isset($user_role_names['document collection editor'])) {
    if (!user_access('access path ' . $path)) {
      return FALSE;
    }
  }

  return TRUE;
}
