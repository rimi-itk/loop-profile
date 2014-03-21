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
  $items['rules_send_mail_on_message_created'] = entity_import('rules_config', '{ "rules_send_mail_on_message_created" : {
      "LABEL" : "Send mail on message created",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "mimemail" ],
      "USES VARIABLES" : {
        "node" : { "label" : "node", "type" : "node" },
        "user" : { "label" : "user", "type" : "user" },
        "message" : { "label" : "message", "type" : "message" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "user:uid" ], "value" : [ "site:current-user:uid" ] } }
      ],
      "DO" : [
        { "mimemail" : {
            "key" : "Mail on message creation",
            "to" : "[message:user:mail]",
            "from_mail" : "[site:mail]",
            "subject" : "Nyt svar til sp\\u00f8rgsm\\u00e5let [node:title]",
            "body" : "\\u003Ch2\\u003ENyt svar til et sp\\u00f8rgsm\\u00e5let [node:title]\\u003C\\/h2\\u003E\\r\\n\\u003Cp\\u003EK\\u00e6re [user:field-first-name] [user:field-last-name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EDer er kommet nyt svar til sp\\u00f8rgsm\\u00e5let \\u003Ca href=\\u0022\\/node\\/[node:nid]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EMed venlig hilsen\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[site:name]\\u003C\\/p\\u003E\\r\\n\\u003C\\/br\\u003E\\r\\n\\u003C\\/br\\u003E\\r\\n\\u003Cp\\u003EDette er en automatisk meddelelse fra [site:url]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EDu kan styre dine abonnementer fra din \\u003Ca href=\\u0022\\/user\\/[user:uid]\\/subscriptions\\u0022\\u003Ebrugerprofil\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
            "attachments" : [ "" ],
            "language" : [ "" ]
          }
        }
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
