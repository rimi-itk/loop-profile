(function ($) {

  var dashboard_comments = {
  comments: [],
  template: '',

  updateList: function() {
    $(".js-dashboard-comments").html("");
    $.each(dashboard_comments.comments, function(index, obj) {
      $(".js-dashboard-comments").append(dashboard_comments.template(obj));
    });
  }
};

$(document).ready(function($) {
  dashboard_comments.template = Handlebars.compile(
    $("#js-list-item-template-comments").html()
  );
  $.get("/loop_dashboard_search_comments", function(data) {
    dashboard_comments.comments = data;
    dashboard_comments.updateList();
  });
});

})(jQuery);