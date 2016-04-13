<?php

/**
 * @file
 * Contains SearchApiSearchNodeService.
 *
 * This services is used to index data at the search node.
 */

/**
 * Indexes and searches items using search node.
 */
class SearchApiSearchNodeService extends SearchApiAbstractService {

  protected $connection;

  /**
   * {@inheritdoc}
   */
  public function __construct(SearchApiServer $server) {
    parent::__construct($server);

    // Get connection to the client.
    if (isset($this->options['host'])) {
      // Check for overridden api-key and host from settings.php
      $apikey = variable_get('search_api_' . $server->machine_name . '_apikey', $this->options['apikey']);
      $host = variable_get('search_api_' . $server->machine_name . '_host', $this->options['host']);

      $this->connection = new SearchNodeClient($host, $apikey);
      $this->connection->authenticate();
    }
  }

  /**
   * {@inheritdoc}
   */
  public function configurationForm(array $form, array &$form_state) {
    $form['host'] = array(
      '#type' => 'textfield',
      '#title' => t('Host address'),
      '#description' => t('The location of the hosted search node to use.'),
      '#required' => TRUE,
      '#default_value' => isset($this->options['host']) ? $this->options['host'] : 'https://localhost',
    );

    $form['apikey'] = array(
      '#type' => 'textfield',
      '#title' => t('API key (write access)'),
      '#description' => t('API used to index data into search node. It has write access and limited to index data based on IP address.'),
      '#required' => TRUE,
      '#default_value' => isset($this->options['apikey']) ? $this->options['apikey'] : '',
    );

    $form['apikey_readonly'] = array(
      '#type' => 'textfield',
      '#title' => t('API key (read only)'),
      '#description' => t('This API key is used in the Javascript front-end and is limited to search only.'),
      '#required' => TRUE,
      '#default_value' => isset($this->options['apikey_readonly']) ? $this->options['apikey_readonly'] : '',
    );

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function supportsFeature($feature) {
    $supported = drupal_map_assoc(array(
      'search_api_service_extra',
    ));

    if (isset($supported[$feature])) {
      return TRUE;
    }

    return parent::supportsFeature($feature);
  }

  /**
   * {@inheritdoc}
   */
  public function getExtraInformation() {
    $info = array();

    // Test that authentication is working.
    $result = $this->connection->authenticate();
    if ($result['status'] != 200) {
      $info[] = array(
        'label' => t('Authentication status'),
        'info' => $result['message'],
        'status' => 'error',
      );
    }
    else {
      $info[] = array(
        'label' => t('Authentication status'),
        'info' => t('Connected'),
        'status' => 'ok',
      );
    }

    // Get available indexes for that API key.
    $indexes = $this->connection->getIndexes();
    if (empty($indexes)) {
      $info[] = array(
        'label' => t('Indexes'),
        'info' => t('No indexes found with that API key.'),
        'status' => 'error',
      );
    }
    else {
      foreach ($indexes as $index) {
        $info[] = array(
          'label' => t('Index: @name (%tag)', array('@name' => $index->name, '%tag' => $index->tag)),
          'info' => $index->index,
          'status' => 'ok',
        );
      }

    }

    return $info;
  }

  /**
   * {@inheritdoc}
   */
  public function indexItems(SearchApiIndex $index, array $items) {
    $indexed = array();

    $search_node_index = $index->options['search_node_indexes'];
    if (!empty($search_node_index)) {
      foreach ($items as $id => $item) {
        // Filter the items to better match the value search node works.
        $filteredItem = $this->filterOutValue($item);

        // Check if content type have been set.
        if (!isset($filteredItem['type'])) {
          drupal_set_message('The index content did not have a type, so defaults to "entity"', 'warning', FALSE);
          $filteredItem['type'] = 'entity';
        }

        // Allow others to alter the filtered values.
        drupal_alter('search_node_filtered_item', $filteredItem);

        // Add it to the index.
        $result = $this->connection->add($search_node_index, $filteredItem['type'], $id, json_encode($filteredItem));
        if ($result['success']){
          // Mark the content as indexed.
          $indexed[] = $id;
        }
        else {
          watchdog('search_api_db', $result['message'], NULL, WATCHDOG_ERROR);
        }
      }
    }
    else {
      throw new SearchApiException('No search node index have been selected.');
    }

    return $indexed;
  }

  /**
   * {@inheritdoc}
   */
  public function deleteItems($ids = 'all', SearchApiIndex $index = NULL) {
    if ($index) {
      $search_node_index = $index->options['search_node_indexes'];
      if (!empty($search_node_index)) {
        if ($ids == 'all') {
          $this->connection->flush($search_node_index);
        }
        else {
          // The $ids will be an array when delete items.
          foreach ($ids as $id) {
            $deleted = FALSE;
            $type = 'unknown';

            // As search api don't provides an entity during deletion, we need
            // to try them all.
            if (isset($index->options['datasource'])) {
              foreach ($index->options['datasource']['bundles'] as $type) {
                $deleted = $this->connection->remove($search_node_index, $type, $id);
                if ($deleted) {
                  // No need to try and delete with other types.
                  break;
                }
              }
            }

            // All types tried, so check if it was delete.
            if (!$deleted) {
              watchdog('search_api_db', 'Unable to delete item with %id and type %type.', array('%id' => $id, '%type' => $type), WATCHDOG_WARNING);
            }
          }
        }
      }
      else {
        throw new SearchApiException('No search node index have been selected.');
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function query(SearchApiIndex $index, $options = array()) {
    return new SearchApiQuery($index, $options);
  }

  /**
   * {@inheritdoc}
   *
   * @TODO: Build search without Angular support.
   *
   *
   * An associative array containing the search results. The following keys
   *   are standardized:
   *   - 'result count': The overall number of results for this query, without
   *     range restrictions. Might be approximated, for large numbers, or
   *     skipped entirely if the "skip result count" option was set on this
   *     query.
   *   - results: An array of results, ordered as specified. The array keys are
   *     the items' IDs, values are arrays containing the following keys:
   *     - id: The item's ID.
   *     - score: A float measuring how well the item fits the search.
   *     - fields: (optional) If set, an array containing some field values
   *       already ready-to-use. This allows search engines (or postprocessors)
   *       to store extracted fields so other modules don't have to extract them
   *       again. This fields should always be checked by modules that want to
   *       use field contents of the result items.
   *     - entity: (optional) If set, the fully loaded result item. This field
   *       should always be used by modules using search results, to avoid
   *       duplicate item loads.
   *     - excerpt: (optional) If set, an HTML text containing highlighted
   *       portions of the fulltext that match the query.
   *   - warnings: A numeric array of translated warning messages that may be
   *     displayed to the user.
   *   - ignored: A numeric array of search keys that were ignored for this
   *     search (e.g., because of being too short or stop words).
   *   - performance: An associative array with the time taken (as floats, in
   *     seconds) for specific parts of the search execution:
   *     - complete: The complete runtime of the query.
   *     - hooks: Hook invocations and other client-side preprocessing.
   *     - preprocessing: Preprocessing of the service class.
   *     - execution: The actual query to the search server, in whatever form.
   *     - postprocessing: Preparing the results for returning.
   *   Additional metadata may be returned in other keys. Only 'result count'
   *   and 'result' always have to be set, all other entries are optional.
   */
  public function search(SearchApiQueryInterface $query) {
    return array(
      'result count' => 0,
      'results' => array(),
    );
  }

  /**
   * Get taxonomy names based on ids.
   *
   * @param array $tids
   *   Taxonomy ids to translate to names.
   *
   * @return array
   *   The names of the tids given.
   */
  private function addTaxonomyNames(array $tids) {
    $terms = array();
    foreach ($tids as $tid) {
      $term = taxonomy_term_load($tid);
      if ($term) {
        array_push($terms, $term->name);
      }
    }

    return $terms;
  }

  /**
   * Create ULR from file id.
   *
   * @TODO: Support multi value file fields.
   *
   * @param $fids
   *
   * @return string
   */
  private function addFileUrl($fids) {
    // Search node would expect and object as default for files.
    $files = array(
      'fid' => '',
      'url' => '',
    );

    if (!empty($fids)) {
      $file = file_load(reset($fids));
      $files = array(
        'fid' => reset($fids),
        'url' => file_create_url($file->uri),
      );
    }

    return $files;
  }

  /**
   * Filter out everything but the value.
   *
   * We do this as the field metadata is handled in the search node index
   * configuration, so to simplify the search queries.
   *
   * @param array $item
   *   Item to filter away metadata.
   *
   * @return array mixed
   *   The filter item to index.
   */
  private function filterOutValue(array $item) {
    foreach ($item as $key => $field) {
      $type = isset($field['entity_type']) ? $field['entity_type'] : $field['type'];
      switch ($type) {
        case 'taxonomy_term':
          $tids = is_array($field['value']) ? $field['value'] : array($field['value']);
          $item[$key] = $this->addTaxonomyNames($tids);
          break;

        case 'file':
          $item[$key] = $this->addFileUrl($field['value']);
          break;

        default:
          $item[$key] = $field['value'];
      }
    }

    return $item;
  }
}
