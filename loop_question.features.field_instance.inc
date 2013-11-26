<?php
/**
 * @file
 * loop_question.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function loop_question_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-question-field_keyword'
  $field_instances['node-question-field_keyword'] = array(
    'bundle' => 'question',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Type in keyword(s).',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_keyword',
    'label' => 'Keyword',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-question-field_subject'
  $field_instances['node-question-field_subject'] = array(
    'bundle' => 'question',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Select a subject.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_subject',
    'label' => 'Subject',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Keyword');
  t('Select a subject.');
  t('Subject');
  t('Type in keyword(s).');

  return $field_instances;
}
