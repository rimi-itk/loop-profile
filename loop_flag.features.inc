<?php
/**
 * @file
 * loop_flag.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function loop_flag_flag_default_flags() {
  $flags = array();
  // Exported flag: "Ranking".
  $flags['ranking'] = array(
    'entity_type' => 'comment',
    'title' => 'Ranking',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Thumbs up',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Remove thumbs up',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'diff_standard' => 'diff_standard',
      'token' => 'token',
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'api_version' => 3,
    'module' => 'loop_flag',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Subscribe to post".
  $flags['subscribe_node'] = array(
    'entity_type' => 'node',
    'title' => 'Subscribe to post',
    'global' => 0,
    'types' => array(
      0 => 'post',
    ),
    'flag_short' => 'Subscribe',
    'flag_long' => '',
    'flag_message' => 'You are now subscribed to this item.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => '',
    'unflag_message' => 'You are no longer subscribed to this item.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 0,
      'rss' => 0,
      'diff_standard' => 0,
      'token' => 0,
    ),
    'show_as_field' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'message_subscribe',
    'locked' => array(
      'name' => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
