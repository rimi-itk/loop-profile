<?php

require_once __DIR__ . '/template.php';

/**
 * @file
 * Theme setting callbacks for the loop theme.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function loop_form_system_theme_settings_alter(&$form, &$form_state) {
  $form['theme_settings']['show_breadcrumbs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumbs'),
    '#default_value' => theme_get_setting('show_breadcrumbs', 'loop'),
    '#description' => t("Show breadcrumbs at the top each page."),
  );
  $form['theme_settings']['loop_skin'] = array(
    '#type'          => 'select',
    '#title'         => t('Skin'),
    '#options' => array(
      '' => t('(default)'),
      'red' => t('Red'),
      'blue' => t('Blue'),
      'green' => t('Green'),
      'cura' => t('Cura'),
      'buloop' => t('Børn og Unge'),
      'risikataloop' => t('Risikataloop'),
      'dokk1' => t('Dokk1'),
    ),
    '#default_value' => theme_get_setting('loop_skin'),
    '#description'   => t('Choose a skin for the site.'),
  );

  $form['login_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Log in settings'),
    '#collapsible' => FALSE,
    '#description' => t("Settings for log in behaviour"),
  );

  $form['login_settings']['show_login_for_regular_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show regular log in button'),
    '#default_value' => theme_get_setting('show_login_for_regular_users', 'loop'),
    '#description' => t("Show log in button for regular users, i.e. username and password fields"),
  );

  $login_service_options = array('' => t('None'));
  foreach (_loop_get_login_services() as $name => $service) {
    if ($name !== 'loop-login') {
      $login_service_options[$name] = $service['name'];
    }
  }

  $form['login_settings']['default_login_service_name'] = array(
    '#type' => 'select',
    '#title' => t('Default login service name'),
    '#options' => $login_service_options,
    '#default_value' => theme_get_setting('default_login_service_name'),
    '#description' => t("Default login service to redirect anonymous users to"),
  );

  $form['login_settings']['default_login_service_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Default login service path'),
    '#default_value' => theme_get_setting('default_login_service_path') ? theme_get_setting('default_login_service_path') : 'user/login',
    '#description' => t("Path on which to check for default login service"),
    '#required' => TRUE,
  );

  $form['logout_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logout button settings'),
    '#collapsible' => FALSE,
    '#description' => t("Settings determining behaviour of the logout button"),
  );

  $form['logout_settings']['show_logout_for_regular_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show logout button for regular users'),
    '#default_value' => theme_get_setting('show_logout_for_regular_users', 'loop'),
    '#description' => t("Show logout button when logged in as a regular user"),
  );

  $form['logout_settings']['show_logout_for_saml_users'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show logout button for SAML users'),
    '#default_value' => theme_get_setting('show_logout_for_saml_users', 'loop'),
    '#description' => t("Show logout button when logged via SAML"),
  );

}
