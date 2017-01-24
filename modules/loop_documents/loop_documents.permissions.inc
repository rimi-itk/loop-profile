<?php

/**
 * @file
 * Permission settings for the loop_documents module.
 */

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
