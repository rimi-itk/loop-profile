<?php
/**
 * @file
 * loop_taxonomy.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function loop_taxonomy_default_rules_configuration() {
  $items = array();
  $items['rules_add_flag_to_taxonomy_term'] = entity_import('rules_config', '{ "rules_add_flag_to_taxonomy_term" : {
      "LABEL" : "Add flag to taxonomy term",
      "PLUGIN" : "action set",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag" ],
      "USES VARIABLES" : { "term" : { "label" : "Term", "type" : "taxonomy_term" } },
      "ACTION SET" : [
        { "flag_flagtaxonomy_term" : {
            "flag" : "subscribe_term",
            "taxonomy_term" : [ "term" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : "0"
          }
        }
      ]
    }
  }');
  $items['rules_remove_flag_from_taxonomy_term'] = entity_import('rules_config', '{ "rules_remove_flag_from_taxonomy_term" : {
      "LABEL" : "Remove flag from taxonomy term",
      "PLUGIN" : "action set",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag" ],
      "USES VARIABLES" : { "term" : { "label" : "Term", "type" : "taxonomy_term" } },
      "ACTION SET" : [
        { "flag_unflagtaxonomy_term" : {
            "flag" : "subscribe_term",
            "taxonomy_term" : [ "term" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : "0"
          }
        }
      ]
    }
  }');
  return $items;
}
