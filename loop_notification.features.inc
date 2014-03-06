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
          "value" : "\\u003Cp\\u003EA new comment has been added to the question: \\u003Ca href=\\u0022[current-page:url:absolute]\\u0022\\u003E[current-page:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThis message is an automated message sent because you are subscribing to updates on the before mentioned question.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Ca href=\\u0022[site:url]\\u0022\\u003E[site:name]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n",
          "format" : "editor",
          "safe_value" : "\\u003Cp\\u003EA new comment has been added to the question: \\u003Ca href=\\u0022absolute]\\u0022\\u003E[current-page:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n\\u003Cp\\u003EThis message is an automated message sent because you are subscribing to updates on the before mentioned question.\\u003C\\/p\\u003E\\n\\u003Cp\\u003E\\u003Ca href=\\u0022url]\\u0022\\u003E[site:name]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
