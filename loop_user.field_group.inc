<?php
/**
 * @file
 * loop_user.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function loop_user_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal_information|user|user|form';
  $field_group->group_name = 'group_personal_information';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal information',
    'weight' => '1',
    'children' => array(
      0 => 'field_profession',
      1 => 'field_first_name',
      2 => 'field_last_name',
      3 => 'field_job_title',
      4 => 'field_location',
      5 => 'field_biography',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-personal-information field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_personal_information|user|user|form'] = $field_group;

  return $export;
}
