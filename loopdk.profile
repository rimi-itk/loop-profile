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
