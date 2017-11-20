<?php
/**
 * @file
 * loop_notification.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function loop_notification_filter_default_formats() {
  $formats = array();

  // Exported format: Mime mail filter.
  $formats['mime_mail_filter'] = array(
    'format' => 'mime_mail_filter',
    'name' => 'Mime mail filter',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<h2> <p> <br> <a>',
          'filter_html_help' => 0,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
