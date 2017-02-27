<?php
/**
 * @file
 * loop_search_node.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_search_node_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function loop_search_node_settings_default_search_api_index() {
  $items = array();
  $items['auto_complete'] = entity_import('search_api_index', '{
    "name" : "auto-complete",
    "machine_name" : "auto_complete",
    "description" : null,
    "server" : "loop_search_node",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "loop_documents_document", "loop_documents_collection", "external_sources", "instruction", "leaf", "post" ] },
      "index_directly" : 0,
      "cron_limit" : "50",
      "search_node_indexes" : "bd6f534b05ab6073e04afef2c67e7e44",
      "fields" : {
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  $items['posts'] = entity_import('search_api_index', '{
    "name" : "Posts",
    "machine_name" : "posts",
    "description" : null,
    "server" : "loop_search_node",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "loop_documents_document", "loop_documents_collection", "external_sources", "instruction", "leaf", "post" ] },
      "index_directly" : 0,
      "cron_limit" : "50",
      "search_node_indexes" : "833bc3ffdcd187e4bf72945e7fe4a08d",
      "fields" : {
        "body:summary" : { "type" : "text" },
        "body:value" : { "type" : "text" },
        "changed" : { "type" : "date" },
        "comment_count" : { "type" : "integer" },
        "comments" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "comment" },
        "comments:comment_body:value" : { "type" : "list\\u003Ctext\\u003E" },
        "created" : { "type" : "date" },
        "field_description:value" : { "type" : "text" },
        "field_external_link:url" : { "type" : "uri" },
        "field_keyword:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_profession:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_subject:name" : { "type" : "text" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" }
      },
      "data_alter_callbacks" : {
        "location" : { "status" : 0, "weight" : "-50", "settings" : { "field_name" : "" } },
        "exclude" : {
          "status" : 0,
          "weight" : "-50",
          "settings" : { "fields" : { "name" : "", "values" : "" } }
        },
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : { "title" : true } }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : { "title" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 0,
          "weight" : "15",
          "settings" : { "fields" : { "title" : true } }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function loop_search_node_settings_default_search_api_server() {
  $items = array();
  $items['loop_search_node'] = entity_import('search_api_server', '{
    "name" : "Loop search node",
    "machine_name" : "loop_search_node",
    "description" : "",
    "class" : "search_api_search_node_service",
    "options" : {
      "host" : "http:\\/\\/search.node.local",
      "apikey" : "2d72e44305d22db33c86400ce27486b1",
      "apikey_readonly" : "1c324b1a808006b080e9da60f7695510"
    },
    "enabled" : "1"
  }');
  return $items;
}
