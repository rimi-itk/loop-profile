<?php

/**
 * @file
 * Contains the SearchApiAlterRoleFilter class.
 */

/**
 * Data alteration that filters out users based on their role.
 */
class SearchNodeLocationFilter extends SearchApiAbstractAlterCallback {

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
    foreach ($items as $item) {
      if (isset($item->locations) && count($item->locations)) {
        $location = reset($item->locations);

        // Check if location is valid.
        if ($location['latitude'] == '0.000000' && $location['longitude'] == '0.000000') {
          // This is normally because geo-encoding have failed. So just go to
          // the next one.
          continue;
        }

        $name = $this->options['field_name'];
        $item->$name = array(
          'lat' => $location['latitude'],
          'lon' => $location['longitude'],
        );
      }
    }
  }

  /**
   * Overrides SearchApiAbstractAlterCallback::configurationForm().
   */
  public function configurationForm() {
    $form = array();

    $form['field_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Field name'),
      '#default_value' => isset($this->options['field_name']) ? $this->options['field_name'] : '',
      '#required' => FALSE,
    );

    return $form;
  }

  /**
   * Add field to items, so it's available in the indexer.
   */
  public function propertyInfo() {
    $ret = array();

    if (isset($this->options['field_name'])) {
      $ret[$this->options['field_name']] = array(
        'label' => 'Location (lat/lon)',
        'description' => t('Lat/lon from the location module'),
        'type' => 'string',
      );
    }

    return $ret;
  }
}
