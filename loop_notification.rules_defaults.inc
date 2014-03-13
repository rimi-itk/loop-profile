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
            "PROVIDE" : { "users" : { "users_who_flagged" : "Users who flagged" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users-who-flagged" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "message",
                    "param_type" : "comment_added_to_post",
                    "param_user" : [ "list-item" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-created:field-message-node-reference" ],
                  "value" : [ "comment:node" ]
                }
              },
              { "entity_save" : { "data" : [ "entity-created" ], "immediate" : 1 } },
              { "component_rules_send_mail" : { "user" : [ "list-item" ], "message" : [ "entity-created" ] } }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_remove_subscription'] = entity_import('rules_config', '{ "rules_remove_subscription" : {
      "LABEL" : "Remove subscription",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Subscriptions" ],
      "REQUIRES" : [ "flag" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : { "node" : { "label" : "node", "type" : "node" } },
      "DO" : [
        { "flag_unflagnode" : {
            "flag" : "subscribe_node",
            "node" : [ "node" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_send_mail'] = entity_import('rules_config', '{ "rules_send_mail" : {
      "LABEL" : "Send mail",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "message_notify" ],
      "ACCESS_EXPOSED" : "1",
      "USES VARIABLES" : {
        "user" : { "label" : "user", "type" : "entity" },
        "message" : { "label" : "message", "type" : "message" }
      },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "user" ], "field" : "message_subscribe_email" } },
        { "data_is" : { "data" : [ "user:message-subscribe-email" ], "value" : 1 } }
      ],
      "DO" : [
        { "message_notify_process" : { "message" : [ "message" ], "mail" : "[message:user:mail]" } }
      ]
    }
  }');
  $items['rules_set_message_read'] = entity_import('rules_config', '{ "rules_set_message_read" : {
      "LABEL" : "Set message read",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "notification" ],
      "REQUIRES" : [ "flag" ],
      "USES VARIABLES" : { "message_read" : { "label" : "Set message read", "type" : "message" } },
      "DO" : [
        { "flag_flagmessage" : {
            "flag" : "message_read",
            "message" : [ "message-read" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  return $items;
}
