<?php

/**
 * Implement hook_install_tasks_alter().
 *
 */
function loopdk_install_tasks_alter(&$tasks, $install_state) {
  // Callback for languageg selection.
  $tasks['install_select_locale']['function'] = 'loopdk_locale_selection';
}

// Set default language to english.
function loopdk_locale_selection(&$install_state) {
  $install_state['parameters']['locale'] = 'en';
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'LOOP';
    $form['server_settings']['site_default_country']['#default_value'] = 'DK';
    $form['server_settings']['date_default_timezone']['#default_value'] = 'Europe/Copenhagen';
  }
}