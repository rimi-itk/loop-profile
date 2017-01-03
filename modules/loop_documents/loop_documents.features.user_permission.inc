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

  // Exported permission: 'access media browser'.
  $permissions['access media browser'] = array(
    'name' => 'access media browser',
    'roles' => array(
      'administrator' => 'administrator',
      'document author' => 'document author',
      'document editor' => 'document editor',
    ),
    'module' => 'media',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
      'document editor' => 'document editor',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'create loop_documents_collection content'.
  $permissions['create loop_documents_collection content'] = array(
    'name' => 'create loop_documents_collection content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create loop_documents_document content'.
  $permissions['create loop_documents_document content'] = array(
    'name' => 'create loop_documents_document content',
    'roles' => array(
      'document author' => 'document author',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any loop_documents_collection content'.
  $permissions['delete any loop_documents_collection content'] = array(
    'name' => 'delete any loop_documents_collection content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any loop_documents_document content'.
  $permissions['delete any loop_documents_document content'] = array(
    'name' => 'delete any loop_documents_document content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own loop_documents_collection content'.
  $permissions['delete own loop_documents_collection content'] = array(
    'name' => 'delete own loop_documents_collection content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own loop_documents_document content'.
  $permissions['delete own loop_documents_document content'] = array(
    'name' => 'delete own loop_documents_document content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any loop_documents_collection content'.
  $permissions['edit any loop_documents_collection content'] = array(
    'name' => 'edit any loop_documents_collection content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any loop_documents_document content'.
  $permissions['edit any loop_documents_document content'] = array(
    'name' => 'edit any loop_documents_document content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own loop_documents_collection content'.
  $permissions['edit own loop_documents_collection content'] = array(
    'name' => 'edit own loop_documents_collection content',
    'roles' => array(
      'document editor' => 'document editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own loop_documents_document content'.
  $permissions['edit own loop_documents_document content'] = array(
    'name' => 'edit own loop_documents_document content',
    'roles' => array(
      'document author' => 'document author',
    ),
    'module' => 'node',
  );

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
    ),
    'module' => 'filter',
  );

  return $permissions;
}
