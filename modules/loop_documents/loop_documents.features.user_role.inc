<?php
/**
 * @file
 * loop_documents.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function loop_documents_user_default_roles() {
  $roles = array();

  // Exported role: document author.
  $roles['document author'] = array(
    'name' => 'document author',
    'weight' => 7,
  );

  // Exported role: document editor.
  $roles['document editor'] = array(
    'name' => 'document editor',
    'weight' => 6,
  );

  return $roles;
}
