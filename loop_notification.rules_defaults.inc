<?php
/**
 * @file
 * loop_notification.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function loop_notification_default_rules_configuration() {
  $items = array();
  $items['rules_create_send_message_on_comment_creation'] = entity_import('rules_config', '{ "rules_create_send_message_on_comment_creation" : {
      "LABEL" : "Create\\/send message on comment creation",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "rules", "comment" ],
      "ON" : { "comment_insert" : [] },
      "DO" : [
        { "flag_fetch_users_node" : {
            "USING" : { "flag" : "subscribe_node", "node" : [ "comment:node" ] },
            "PROVIDE" : { "users" : { "users" : "Users who flagged" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "message",
                    "param_type" : "yet_another",
                    "param_user" : [ "list-item" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
                }
              },
              { "entity_save" : { "data" : [ "entity-created" ] } }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
