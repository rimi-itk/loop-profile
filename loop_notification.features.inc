<?php
/**
 * @file
 * loop_notification.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_notification_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
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
          "value" : "\\u003Cp\\u003ENyt svar p\\u00e5 sp\\u00f8rgsm\\u00e5let \\u0022\\u003Ca href=\\u0022\\/node\\/[message:field-message-node-reference:nid]\\u0022\\u003E[message:field-message-node-reference:title]\\u003C\\/a\\u003E\\u0022\\u003C\\/p\\u003E",
          "format" : "editor",
          "safe_value" : "\\u003Cp\\u003ENyt svar p\\u00e5 sp\\u00f8rgsm\\u00e5let \\u0022\\u003Ca href=\\u0022\\/node\\/[message:field-message-node-reference:nid]\\u0022\\u003E[message:field-message-node-reference:title]\\u003C\\/a\\u003E\\u0022\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
