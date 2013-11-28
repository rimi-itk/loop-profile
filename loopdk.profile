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

/**
 * Implements hook_install_tasks().
 *
 * As this function is called early and often, we have to maintain a cache or
 * else the task specifying a form may not be available on form submit.
 */
function loopdk_install_tasks(&$install_state) {
  $ret = array(
    // Update translations.
    'loopdk_import_translation' => array(
      'display_name' => st('Set up translations'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),
    'loopdk_setup_filter_and_wysiwyg' => array(
      'display_name' => st('Setup filter and WYSIWIG'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch'
    ),
    'loopdk_setup_apache_solr' => array(
      'display_name' => st('Setup Apache Solr'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch'
    ),
  );
  return $ret;
}

/**
 * Translation callback.
 *
 * Add danish language and import for every module.
 *
 * @param $install_state
 *   An array of information about the current installation state.
 *
 * @return array
 *   List of batches.
 */
function loopdk_import_translation() {
  // Enable danish language.
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  locale_add_language('da', NULL, NULL, NULL, '', NULL, TRUE, TRUE);

  // Build batch with l10n_update module.
  $history = l10n_update_get_history();
  module_load_include('check.inc', 'l10n_update');
  $available = l10n_update_available_releases();
  $updates = l10n_update_build_updates($history, $available);

  // Fire of the batch!
  module_load_include('batch.inc', 'l10n_update');
  $updates = _l10n_update_prepare_updates($updates, NULL, array());
  $batch = l10n_update_batch_multiple($updates, LOCALE_IMPORT_KEEP);
  return $batch;
}

/**
 * Setup text filter and WYSIWYG.
 */
function loopdk_setup_filter_and_wysiwyg() {
  $format = new Stdclass();
  $format->format = 'editor';
  $format->name = 'Editor';
  $format->status = 1;
  $format->weight = 0;
  $format->filters = array(
    'filter_url' => array(
      'weight' => -49,
      'status' => 1,
      'settings' => array(
        'filter_url_length' => 72,
      ),
    ),
    'filter_html' => array(
      'weight' => -48,
      'status' => 1,
      'settings' => array(
        'allowed_html' => '<a> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd>',
        'filter_html_help' => 1,
        'filter_html_nofollow' => 0,
      ),
    ),
    'filter_autop' => array(
      'weight' => -46,
      'status' => 1,
      'settings' => array(),
    ),
    'filter_htmlcorrector' => array(
      'weight' => -45,
      'status' => 1,
      'settings' => array(),
    ),
  );

  filter_format_save($format);

  $settings = array(
    'default' => 1,
    'user_choose' => 0,
    'show_toggle' => 1,
    'theme' => 'advanced',
    'language' => 'en',
    'buttons' => array(
      'default' => array(
        'Bold' => 1,
        'Italic' => 1,
        'Underline' => 1,
        'BulletedList' => 1,
        'NumberedList' => 1,
        'Link' => 1,
        'PasteText' => 1,
      ),
    ),
    'toolbar_loc' => 'top',
    'toolbar_align' => 'left',
    'path_loc' => 'bottom',
    'resizing' => 1,
    'verify_html' => 1,
    'preformatted' => 0,
    'convert_fonts_to_spans' => 1,
    'remove_linebreaks' => 1,
    'apply_source_formatting' => 0,
    'paste_auto_cleanup_on_paste' => 0,
    'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
    'css_setting' => 'theme',
    'css_path' => '',
    'css_classes' => '',
  );

  db_merge('wysiwyg')
    ->key(array('format' => $format->format))
    ->fields(array(
      'editor' => 'ckeditor',
      'settings' => serialize($settings),
    ))
    ->execute();
}

/**
 * Setup Apache Solr.
 */
function loopdk_setup_apache_solr() {
  db_query("UPDATE apachesolr_environment SET name='LOOP', url='http://localhost:8983/solr/loop_stg'");
}
