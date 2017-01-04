<?php

/**
 * @file
 * Permission settings for the loop_documents module.
 */

/**
 * Implements hook_permission().
 *
 * The permission 'administer documents' has rights to …
 *
 * The permission 'administer document collections' has rights to …
 */
function loop_documents_permission() {
  return array(
    'administer documents' => array(
      'title' => t('Administer documents'),
      'description' => t('Permission to administer documents'),
    ),
    'administer document collections' => array(
      'title' => t('Administer document collections'),
      'description' => t('Permission to administer document collections'),
    ),
  );
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
      'access media browser',
      'create files',
      'create loop_documents_document content',
      'download any image files',
      'edit own loop_documents_document content',
      'use media wysiwyg',
      'use text format loop_documents',
    ),
  );

  $permissions['document collection editor'] = $permissions['document author'] + array(
    'administer menu',
    'create loop_documents_collection content',
    'delete any image files',
    'delete any loop_documents_collection content',
    'delete any loop_documents_document content',
    'edit any image files',
    'edit any loop_documents_collection content',
    'edit any loop_documents_document content',
    'menu view unpublished',
  );

  $permissions['administrator'] = $permissions['document collections editor'];

  return isset($permissions[$role]) ? $permissions[$role] : NULL;
}
