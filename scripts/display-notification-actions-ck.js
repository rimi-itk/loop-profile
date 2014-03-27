/**
 *
 * Display notification action
 *
 */(function(e){function t(){e(".js-user-profile-notification-select").click(function(){e(".js-user-profile-notification-actions").show("slow");var t=0;e(".js-user-profile-notification-select:checked").each(function(){t++});t==0&&e(".js-user-profile-notification-actions").hide("slow")})}function n(){e(".js-user-profile--notification-clear-all").click(function(){e(".js-user-profile-notification-select").attr("checked",!1);e(".js-user-profile-notification-actions").hide("slow")})}e(document).ready(function(){e(".js-user-profile-notification-actions").hide();t();n()})})(jQuery);