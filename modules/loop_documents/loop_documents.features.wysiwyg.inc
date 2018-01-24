<?php
/**
 * @file
 * loop_documents.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function loop_documents_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: loop_documents.
  $profiles['loop_documents'] = array(
    'format' => 'loop_documents',
    'editor' => 'ckeditor',
    'settings' => array(
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Outdent' => 1,
          'Indent' => 1,
          'Undo' => 1,
          'Redo' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'PasteFromWord' => 1,
          'Templates' => 1,
        ),
        'drupal_proofread' => array(
          'Proofread' => 1,
        ),
        'drupal_path' => array(
          'Link' => 1,
        ),
        'drupal' => array(
          'media' => 1,
        ),
      ),
      'theme' => '',
      'language' => 'en',
      'toolbarLocation' => 'top',
      'resize_enabled' => 1,
      'default_toolbar_grouping' => 0,
      'simple_source_formatting' => 0,
      'acf_mode' => 0,
      'acf_allowed_content' => '',
      'css_setting' => 'theme',
      'css_theme' => '',
      'css_path' => '',
      'stylesSet' => '',
      'block_formats' => 'p,h2,h3',
      'forcePasteAsPlainText' => 0,
      'pasteFromWordNumberedHeadingToList' => 0,
      'pasteFromWordPromptCleanup' => 0,
      'pasteFromWordRemoveFontStyles' => 1,
      'pasteFromWordRemoveStyles' => 1,
    ),
    'preferences' => array(
      'add_to_summaries' => 1,
      'default' => 1,
      'show_toggle' => 0,
      'user_choose' => 0,
      'version' => '4.5.3.6c70c82',
    ),
    'name' => 'formatloop_documents',
  );

  return $profiles;
}
