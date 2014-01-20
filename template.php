<?php
/**
 * @file
 * Preprocess and Process Functions.
 */

/**
 * Override or insert variables into the html template.
 */
function loop_preprocess_html(&$variables) {
}

/**
 * Override or insert variables into the page template.
 */
function loop_preprocess_page(&$variables) {
  // Prepare system search block for page.tpl.
  $variables['search'] = module_invoke('search', 'block_view', 'form');
}


/**
 * Override or insert variables into the region template.
 */
function loop_preprocess_region(&$variables) {
}

/**
 * Override or insert variables into the node template.
 */
function loop_preprocess_node(&$variables) {
}

/**
 * Override or insert variables into the field template.
 */
function loop_preprocess_field(&$variables) {
}

/**
 * Override or insert variables into the block template.
 */
function loop_preprocess_block(&$variables) {
}

/**
 * Override or insert variables into the panel pane template.
 */
function loop_preprocess_panels_pane(&$variables) {
}

/**
 * Implements template_preprocess_search_results().
 */
function loop_apachesolr_search_page_alter(&$build, $search_page) {
  if (!isset($build['search_results']['#results'])) {
    // No hits. Send formular to template.
    module_load_include('inc', 'node', 'node.pages');
    $node = new stdClass();
    $node->type = 'post';

    // Add the post.
    $node->field_description['und'][0]['value'] = arg(2);
    $form = drupal_get_form('node_form', $node);
    unset($build['search_form']);
    unset($build['suggestions']);
    unset($build['search_results']);
    $build['form'] = $form;
  }
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * Cleans up markup for main menu.
 */
function loop_menu_tree__main_menu($variables) {
  return $variables['tree'];
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * Cleans up markup for main menu.
 * And insert icons in front of spcific menu items.
 */
function loop_menu_link__main_menu(array $variables) {
  // Path to theme variable.
  $path_to_theme = drupal_get_path('theme', 'loop');

  $element = $variables['element'];
  $element['#attributes']['class'][] = 'nav--link';
  if ($element['#href'] == '<nolink>') {
    $element['#attributes']['class'][] = 'js-toggle-mobile-nav';
  }
  $element['#localized_options']['attributes']['class'] = $element['#attributes']['class'];
  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $output_title = '<span class="nav--text">' . $element['#title'] . '</span>';

  // Insert menu icon for specific menu items.
  if ($element['#href'] == 'user') {
    $icon_img = $path_to_theme . '/images/nav-user-icon.png';
  }
  if (stristr($element['#href'], '/messages')) {
    $icon_img = $path_to_theme . '/images/nav-mail-icon.png';
  }
  if ($element['#href'] == 'node/add/post') {
    $icon_img = $path_to_theme . '/images/nav-add-icon.png';
  }
  if ($element['#href'] == '<nolink>') {
    $icon_img = $path_to_theme . '/images/nav-menu-icon.png';
  }
  if (isset($icon_img)) {
    $imgvars = array(
      'path' => $icon_img,
      'attributes' => array('class' => array('nav--icon')),
    );
    $output_title = theme_image($imgvars) . $output_title;
  }

  $output = l($output_title, $element['#href'], $element['#localized_options']);
  return $output;
}

/**
 * Returns HTML for a wrapper for a menu sub-tree.
 *
 * Cleans up markup for Loop primary menu.
 */
function loop_menu_tree__menu_loop_primary_menu($variables) {
  return $variables['tree'];
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * Cleans up markup for Loop primary menu.
 */
function loop_menu_link__menu_loop_primary_menu(array $variables) {
  $element = $variables['element'];
  $element['#attributes']['class'][] = 'nav-mobile--link';
  $element['#localized_options']['attributes']['class'] = $element['#attributes']['class'];
  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $output_title = '<span class="nav-mobile--text">' . $element['#title'] . '</span>';

  $output = l($output_title, $element['#href'], $element['#localized_options']);
  return $output;
}
