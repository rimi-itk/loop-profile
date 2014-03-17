<?php
/**
 * @file
 * Preprocess and Process Functions.
 */


/**
 * Override or insert variables into the page template.
 */
function loop_preprocess_page(&$variables) {
  $arg0 = arg(0);
  // Prepare system search block for page.tpl.
  if (module_exists('search_api_page')) {
    $variables['search'] = module_invoke('search_api_page', 'block_view', 'default');
  }
  else {
    $variables['search'] = module_invoke('search', 'block_view', 'form');
  }

  // Remove search form when no search results are found.
  if ( (isset($variables['page']['content']['system_main']['results'])) &&  ($variables['page']['content']['system_main']['results']['#results']['result count'] == 0)) {
    unset($variables['page']['content']['system_main']['form']);
  }

  if ($arg0 == 'user') {
    $variables['loop_user_my_content'] = module_invoke('loop_user', 'block_view', 'loop_user_my_content');
    hide($variables['tabs']['#secondary']);
  }

  // Load LOOP primary menu.
  if (module_exists('loop_navigation')) {
    $variables['main_menu_block'] = module_invoke('system', 'block_view', 'main-menu');
    $variables['primary_menu_block'] = module_invoke('menu', 'block_view', 'menu-loop-primary-menu');
  }
  else {
    $variables['main_menu_block'] = FALSE;
    $variables['primary_menu_block'] = FALSE;
  }

  // Load LOOP primary menu.
  if (module_exists('loop_user') && arg(0) == 'user') {
    $variables['user_public_block'] = module_invoke('loop_user', 'block_view', 'loop_user_my_content');
  }
  else {
    $variables['user_public_block'] = FALSE;
  }

  // Check if we are using a panel page to define layout.
  $variables['no_panel'] = FALSE;
  $panel = panels_get_current_page_display();

  if(empty($panel)) {
    $variables['no_panel'] = TRUE;
  }
}


/**
 * Override or insert variables into the node template.
 */
function loop_preprocess_node(&$variables) {
  $author = user_load($variables['node']->uid);
  $variables['author_name'] = fetch_full_name($author);
  $fetched_job_title = field_get_items('user', $author, 'field_job_title');
  $variables['job_title'] = field_view_value('user', $author, 'field_job_title', $fetched_job_title[0], array());
}


/**
 * Override or insert variables into the panel pane template.
 */
function loop_preprocess_panels_pane(&$variables) {
  // Add template for flag subscribe button on post node.
  if ($variables['pane']->subtype == 'node:flag_subscribe_node') {
    $variables['theme_hook_suggestions'][] = 'panels_pane__flag_subscribe';
  }
}


/**
 * Implements hook_search_api_page_results().
 */
function loop_preprocess_search_api_page_results(&$variables) {
  if ($variables['result_count'] == 0) {
    global $user;
    // No hits. Send formular to template.
    module_load_include('inc', 'node', 'node.pages');
    $node = new stdClass();
    $node->type = 'post';
    $node->langauge = LANGUAGE_NONE;
    $node->uid = $user->uid;
    $node->name = $user->name;

    // Add the post.
    $node->field_description['und'][0]['value'] = arg(1);
    $form = drupal_get_form('node_form', $node);
    $variables['node_form'] = $form;
  }
}

/**
 * Implements theme_menu_local_task().
 */
function loop_menu_local_task($variables) {
  $secondary = '';
  $link = $variables['element']['#link'];
  $list_class = 'block-module--user-links-item';

  // Tabs on login pages.
  if ($GLOBALS['user']-> uid == 0 || (arg(0) == 'notifications' && arg(1) == 'subscription')) {
    $list_class = 'tabs-anonymous';
  }

  // User account tabs (Left menu)
  if ($link['page_callback'] == 'page_manager_user_view_page') {
    $link['title'] = t('My account');
  }

  if ($link['page_callback'] == 'messaging_simple_user_page') {
    $link['title'] = t('Notifications');
  }

  if ($link['path'] == 'user/%/notifications') {
    $link['title'] = t('Subscriptions');
  }

  if ($link['path'] == 'user/%/messages') {
    // Add the secondary menu.
    $secondary = menu_secondary_local_tasks();
  }

  // Don't print shortcuts and statistics.
  if ($link['page_callback'] == 'statistics_user_tracker' || $link['path'] == 'user/%/shortcuts' || $link['path'] == 'user/%/message-subscribe') {
    return FALSE;
  }

  if(!empty($variables['element']['#active'])) {
    $list_class .= ' active';
  }

  $sub_menu = '';
  if ($secondary) {
    $sub_menu = '<ul class="block-module-user-links-list-sub ">' . drupal_render($secondary) . '</ul>';
  }


  $link_text = $link['title'];

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

  return '<li class="' .$list_class. '">' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n" . $sub_menu;
}


/**
 * Implements theme_menu_local_tasks().
 */
function loop_menu_local_tasks($variables) {
  $output = '';
  // Tabs for login pages.
  if ($GLOBALS['user']-> uid > 0 && arg(0) == 'user') {
    if (!empty($variables['primary'])) {
      $variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
      $variables['primary']['#prefix'] .= '<ul class="block-module--user-links-list">';
      $variables['primary']['#suffix'] = '<li class="block-module--user-links-item-last"><a href="/user/logout">' . t('Logout') . '</a></li></ul>';
      $output .= drupal_render($variables['primary']);
    }
  }
  return $output;
}


/**
 * Implements theme_menu_tree__main_menu().
 *
 * System generated menu links from different modules. Menu not to be changed by users.
 * Forms the header menu together with primary menu.
 */
function loop_menu_tree__main_menu ($variables) {
  $theme_path = drupal_get_path('theme', 'loop');

  // Add notificaiton link
  if (printNotificationTab()) {
    $variables['tree'] = $variables['tree'] . printNotificationTab();
  }

  // If loop navigation exists add a mobile dropdown navigation.
  if (module_exists('loop_navigation')) {
    $element['#localized_options']['attributes']['class'][] = 'last leaf nav--toggle-mobile-nav js-toggle-mobile-nav nolink';

    // Allow images in the links.
    $element['#localized_options']['html'][] = TRUE;

    // Allow no path (path = #)
    $element['#localized_options']['external'][] = TRUE;

    $img = array(
      'path' => '/' . $theme_path . '/images/nav-menu-icon.png',
      'attributes' => array('class' => 'nav--icon'),
    );
    // Create the title with image icon.
    $element['#title'] = theme_image($img) . '<span class="nav--text">Menu</span>';

    $variables['tree'] = $variables['tree'] . l($element['#title'], '#', $element['#localized_options']);
  }

  // If the menu contains <li> tag add a ul tag.
  return $variables['tree'];
}


/**
 * Implements theme_menu_tree__menu_loop_primary_menu().
 *
 * User generated link.
 * Forms the header menu together with main menu.
 */
function loop_menu_tree__menu_loop_primary_menu($variables) {
  // If the menu contains <li> tag add a ul tag.
  return $variables['tree'];
}


/**
 * Implements theme_menu_link().
 */
function loop_menu_link__main_menu($variables){
  $theme_path = drupal_get_path('theme', 'loop');
  $element = $variables['element'];

  // Add images to links depending on the path of the link
  switch ($element['#href']) {
    case 'user':
      $img = array(
        'path' => '/' . $theme_path . '/images/nav-user-icon.png',
        'attributes' => array('class' => 'nav--icon'),
      );
      // Create the title with image icon.
      $element['#title'] = theme_image($img) . '<span class="nav--text">' . $element['#title'] . '</span>';
      break;
    case 'node/add/post':
      $img = array(
        'path' => '/' . $theme_path . '/images/nav-add-icon.png',
        'attributes' => array('class' => 'nav--icon'),
      );
      // Create the title with image icon.
      $element['#title'] = theme_image($img) . '<span class="nav--text">' . $element['#title'] . '</span>';
      break;
  }

  $element['#localized_options']['attributes']['class'][] = 'nav--link';

  // Allow images in the links.
  $element['#localized_options']['html'][] = TRUE;

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return $output . "\n";
}


/**
 * Implements theme_menu_link().
 */
function loop_menu_link__menu_loop_primary_menu($variables){
  $theme_path = drupal_get_path('theme', 'loop');
  $element = $variables['element'];

  // Sub item exist (Element is parent).
  if (!empty($variables['element']['#below'])) {
    $img = array(
      'path' => '/' . $theme_path . '/images/nav-arrow-down-icon.png',
      'attributes' => array('class' => 'nav-dropdown--icon'),
    );
    // Create the title with image icon.
    $element['#title'] = theme_image($img) . '<span class="nav--text">' . $element['#title'] . '</span>';

    // Wrap the sub menu.
    $sub_menu = '<div class="nav-dropdown--item">' . drupal_render($element['#below']) . '</div>';

    $element['#localized_options']['attributes']['class'][] = 'nav-dropdown--header';

    // Allow images in the links.
    $element['#localized_options']['html'][] = TRUE;

    $output = '<div class="nav-dropdown--wrapper">' . l($element['#title'], $element['#href'], $element['#localized_options']) . $sub_menu . '</div>';
  }

  // Element has parent.
  elseif ($element['#original_link']['plid'] > 0) {
    $element['#localized_options']['attributes']['class'][] = 'nav-dropdown--link';
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return  $output;
  }

  // Default main menu link, not parent and not child.
  else {
    $element['#localized_options']['attributes']['class'][] = 'nav--link';
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  }
  return $output . "\n";
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

  $variables['full_name'] = fetch_full_name($account);

  // Helpful $user_profile variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    $variables['user_profile'][$key] = $variables['elements'][$key];
  }

  // Preprocess fields.
  field_attach_preprocess('user', $account, $variables['elements'], $variables);
}


/**
 * Implements theme_panels_default_style_render_region().
 *
 * Remove the panel separator from the default rendering method.
 */
function loop_panels_default_style_render_region($vars) {
  $output = '';
  $output .= implode('', $vars['panes']);
  return $output;
}


/**
 * Implements hook_form_FORM_ID_alter().
 */
function loop_form_user_login_alter(&$form, &$form_state, $form_id) {
  $form['#prefix'] = '<h2>' . t('User login') . '</h2>';
  $form['pass']['#suffix'] = '<ul class="user-form--password-link"><li><a href="/user/password">' . t('Request new password') . '</a></li></ul>';
  $form['name']['#description'] = FALSE;
  $form['name']['#title'] = t('Username or e-mail');
  $form['pass']['#description'] = FALSE;
}


/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Adds custom class names and placeholder attribute and icon prefix to search field.
 */
function loop_form_search_api_page_search_form_default_alter(&$form, &$form_state, $form_id) {
  // Change title text and make sure the label is displayed.
  $form['keys_1']['#title_display'] = 'before';
  $form['keys_1']['#title'] = t('Search for an answer');

  // Add icon markup as a prefix to field.
  $form['keys_1']['#field_prefix'] = '<i class="typeahead-block--icon icon-search"></i>';
}


/**
 * Implements hook_form_FORM_ID_alter().
 */
function loop_form_comment_form_alter(&$form, $form_state)  {
  $variables['user_obj'] = user_load($GLOBALS['user']->uid);
  if (!empty($variables['user_obj'])) {
    $variables['user_name'] = fetch_full_name($variables['user_obj']);

    // Load entity wrapper.
    $wrapper = entity_metadata_wrapper('user', $variables['user_obj']);

    // Get job title.
    $variables['jobtitle'] = $wrapper->field_job_title->value();
  }


  $form['#prefix'] = theme('comment_form_prefix', $variables);
  $form['#prefix'] .= '<div class="form-module">';
  hide($form['author']);
  $form['comment_body'][LANGUAGE_NONE][0]['#wysiwyg'] = FALSE;
  $form['#suffix'] = '</div>';
}


/**
 * Implements hook_form_FORM_ID_alter().
 * For display on user/[uid]/notifications/subscription.
 */
function loop_form_notifications_account_manage_subscriptions_form_alter(&$form, $form_state)  {
  // Hide filtering.
  $form['filters']['#access'] = FALSE;

  // Remove unneeded info about the users subscriptions and clean up the table.
  unset($form['admin']['options']['#prefix']);
  unset($form['admin']['options']['#suffix']);
  unset($form['admin']['subscriptions']['#header']['sid']);
  unset($form['admin']['subscriptions']['#header']['type']);
  unset($form['admin']['subscriptions']['#header']['status']);
  unset($form['admin']['subscriptions']['#header']['created']);
  unset($form['admin']['subscriptions']['#header']['send_method']);
  unset($form['admin']['subscriptions']['#header']['send_interval']);

  // Add a class to the form.
  $form['admin']['subscriptions']['#attributes']['class'][] = 'notification--user-subscriptions';
}


/**
 * Implements hook_theme().
 */
function loop_theme($existing, $type, $theme, $path) {
  return array(
    'comment_form_prefix' => array(
      'variables' => array(),
      'path' => drupal_get_path('theme', 'loop') . '/templates/forms',
      'template' => 'comment-form-prefix',
    ),
  );
}


/**
 * Implements hook_preprocess_comment().
 *
 * Load user for every comment.
 */
function loop_preprocess_comment(&$variables) {
  // Make the content author object available.
  $variables['comment']->account = user_load($variables['comment']->uid);

  $variables['comment_author_name'] = fetch_full_name($variables['comment']->account);

  // Fetch the fields needed.
  $fetched_job_title = field_get_items('user', $variables['comment']->account, 'field_job_title');
  $variables['job_title'] = field_view_value('user', $variables['comment']->account, 'field_job_title', $fetched_job_title[0], array());
}

/**
 * Implements hook_preprocess_loop_post_subscription_list().
 *
 * Preprocesss function for displaying subscribe/unsubscribe on nodes
 */
function loop_preprocess_loop_post_subscription_list(&$vars) {
  $vars['custom_link'] = l($vars['link']['#text'], $vars['link']['#path'], array('attributes' => array('class' => array('block-module--link')), 'html' => 'TRUE', 'query' => array($vars['link']['#query'])));

  if($vars['link']['#text'] == 'Subscribe') {
    $vars['current_type_css'] = 'block-follow-question';
  }
  else {
    $vars['current_type_css'] = 'block-unfollow-question';
  }
}


/**
 * Fetch the full name from a user object, if both first name and last name is set.
 *
 * @param $uid
 *
 * @return $name
 */
function fetch_full_name ($user_obj) {
  $name = '';

  // Make sure we are dealing with an object.
  if(is_object($user_obj)) {

    // Load entity wrapper.
    $wrapper = entity_metadata_wrapper('user', $user_obj);

    // Get first name and last name.
    $first_name = $wrapper->field_first_name->value();
    $last_name = $wrapper->field_last_name->value();

    // Set name.
    if ($first_name && $last_name) {
      $name = $first_name . ' ' . $last_name;
    } else {
      $name = $user_obj->name;
    }
  }
  return $name;
}


/**
 * Implements hook_textarea().
 *
 * Remove grippie from textarea.
 */
function loop_textarea($variables) {
  $element = $variables['element'];
  $element['#attributes']['name'] = $element['#name'];
  $element['#attributes']['id'] = $element['#id'];
  $element['#attributes']['cols'] = $element['#cols'];
  $element['#attributes']['rows'] = $element['#rows'];
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    $wrapper_attributes['class'][] = 'resizable';
  }

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}

function loop_preprocess_views_view(&$vars) {
  // We run the new message count in this function since the view updates with ajax.
  if ($vars['view']->name == 'user_messages') {
    // Fetch all current users messages from the message table.
    $all_message_count = db_query('SELECT uid FROM message WHERE uid = :uid', array(':uid' => $GLOBALS['user']->uid))->rowCount();

    // Fetch flag id (fid) for the message_read flag.
    $flag_id = db_query('SELECT fid FROM flag WHERE name = :machine_name', array(':machine_name' => "message_read"))->fetchField();

    // Fetch all flags of type message_read (fid) that the current user made.
    $flagged_read_message_count = db_query('SELECT entity_id FROM flagging WHERE uid = :uid AND fid = :fid', array(':uid' => $GLOBALS['user']->uid, ':fid' => $flag_id))->rowCount();

    // Compare the two.
    $new_message_count = $all_message_count - $flagged_read_message_count;
  }
  $update_script_path = $GLOBALS['base_root'] . '/' . path_to_theme() .'/scripts/update-new-notifications.js';
  drupal_add_js($update_script_path, 'file');
  $vars['user_messages'] = $new_message_count;
}

/**
 * Implements printNotificationTab().
 *
 * Function for printing the notification tab. Since the page already exists we don't use hook menu.
 *
 * @return html for the notification tab or false if module does not exist or user is not logged in.
 */
function printNotificationTab() {
  // We run the new message count in this function called from loop_links__system_primary_menu() since it should display on all pages.
  if (module_exists('loop_notification') && $GLOBALS['user']->uid > 0) {
    $theme_path = drupal_get_path('theme', 'loop');

    // Fetch all current users messages from the message table.
    $all_message_count = db_query('SELECT uid FROM message WHERE uid = :uid', array(':uid' => $GLOBALS['user']->uid))->rowCount();

    // Fetch flag id (fid) for the message_read flag.
    $flag_id = db_query('SELECT fid FROM flag WHERE name = :machine_name', array(':machine_name' => "message_read"))->fetchField();

    // Fetch all flags of type message_read (fid) that the current user made.
    $flagged_read_message_count = db_query('SELECT entity_id FROM flagging WHERE uid = :uid AND fid = :fid', array(':uid' => $GLOBALS['user']->uid, ':fid' => $flag_id))->rowCount();

    // Compare the two.
    $new_message_count = $all_message_count - $flagged_read_message_count;

    // If new messages exist.
    if ($new_message_count > 0) {
      $new_messages = '<span class="notification">' . $new_message_count . '</span>';
    }
    else {
      $new_messages = '';
    }

    // Add the link image for mobile.
    $img = array(
      'path' => '/' . $theme_path . '/images/nav-mail-icon.png',
      'attributes' => array('class' => 'nav--icon'),
    );

    $title = theme_image($img) . '<span class="nav--text">' . t('Notifications') . '</span>' . $new_messages;

    $menutab = l($title, 'user/' . $GLOBALS['user']->uid . '/messages', array('attributes' => array('class' => array('nav--link')), 'html' => 'TRUE'));

  }
  else {
    $menutab = FALSE;
  }
  return $menutab;
}
