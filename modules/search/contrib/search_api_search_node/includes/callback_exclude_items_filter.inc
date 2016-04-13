<?php

/**
 * @file
 * Contains the SearchApiAlterRoleFilter class.
 */

/**
 * Data alteration that filters out users based on their role.
 */
class SearchNodeExcludeItemsFilter extends SearchApiAbstractAlterCallback {

  /**
   * Overrides SearchApiAbstractAlterCallback::supportsIndex().
   *
   */
  public function supportsIndex(SearchApiIndex $index) {
    return TRUE;
  }

  /**
   * Implements SearchApiAlterCallbackInterface::alterItems().
   */
  public function alterItems(array &$items) {
    $fields = $this->options['fields'];
    $values = explode(PHP_EOL, $fields['values']);

    foreach ($items as $id => $item) {
      // Check if field is empty and goto the next item if it is.
      if (empty($item->$fields['name'])) {
        continue;
      }

      // Get field value.
      $field_value = is_string($item->$fields['name']) ? $item->$fields['name'] : FALSE;
      if ($field_value === FALSE) {
        $field_value = isset($field_name[LANGUAGE_NONE]['value']) ? $field_name[LANGUAGE_NONE]['value'] : FALSE;
      }

      // Check if item field has that value.
      if ($field_value) {
        foreach ($values as $value) {
          if (preg_match('/' . $value . '/s', $field_value, $m)) {
            unset($items[$id]);
          }
        }
      }
    }
  }

  /**
   * Overrides SearchApiAbstractAlterCallback::configurationForm().
   *
   * Add option for the roles to include/exclude.
   */
  public function configurationForm() {
    $fields = array();
    $form = array();

    // Get fields and filter for the current index.
    $index = $this->index;
    foreach ($index->options['fields'] as $field => $options) {
      if (isset($options['entity_type']) && $options['entity_type'] == 'taxonomy_term') {
        // Load field.
        $info = field_info_field($field);
        $vocab = taxonomy_vocabulary_machine_name_load($info['settings']['allowed_values'][0]['vocabulary']);
        $fields[$field] = $vocab->name . ' (' . $field .')';
      }
      else {
        // The index save some fields with ":".
        $name = explode(':', $field);
        $fields[$field] = array_shift($name) . ' (' . $field .')';
      }
    }

    $form['fields'] = array(
      '#type' => 'fieldset',
      '#title' => 'Search fields',
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => !empty($this->options['fields']['values']),
    );

    $form['fields']['name'] = array(
      '#type' => 'radios',
      '#title' => t('Search fields'),
      '#options' => $fields,
      '#default_value' => isset($this->options['fields']['name']) ? $this->options['fields']['name'] : '',
    );

    $form['fields']['values'] = array(
      '#type' => 'textarea',
      '#title' => t('Values'),
      '#default_value' => isset($this->options['fields']['values']) ? $this->options['fields']['values'] : '',
      '#description' => t('Enter one matching string per line. Regular expressions may be used.'),
    );

    return $form;
  }

}
