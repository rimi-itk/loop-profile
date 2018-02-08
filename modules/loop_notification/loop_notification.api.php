<?php

/**
 * @file
 * Hooks provided by the Notification module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Modify an array of message recipients before creating a notification.
 *
 * @param array $users
 *   An array of user IDs (uid) to receive notification.
 * @param object $node
 *   The node that triggered the notification to be send.
 */
function hook_loop_notification_message_recipient_alter(array &$users, $node) {
  $user_ids = array();
  $user_ids[] = '1';
  $users += $user_ids;
}

/**
 * @} End of "addtogroup hooks".
 */
