<?php
/**
 * @file
 * loop_documents.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function loop_documents_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'entity print access bundle comment_node_loop_documents_collection'.
  $permissions['entity print access bundle comment_node_loop_documents_collection'] = array(
    'name' => 'entity print access bundle comment_node_loop_documents_collection',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'entity_print',
  );

  // Exported permission: 'menu view unpublished'.
  $permissions['menu view unpublished'] = array(
    'name' => 'menu view unpublished',
    'roles' => array(
      'administrator' => 'administrator',
      'document editor' => 'document editor',
    ),
    'module' => 'menu_view_unpublished',
  );

  // Exported permission: 'use text format loop_documents'.
  $permissions['use text format loop_documents'] = array(
    'name' => 'use text format loop_documents',
    'roles' => array(
      'administrator' => 'administrator',
      'document author' => 'document author',
      'document editor' => 'document editor',
      'documentation coordinator' => 'documentation coordinator',
      'manager' => 'manager',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
