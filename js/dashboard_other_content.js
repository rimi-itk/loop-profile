(function ($) {

  var dashboard_other_content = {
  other_content: [],
  template: '',

  updateList: function() {
    $(".js-dashboard-other-content").html("");
    $.each(dashboard_other_content.other_content, function(index, obj) {
      $(".js-dashboard-other-content").append(dashboard_other_content.template(obj));
    });
  }
};

$(document).ready(function($) {
  dashboard_other_content.template = Handlebars.compile(
    $("#js-list-item-template-other-content").html()
  );
  $.get("/loop_dashboard_search_other_content", function(data) {
    dashboard_other_content.other_content = data;
    dashboard_other_content.updateList();
  });
});

})(jQuery);