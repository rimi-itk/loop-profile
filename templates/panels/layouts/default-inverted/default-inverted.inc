<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Default inverted'),
  'category' => t('Loop custom'),
  'icon' => 'default.png',
  'theme' => 'default-inverted',
  'regions' => array(
    'alpha' => t('Alpha'),
    'beta' => t('Beta')
  ),
);
