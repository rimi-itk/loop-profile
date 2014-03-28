/**
 *
 * Display notification action
 *
 */

(function($) {
  function display_notification_actions() {
    // Attach click function.
    $( ".js-user-profile-notification-select" ).click(function(){
      // Show actions.
      $('.js-user-profile-notification-actions').show();

      // Count the number of boxes checked.
      var boxes_checked = 0;
      $('.js-user-profile-notification-select:checked').each(function () {
        boxes_checked ++;
      });

      // If no boxes are checked, hide the actions.
      if (boxes_checked == 0) {
        $('.js-user-profile-notification-actions').hide();
      }
    });
  }

  function clear_selections() {
    // Attach click function.
    $( ".js-user-profile--notification-clear-all" ).click(function(){
      // Deselect all checkboxes.
      $('.js-user-profile-notification-select').attr('checked', false);

      // Hide actions.
      $('.js-user-profile-notification-actions').hide();
    });
  }

  // Start the show.
  $(document).ready(function () {
    display_notification_actions();
    clear_selections();
    $('.js-user-profile-notification-actions').hide();
  });
})(jQuery);
