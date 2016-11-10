<?php

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
