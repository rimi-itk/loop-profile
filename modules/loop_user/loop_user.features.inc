<?php
/**
 * @file
 * loop_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function loop_user_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function loop_user_image_default_styles() {
  $styles = array();

  // Exported image style: preview.
  $styles['preview'] = array(
    'label' => 'Preview',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 192,
          'height' => 192,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: profile.
  $styles['profile'] = array(
    'label' => 'Profile',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 500,
          'height' => 500,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
