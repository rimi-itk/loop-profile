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

  if ( (arg(0) == 'search') && (!isset($variables['page']['no_result'])) ) {
    // No search results, change title.
    $variables['title'] = t('Ask question');
  }

  // Load LOOP primary menu.
  if (module_exists('loop_navigation')) {
    $variables['loop_primary_menu'] = module_invoke('menu', 'block_view', 'menu-loop-primary-menu');
  }

  // Check if we are using a panel page to define layout.
  $variables['no_panel'] = FALSE;
  $panel = panels_get_current_page_display();

  if(empty($panel)) {
    $variables['no_panel'] = TRUE;
  }
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

    // Add no search results message.
    $build['no_result'] = array(
      '#prefix' => '<div class="loop-no-search-results">',
      '#suffix' => '</div>',
      '#markup' => t('No search results found!'),
    );

    // Add the post.
    $node->field_description['und'][0]['value'] = arg(2);
    $form = drupal_get_form('node_form', $node);
    $build['form'] = $form;

    // Remove suggestions and other related information.
    unset($build['search_form']);
    unset($build['suggestions']);
    unset($build['search_results']);
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
function loop_menu_link__menu_loop_primary_menu($variables) {
  $element = $variables['element'];
  $element['#attributes']['class'][] = 'nav-mobile--link';
  $element['#localized_options']['attributes']['class'] = $element['#attributes']['class'];
  // Make sure text string is treated as html by l function.
  $element['#localized_options']['html'] = TRUE;

  $output_title = '<span class="nav-mobile--text">' . $element['#title'] . '</span>';

  $output = l($output_title, $element['#href'], $element['#localized_options']);
  return $output;
}

/**
 * Returns HTML for a fieldset form element and its children.
 *
 * Changes the class added to fieldsets, so it differs from the wrapper added inside.
 */
function loop_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('field-group-fieldset'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
  }
  $output .= '<div class="fieldset-wrapper">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}

/**
 * Implements template_preprocess_user_profile().
 */
function loop_preprocess_user_profile(&$variables) {
  $account = $variables['elements']['#account'];

  // Provide a full name to the template if both first name and surname exists.
  $first_name = field_get_items('user', $variables['elements']['#account'], 'field_first_name');
  $surname = field_get_items('user', $variables['elements']['#account'], 'field_last_name');
  if(!empty($first_name)) {
    $variables['first_name'] = field_view_value('user', $variables['elements']['#account'], 'field_first_name', $first_name['0']);
  }
  if(!empty($surname)) {
    $variables['surname'] = field_view_value('user', $variables['elements']['#account'], 'field_last_name', $surname['0']);
  }
  if(!empty($first_name) && !empty($surname)) {
    $variables['full_name'] = $variables['first_name']['#markup'] . ' ' . $variables['surname']['#markup'];
  }

  // Helpful $user_profile variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }

  // Preprocess fields.
  field_attach_preprocess('user', $account, $variables['elements'], $variables);
}