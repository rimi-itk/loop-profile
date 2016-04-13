<?php
/**
 * @file
 * Client to communicate with the search node.
 *
 * @TODO: Make the client non-drupal dependent.
 */

class SearchNodeClient {

  /**
   * The host where search node is located.
   *
   * @var string
   */
  protected $host = 'https://127.0.0.1';

  /**
   * API key to authenticate with search node.
   *
   * @var string
   */
  protected $apikey;

  /**
   * Authentication token.
   *
   * @var string
   */
  protected $token;

  /**
   * Default constructor.
   *
   * @param $host
   *   The host address for the search node.
   * @param $apikey
   *   The API key.
   */
  public function __construct($host, $apikey) {
    $this->host = $host;
    $this->apikey = $apikey;
  }

  /**
   * Authentication with API key at search node.
   *
   * @return array
   *   Status HTTP code and message from search node.
   */
  public function authenticate() {
    if (empty($this->token)) {
      $request = drupal_http_request($this->host . '/authenticate', array(
        'method' => 'POST',
        'headers' => array(
          'Content-Type' => 'application/json',
        ),
        'data' => json_encode(
          array(
            'apikey' => $this->apikey,
          )
        ),
        'timeout' => 5,
      ));

      switch ($request->code) {
        case 0:
          $responses = array(
            'status' => 500,
            'message' => $request->error,
          );
          break;

        case 200:
          // Store token.
          $this->token = json_decode($request->data)->token;
          $responses = array(
            'status' => $request->code,
            'message' => $request->status_message . ' - ' . $request->data,
          );
          break;

        default:
          watchdog('search_node', 'Unknown response from client: %code', array('%code' => $request->code), WATCHDOG_CRITICAL);
          if (isset($request->status_message)) {
            $responses = array(
              'status' => $request->code,
              'message' => $request->status_message . ' - ' . $request->data,
            );
          }
          else {
            $responses = array(
              'status' => $request->code,
              'message' => t('Unknown search error.'),
            );
          }
          break;
      }

      return $responses;
    }
    else {
      return array(
        'status' => 200,
        'message' => 'Connected',
      );
    }
  }

  /**
   * Get the current token.
   *
   * @return string
   *   The token from last authentication.
   */
  function getToken() {
    return $this->token;
  }

  /**
   * Get indexes available with the current API key.
   *
   * @return array|mixed
   *   The indexes and information about theme.
   */
  public function getIndexes() {
    $indexes = array();

    $request = drupal_http_request($this->host . '/api/indexes', array(
      'method' => 'GET',
      'headers' => array(
        'Content-Type' => 'application/json',
        'Authorization' => 'Bearer ' . $this->token
      ),
    ));

    if ($request->code == 200) {
      $indexes = json_decode($request->data);
    }

    return $indexes;
  }

  /**
   * Add new document to search node.
   *
   * @param $index
   *   The index to add the document to.
   * @param $type
   *   The type of the document.
   * @param $id
   *   The documents ID.
   * @param $data
   *   The document to be added.
   *
   * @return bool
   *   TRUE if it was added else FALSE.
   */
  public function add($index, $type, $id, $data) {
    $request = drupal_http_request($this->host . '/api', array(
      'method' => 'POST',
      'headers' => array(
        'Content-Type' => 'application/json',
        'Authorization' => 'Bearer ' . $this->token
      ),
      'data' => json_encode(
        array(
          'index' => $index,
          'type' => $type,
          'id' => $id,
          'data' => $data,
        )
      )
    ));

    $res = array(
      'success' => TRUE,
      'code' => 200,
      'message' => '',
    );
    switch ($request->code) {
      case 201:
        // Created.
        $res['message'] = t('Content with %id have been added to the index.', array('%id' => $id));
        break;

      case 200:
        // Updated (reindex with new version).
        $res['message'] = t('Content with %id have been updated.', array('%id' => $id));
        break;

      case 500:
        $json = json_decode($request->data);
        $res['message'] = t($json->error);
        $res['success'] = FALSE;
        $res['code'] = 500;
        break;

      default:
        $res['message'] = t('Unknown error: content was not indexed.');
        $res['success'] = FALSE;
        $res['code'] = 500;
        break;
    }

    return $res;
  }

  /**
   * Update document at search node.
   *
   * @param $index
   *   The index to add the document to.
   * @param $type
   *   The type of the document.
   * @param $id
   *   The documents ID.
   * @param $data
   *   The document to be added.
   *
   * @return bool
   *   TRUE if it was updated else FALSE.
   */
  public function update($index, $type, $id, $data) {
    $request = drupal_http_request($this->host . '/api', array(
      'method' => 'PUT',
      'headers' => array(
        'Content-Type' => 'application/json',
        'Authorization' => 'Bearer ' . $this->token
      ),
      'data' => json_encode(
        array(
          'index' => $index,
          'type' => $type,
          'id' => $id,
          'data' => $data,
        )
      )
    ));

    if ($request->code == 200) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Remove document from search node.
   *
   * @param $index
   *   The index to add the document to.
   * @param $type
   *   The type of the document.
   * @param $id
   *   The documents ID.
   *
   * @return bool
   *   TRUE if removed else FALSE.
   */
  public function remove($index, $type, $id) {
    $request = drupal_http_request($this->host . '/api', array(
      'method' => 'DELETE',
      'headers' => array(
        'Content-Type' => 'application/json',
        'Authorization' => 'Bearer ' . $this->token
      ),
      'data' => json_encode(
        array(
          'index' => $index,
          'type' => $type,
          'id' => $id,
        )
      )
    ));

    if ($request->code == 201) {
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Flush index at search node.
   *
   * @param $index
   *   The index to flush.
   *
   * @return bool
   *  TRUE if flushed else FALSE.
   */
  public function flush($index) {
    $request = drupal_http_request($this->host . '/api/' . $index . '/flush', array(
      'method' => 'DELETE',
      'headers' => array(
        'Content-Type' => 'application/json',
        'Authorization' => 'Bearer ' . $this->token
      ),
    ));

    if ($request->code == 200) {
      return TRUE;
    }

    return FALSE;
  }
}