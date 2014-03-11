<?php
/**
 * @file
 * loop_notification.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_notification_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function loop_notification_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function loop_notification_flag_default_flags() {
  $flags = array();
  // Exported flag: "Message read".
  $flags['message_read'] = array(
    'entity_type' => 'message',
    'title' => 'Message read',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Mark as read',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Mark as unread',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => 'Læst',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'diff_standard' => 0,
      'message_notify_email_subject' => 0,
      'message_notify_email_body' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'module' => 'loop_notification',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_default_message_type().
 */
function loop_notification_default_message_type() {
  $items = array();
  $items['comment_added_to_post'] = entity_import('message_type', '{
    "name" : "comment_added_to_post",
    "description" : "Comment added to post",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "en",
    "arguments" : null,
    "message_text" : { "en" : [
        {
          "value" : "\\u003Cp\\u003ENyt svar p\\u00e5 sp\\u00f8rgsm\\u00e5let \\u0026quot;\\u003Ca href=\\u0022\\/node\\/[message:field-message-node-reference:nid]\\u0022\\u003E[message:field-message-node-reference:title]\\u003C\\/a\\u003E\\u0026quot;\\u003C\\/p\\u003E",
          "format" : "editor",
          "safe_value" : "\\u003Cp\\u003ENyt svar p\\u00e5 sp\\u00f8rgsm\\u00e5let \\u0022\\u003Ca href=\\u0022\\/node\\/[message:field-message-node-reference:nid]\\u0022\\u003E[message:field-message-node-reference:title]\\u003C\\/a\\u003E\\u0022\\u003C\\/p\\u003E\\n"
        },
        {
          "value" : "\\u003Cp\\u003EDer er kommet et nyt svar til sp\\u00f8rgsm\\u00e5let:\\u003Cspan style=\\u0022line-height: 1.538em;\\u0022\\u003E\\u0026nbsp;\\u0026quot;\\u003C\\/span\\u003E\\u003Ca href=\\u0022\\/node\\/[message:field-message-node-reference:nid]\\u0022 style=\\u0022line-height: 1.538em;\\u0022\\u003E[message:field-message-node-reference:title]\\u003C\\/a\\u003E\\u003Cspan style=\\u0022line-height: 1.538em;\\u0022\\u003E\\u0026quot;\\u003C\\/span\\u003E\\u003C\\/p\\u003E\\u003Cp\\u003EMvh LOOP\\u003C\\/p\\u003E\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\u003Cp\\u003EDette er en automatisk besked sendt fra\\u0026nbsp;\\u003Ca style=\\u0022line-height: 1.538em; white-space: nowrap;\\u0022 title=\\u0022Insert this token into your form\\u0022\\u003E[site:url]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
          "format" : "editor",
          "safe_value" : "\\u003Cp\\u003EDer er kommet et nyt svar til sp\\u00f8rgsm\\u00e5let:\\u00a0\\u0022\\u003Ca href=\\u0022\\/node\\/[message:field-message-node-reference:nid]\\u0022\\u003E[message:field-message-node-reference:title]\\u003C\\/a\\u003E\\u0022Mvh LOOP\\u00a0Dette er en automatisk besked sendt fra\\u00a0\\u003Ca title=\\u0022Insert this token into your form\\u0022\\u003E[site:url]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
