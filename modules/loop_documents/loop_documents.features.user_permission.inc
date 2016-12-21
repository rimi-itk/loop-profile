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

  // Exported permission: 'menu view unpublished'.
  $permissions['menu view unpublished'] = array(
    'name' => 'menu view unpublished',
    'roles' => array(
      'administrator' => 'administrator',
      'document editor' => 'document editor',
    ),
    'module' => 'menu_view_unpublished',
  );

  return $permissions;
}
