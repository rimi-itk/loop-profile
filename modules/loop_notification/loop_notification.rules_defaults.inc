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
  $items['loop_notification_autosubscribe_node_comment_author'] = entity_import('rules_config', '{ "loop_notification_autosubscribe_node_comment_author" : {
      "LABEL" : "Autosubscribe node comment author",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "rules", "comment" ],
      "ON" : { "comment_insert" : [] },
      "DO" : [
        { "flag_flagnode" : {
            "flag" : "subscribe_node",
            "node" : [ "comment:node" ],
            "flagging_user" : [ "comment:author" ],
            "permission_check" : "0"
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "node", "id" : [ "comment:node:nid" ] },
            "PROVIDE" : { "entity_fetched" : { "entity_fetched" : "Fetched entity" } }
          }
        }
      ]
    }
  }');
  $items['loop_notification_create_notification_on_comment_edit'] = entity_import('rules_config', '{ "loop_notification_create_notification_on_comment_edit" : {
      "LABEL" : "Create notification on comment edit",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "active_user_object" : { "label" : "Active user objject", "type" : "user" },
        "comment_author" : { "label" : "comment_author", "type" : "user" },
        "comment" : { "label" : "comment", "type" : "comment" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } },
            "IF" : [
              { "NOT data_is" : { "data" : [ "active-user-object" ], "value" : [ "comment-author" ] } }
            ],
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "message",
                    "param_type" : "comment_added_to_post",
                    "param_user" : [ "active-user-object" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-created:field-message-node-reference" ],
                  "value" : [ "comment:node" ]
                }
              },
              { "entity_save" : { "data" : [ "entity-created" ], "immediate" : 1 } }
            ],
            "LABEL" : "Create notification"
          }
        }
      ]
    }
  }');
  $items['loop_notification_create_notification_on_node_create'] = entity_import('rules_config', '{ "loop_notification_create_notification_on_node_create" : {
      "LABEL" : "Create notification on node create",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "active_user_object" : { "label" : "Active user objject", "type" : "user" },
        "node_author" : { "label" : "node_author", "type" : "user" },
        "node" : { "label" : "node", "type" : "node" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } },
            "IF" : [
              { "NOT data_is" : { "data" : [ "active-user-object" ], "value" : [ "node-author" ] } }
            ],
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "message",
                    "param_type" : "node_added",
                    "param_user" : [ "active-user-object" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-created:field-message-node-reference" ],
                  "value" : [ "node" ]
                }
              },
              { "entity_save" : { "data" : [ "entity-created" ], "immediate" : 1 } }
            ],
            "LABEL" : "Create notification"
          }
        }
      ]
    }
  }');
  $items['loop_notification_create_notification_on_node_edit'] = entity_import('rules_config', '{ "loop_notification_create_notification_on_node_edit" : {
      "LABEL" : "Create notification on node edit",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "active_user_object" : { "label" : "Active user objject", "type" : "user" },
        "node_author" : { "label" : "node_author", "type" : "user" },
        "node" : { "label" : "node", "type" : "node" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } },
            "IF" : [
              { "NOT data_is" : { "data" : [ "active-user-object" ], "value" : [ "node-author" ] } }
            ],
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "message",
                    "param_type" : "node_edited",
                    "param_user" : [ "active-user-object" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-created:field-message-node-reference" ],
                  "value" : [ "node" ]
                }
              },
              { "entity_save" : { "data" : [ "entity-created" ], "immediate" : 1 } }
            ],
            "LABEL" : "Create notification"
          }
        }
      ]
    }
  }');
  $items['loop_notification_send_mail'] = entity_import('rules_config', '{ "loop_notification_send_mail" : {
      "LABEL" : "Send mail to subscribers",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "mimemail" ],
      "USES VARIABLES" : {
        "node" : { "label" : "node", "type" : "node" },
        "user" : { "label" : "user", "type" : "user" },
        "comment" : { "label" : "comment", "type" : "comment" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "user:uid" ], "value" : [ "comment:author:uid" ] } }
      ],
      "DO" : [
        { "mimemail" : {
            "USING" : {
              "key" : "Mail on message creation",
              "to" : "[user:mail]",
              "from_mail" : "[site:mail]",
              "subject" : "Nyt svar til sp\\u00f8rgsm\\u00e5let [node:title]",
              "body" : "\\u003Ch2\\u003ENyt svar til sp\\u00f8rgsm\\u00e5let [node:title]\\u003C\\/h2\\u003E\\r\\n\\u003Cp\\u003EK\\u00e6re [user:field-first-name] [user:field-last-name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EDer er kommet nyt svar til sp\\u00f8rgsm\\u00e5let \\u003Ca href=\\u0022\\/node\\/[node:nid]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EMed venlig hilsen\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[site:name]\\u003C\\/p\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\nDette er en automatisk meddelelse fra Loop, og kan ikke besvares.\\u003Cbr \\/\\u003E\\r\\nDu kan styre dine abonnementer fra din brugerprofil\\u003Cbr \\/\\u003E\\r\\nHUSK! Du ikke kan f\\u00e5 adgang via linket i mailen, hvis det er mere end 21 dage siden du har logget ind i Loop.\\u003Cbr \\/\\u003E\\r\\nDu kan altid hurtigt logge ind i Loop via knappen i bogm\\u00e6rke-baren i Internet Explorer, eller via linket p\\u00e5 portalen: \\u003Ca href=\\u0022http:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u0022\\u003Ehttp:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u003C\\/a\\u003E\\r\\n",
              "attachments" : [ "" ],
              "language" : [ "" ]
            },
            "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
          }
        }
      ]
    }
  }');
  $items['loop_notification_send_mail_to_subscribers_on_comment_edit'] = entity_import('rules_config', '{ "loop_notification_send_mail_to_subscribers_on_comment_edit" : {
      "LABEL" : "Send mail to subscribers on comment edit",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "mimemail" ],
      "USES VARIABLES" : {
        "node" : { "label" : "node", "type" : "node" },
        "user" : { "label" : "user", "type" : "user" },
        "comment" : { "label" : "comment", "type" : "comment" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "user:uid" ], "value" : [ "comment:author:uid" ] } }
      ],
      "DO" : [
        { "mimemail" : {
            "USING" : {
              "key" : "Mail on message creation",
              "to" : "[user:mail]",
              "from_mail" : "[site:mail]",
              "subject" : "Et svar til sp\\u00f8rgsm\\u00e5let [node:title] er blevet \\u00e6ndret",
              "body" : "\\u003Ch2\\u003EEt svar til sp\\u00f8rgsm\\u00e5let [node:title] er blevet \\u00e6ndret\\u003C\\/h2\\u003E\\r\\n\\u003Cp\\u003EK\\u00e6re [user:field-first-name] [user:field-last-name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EEt svar til sp\\u00f8rgsm\\u00e5let \\u003Ca href=\\u0022\\/node\\/[node:nid]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E er blevet \\u00e6ndret.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003ENyt svar: [comment:body]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EMed venlig hilsen\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[site:name]\\u003C\\/p\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\nDette er en automatisk meddelelse fra Loop, og kan ikke besvares.\\u003Cbr \\/\\u003E\\r\\nDu kan styre dine abonnementer fra din brugerprofil\\u003Cbr \\/\\u003E\\r\\nHUSK! Du ikke kan f\\u00e5 adgang via linket i mailen, hvis det er mere end 21 dage siden du har logget ind i Loop.\\u003Cbr \\/\\u003E\\r\\nDu kan altid hurtigt logge ind i Loop via knappen i bogm\\u00e6rke-baren i Internet Explorer, eller via linket p\\u00e5 portalen: \\u003Ca href=\\u0022http:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u0022\\u003Ehttp:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u003C\\/a\\u003E\\r\\n",
              "attachments" : [ "" ],
              "language" : [ "" ]
            },
            "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
          }
        }
      ]
    }
  }');
  $items['loop_notification_send_mail_to_subscribers_on_node_create'] = entity_import('rules_config', '{ "loop_notification_send_mail_to_subscribers_on_node_create" : {
      "LABEL" : "Send mail to subscribers on node create",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "mimemail" ],
      "USES VARIABLES" : {
        "node" : { "label" : "node", "type" : "node" },
        "user" : { "label" : "user", "type" : "user" },
        "comment" : { "label" : "comment", "type" : "comment" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "user:uid" ], "value" : [ "node:author:uid" ] } }
      ],
      "DO" : [
        { "mimemail" : {
            "USING" : {
              "key" : "Mail on message creation",
              "to" : "[user:mail]",
              "from_mail" : "[site:mail]",
              "subject" : "Nyt sp\\u00f8rgsm\\u00e5l indenfor et emne du f\\u00f8lger.",
              "body" : "\\u003Ch2\\u003ENyt sp\\u00f8rgsm\\u00e5l oprettet [node:title] indenfor et emne du f\\u00f8lger\\u003C\\/h2\\u003E\\r\\n\\u003Cp\\u003EK\\u00e6re [user:field-first-name] [user:field-last-name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EDer er kommet et nyt sp\\u00f8rgsm\\u00e5l indenfor et emne du f\\u00f8lger: \\u003Ca href=\\u0022\\/node\\/[node:nid]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EMed venlig hilsen\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[site:name]\\u003C\\/p\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\nDette er en automatisk meddelelse fra Loop, og kan ikke besvares.\\u003Cbr \\/\\u003E\\r\\nDu kan styre dine abonnementer fra din brugerprofil\\u003Cbr \\/\\u003E\\r\\nHUSK! Du ikke kan f\\u00e5 adgang via linket i mailen, hvis det er mere end 21 dage siden du har logget ind i Loop.\\u003Cbr \\/\\u003E\\r\\nDu kan altid hurtigt logge ind i Loop via knappen i bogm\\u00e6rke-baren i Internet Explorer, eller via linket p\\u00e5 portalen: \\u003Ca href=\\u0022http:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u0022\\u003Ehttp:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u003C\\/a\\u003E",
              "attachments" : [ "" ],
              "language" : [ "" ]
            },
            "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
          }
        }
      ]
    }
  }');
  $items['loop_notification_send_mail_to_subscribers_on_node_edit'] = entity_import('rules_config', '{ "loop_notification_send_mail_to_subscribers_on_node_edit" : {
      "LABEL" : "Send mail to subscribers on node edit",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "mimemail" ],
      "USES VARIABLES" : {
        "node" : { "label" : "node", "type" : "node" },
        "user" : { "label" : "user", "type" : "user" },
        "comment" : { "label" : "comment", "type" : "comment" }
      },
      "IF" : [
        { "NOT data_is" : { "data" : [ "user:uid" ], "value" : [ "node:author:uid" ] } }
      ],
      "DO" : [
        { "mimemail" : {
            "USING" : {
              "key" : "Mail on message creation",
              "to" : "[user:mail]",
              "from_mail" : "[site:mail]",
              "subject" : "Nyt svar til sp\\u00f8rgsm\\u00e5let [node:title]",
              "body" : "\\u003Ch2\\u003EEt sp\\u00f8rgsm\\u00e5l er blevet \\u00e6ndret: [node:title]\\u003C\\/h2\\u003E\\r\\n\\u003Cp\\u003EK\\u00e6re [user:field-first-name] [user:field-last-name]\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EEt sp\\u00f8rgsm\\u00e5l du f\\u00f8lger er blevet \\u00e6ndret \\u003Ca href=\\u0022\\/node\\/[node:nid]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EMed venlig hilsen\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[site:name]\\u003C\\/p\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\n\\u003Cbr \\/\\u003E\\r\\nDette er en automatisk meddelelse fra Loop, og kan ikke besvares.\\u003Cbr \\/\\u003E\\r\\nDu kan styre dine abonnementer fra din brugerprofil\\u003Cbr\\u003E\\r\\nHUSK! Du ikke kan f\\u00e5 adgang via linket i mailen, hvis det er mere end 21 dage siden du har logget ind i Loop.\\u003Cbr \\/\\u003E\\r\\nDu kan altid hurtigt logge ind i Loop via knappen i bogm\\u00e6rke-baren i Internet Explorer, eller via linket p\\u00e5 portalen: \\u003Ca href=\\u0022http:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u0022\\u003Ehttp:\\/\\/www.sundhedogomsorg.dk\\/da\\/Vaerktoejer\\/LOOP.aspx\\u003C\\/a\\u003E\\r\\n\\r\\n",
              "attachments" : [ "" ],
              "language" : [ "" ]
            },
            "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
          }
        }
      ]
    }
  }');
  $items['rules_autosubscribe_node_post_author'] = entity_import('rules_config', '{ "rules_autosubscribe_node_post_author" : {
      "LABEL" : "Autosubscribe node post author",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "rules" ],
      "ON" : { "node_insert--post" : { "bundle" : "post" } },
      "DO" : [
        { "flag_flagnode" : {
            "flag" : "subscribe_node",
            "node" : [ "node" ],
            "flagging_user" : [ "node:author" ],
            "permission_check" : 0
          }
        }
      ]
    }
  }');
  $items['rules_create_notification'] = entity_import('rules_config', '{ "rules_create_notification" : {
      "LABEL" : "Create notification on comment create",
      "PLUGIN" : "rule set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "active_user_object" : { "label" : "Active user objject", "type" : "user" },
        "comment_author" : { "label" : "comment_author", "type" : "user" },
        "comment" : { "label" : "comment", "type" : "comment" }
      },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } },
            "IF" : [
              { "NOT data_is" : { "data" : [ "active-user-object" ], "value" : [ "comment-author" ] } }
            ],
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "message",
                    "param_type" : "comment_added_to_post",
                    "param_user" : [ "active-user-object" ]
                  },
                  "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
                }
              },
              { "data_set" : {
                  "data" : [ "entity-created:field-message-node-reference" ],
                  "value" : [ "comment:node" ]
                }
              },
              { "entity_save" : { "data" : [ "entity-created" ], "immediate" : 1 } }
            ],
            "LABEL" : "Create notification"
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
