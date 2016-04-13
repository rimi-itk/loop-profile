<?php

/**
 * @file
 * Hooks provided by Search Node page.
 */

/**
 * Allow modules to change the configuration.
 *
 * @param array $config
 *   The complete configuration array before it gets json_encode and injected
 *   into the current page. It's the complete configuration used by the
 *   AngularJS search application.
 */
function hook_search_node_page_configuration_alter(&$config) {
  // Change the search host end-point.
  $config['host'] = 'https://search.com';
}