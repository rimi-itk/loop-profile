<?php

/**
 * @file
 * Missing comment.
 */

$plugin = array(
// Just do this one, it is needed.
  'single' => TRUE,
// A category to put this under.
  'category' => t('Miscellaneous'),
// Title to show up on the pane screen.
  'title' => t('Notify friend'),
// Description to show up on the pane screen.
  'description' => t('Notify a friend of a node, sending that friend a message'),
// A function that will return the settings form for the pane.
  'edit form' => 'loop_friend_notification_pane_custom_pane_edit_form',
// A function that will return the renderable content.
  'render callback' => 'loop_friend_notification_pane_custom_pane_render',
// A function that will return the information displayed on the admin screen
// (optional).
  'admin info' => 'loop_friend_notification_pane_custom_pane_admin_info',
// Array of defaults for the settings form.
  'defaults' => array(
    'text' => '',
  ),
// This is NEEDED to be able to use substitution strings in your pane.
  'all contexts' => TRUE,
);
