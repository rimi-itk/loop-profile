<?php
/**
 * @file
 * loop_documents.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function loop_documents_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_loop_documents_metadata|node|loop_documents_collection|form';
  $field_group->group_name = 'group_loop_documents_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'loop_documents_collection';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '5',
    'children' => array(
      0 => 'field_loop_documents_approv_date',
      1 => 'field_loop_documents_approver',
      2 => 'field_loop_documents_owner',
      3 => 'field_loop_documents_review_date',
      4 => 'field_loop_documents_version',
      5 => 'field_revision_date',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-loop-documents-metadata field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_loop_documents_metadata|node|loop_documents_collection|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_loop_documents_metadata|node|loop_documents_document|form';
  $field_group->group_name = 'group_loop_documents_metadata';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'loop_documents_document';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Metadata',
    'weight' => '5',
    'children' => array(
      0 => 'field_loop_documents_author',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-loop-documents-metadata field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_loop_documents_metadata|node|loop_documents_document|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Metadata');

  return $field_groups;
}
