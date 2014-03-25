/**
 *
 * Update new notifications.
 *
 * Javascript used to update the new notifications number when a message changes status to read.
 *
 */(function(e){function t(){e(".js-notification-count").on("click",".js-message--flag",function(){var t=e(".js-user-message-count").data("new-message-count")-1;e(".js-notification-tab-count").text(t)})}e(document).ready(function(){t()})})(jQuery);