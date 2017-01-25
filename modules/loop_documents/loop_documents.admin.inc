<?php

/**
 * @file
 * Admin interface for the loop_documents module.
 */

/**
 * Build settings form.
 */
function loop_documents_admin() {
  $form = array();

  $wkhtmltopdf_options_default_value = '';

  $options = loop_documents_get_wkhtmltopdf_options();
  if ($options) {
    foreach ($options as $name => $value) {
      $wkhtmltopdf_options_default_value .= $name . ': ' . $value . PHP_EOL;
    }
  }

  $form = array(
    'loop_documents_wkhtmltopdf' => array(
      '#type' => 'fieldset',
      '#title' => t('wkhtmltopdf settings'),

      'loop_documents_wkhtmltopdf_options' => array(
        '#type' => 'textarea',
        '#title' => t('Options'),
        '#default_value' => variable_get('loop_documents_wkhtmltopdf_options', $wkhtmltopdf_options_default_value),
        '#rows' => 10,
        '#description' => t('Options for wkhtmltopdf command line tool. One options per line in the format "option-name: option-value".<br/>See <a href="http://wkhtmltopdf.org/usage/wkhtmltopdf.txt">http://wkhtmltopdf.org/usage/wkhtmltopdf.txt</a> for details on valid options. Option values can contain token placeholders; see below for available tokens.'),
        '#element_validate' => array('token_element_validate'),
        '#token_types' => array('node', 'site', 'user'),
        '#required' => FALSE,
      ),

      'token_help' => array(
        '#theme' => 'token_tree_link',
        '#token_types' => array('node', 'site', 'user'),
      ),

      'loop_documents_header_image' => array(
        '#type' => 'managed_file',
        '#name' => 'header_image',
        '#title' => t('Header image file'),
        '#description' => t('Optional image that can be used in print headers.'),
        '#default_value' => variable_get('loop_documents_header_image', NULL),
        '#upload_location' => 'public://files/',
      ),

      'loop_documents_footer_image' => array(
        '#type' => 'managed_file',
        '#name' => 'footer_image',
        '#title' => t('Footer image file'),
        '#description' => t('Optional image that can be used in print footers.'),
        '#default_value' => variable_get('loop_documents_footer_image', NULL),
        '#upload_location' => 'public://files/',
      ),
    ),
  );

  return system_settings_form($form);
}
