<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Front page'),
  'category' => t('Loop custom'),
  'icon' => 'front-page.png',
  'theme' => 'front-page',
  'regions' => array(
    'alpha' => t('Alpha'),
    'beta' => t('Beta'),
    'gamma' => t('Gamma')
  ),
);
