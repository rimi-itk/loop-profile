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
  $field_group->identifier = 'group_description|user|user|default';
  $field_group->group_name = 'group_description';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Description',
    'weight' => '5',
    'children' => array(
      0 => 'field_biography',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Description',
      'instance_settings' => array(
        'classes' => 'user-profile-module--field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_description|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_job_title|user|user|default';
  $field_group->group_name = 'group_job_title';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Job title',
    'weight' => '2',
    'children' => array(
      0 => 'field_job_title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Job title',
      'instance_settings' => array(
        'classes' => 'user-profile-module--field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_job_title|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_location|user|user|default';
  $field_group->group_name = 'group_location';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '4',
    'children' => array(
      0 => 'field_location',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Location',
      'instance_settings' => array(
        'classes' => 'user-profile-module--field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_location|user|user|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_location|user|user|form';
  $field_group->group_name = 'group_location';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_personal_information';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '48',
    'children' => array(
      0 => 'field_location_place',
      1 => 'field_location_address',
      2 => 'field_location_postal_code',
      3 => 'field_location_city',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Location',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-location field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_location|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal_information|user|user|default';
  $field_group->group_name = 'group_personal_information';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal information',
    'weight' => '1',
    'children' => array(
      0 => 'field_first_name',
      1 => 'field_last_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Personal information',
      'instance_settings' => array(
        'classes' => 'user-profile-module--field-group-fieldset-personal-info',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_personal_information|user|user|default'] = $field_group;

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
      0 => 'field_biography',
      1 => 'field_first_name',
      2 => 'field_job_title',
      3 => 'field_last_name',
      4 => 'field_profession',
      5 => 'group_location',
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

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profession|user|user|default';
  $field_group->group_name = 'group_profession';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Profession',
    'weight' => '3',
    'children' => array(
      0 => 'field_profession',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Profession',
      'instance_settings' => array(
        'classes' => 'user-profile-module--field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_profession|user|user|default'] = $field_group;

  return $export;
}
