<?php
/**
 * @file
 * loop_notification.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function loop_notification_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-page-body.display|notifications"] = array(
    'label' => 'above',
    'settings' => array(),
    'type' => 'hidden',
    'weight' => 0,
  );

 return $overrides;
}
