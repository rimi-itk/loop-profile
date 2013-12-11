<?php
/**
 * @file
 * loop_user.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function loop_user_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_profession'
  $field_instances['user-user-field_profession'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_profession',
    'label' => 'Profession',
    'required' => 1,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 47,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Profession');

  return $field_instances;
}
