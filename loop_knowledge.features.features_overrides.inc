<?php
/**
 * @file
 * loop_knowledge.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function loop_knowledge_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.post.options|data_alter_callbacks|search_api_alter_bundle_filter|settings|bundles|external_sources"]["DELETED"] = TRUE;
  $overrides["search_api_index.post.options|data_alter_callbacks|search_api_alter_bundle_filter|settings|bundles|leaf"]["DELETED"] = TRUE;
  $overrides["search_api_index.post.options|data_alter_callbacks|search_api_alter_bundle_filter|settings|bundles|page"] = 'page';
  $overrides["search_api_index.post.options|data_alter_callbacks|search_api_alter_bundle_filter|settings|bundles|vejledning"] = 'vejledning';
  $overrides["search_api_index.post.options|data_alter_callbacks|search_api_alter_language_control"] = array(
    'status' => 0,
    'weight' => 0,
    'settings' => array(
      'lang_field' => '',
      'languages' => array(),
    ),
  );
  $overrides["search_api_index.post.options|fields|body:value"] = array(
    'type' => 'text',
  );
  $overrides["search_api_index.post.options|fields|title"] = array(
    'type' => 'text',
  );

 return $overrides;
}
