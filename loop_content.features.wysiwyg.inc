<?php
/**
 * @file
 * loop_content.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function loop_content_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: editor
  $profiles['editor'] = array(
    'format' => 'editor',
    'editor' => 'ckeditor',
    'settings' => array(
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
          'Styles' => 1,
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
      'css_classes' => 'Header (h2)=h2.header--big
Header (h3)=h3.header--medium
Header (h4)=h4.header--small',
    ),
  );

  return $profiles;
}
