(function ($) {

  var dashboard = {
  questions: [],
  comments: [],
  other_content: [],

  question_template: '',
  comment_template: '',
  other_content_template: '',

  updateList: function(section) {
    if (section === 'questions') {
      $(".js-dashboard-questions").each(function() {
        $(this).html("");
      });
      $.each(dashboard.questions, function(index, obj) {
        $(".js-dashboard-questions").append(dashboard.question_template(obj));
      });
    }
    else if (section === 'comments') {
      $(".js-dashboard-comments").each(function() {
        $(this).html("");
      });
      $.each(dashboard.comments, function(index, obj) {
        $(".js-dashboard-comments").append(dashboard.comment_template(obj));
      });
    }
    else if (section === 'other-content') {
      $(".js-dashboard-other-content").each(function() {
        $(this).html("");
      });
      $.each(dashboard.other_content, function(index, obj) {
        $(".js-dashboard-other-content").append(dashboard.other_content_template(obj));
      });
    }
  }
};

$(document).ready(function($) {

  dashboard.question_template = Handlebars.compile(
    $("#js-list-item-template-questions").html()
  );

  dashboard.comment_template = Handlebars.compile(
    $("#js-list-item-template-comments").html()
  );
  dashboard.other_content_template = Handlebars.compile(
    $("#js-list-item-template-other-content").html()
  );

  $.get( "/loop_dashboard_search_questions", function( data ) {
    dashboard.questions = data;
    dashboard.updateList('questions');
  });
  $.get( "/loop_dashboard_search_comments", function( data ) {
    dashboard.comments = data;
    dashboard.updateList('comments');
  });
  $.get( "/loop_dashboard_search_other_content", function( data ) {
    dashboard.other_content = data;
    dashboard.updateList('other-content');
  });
});

})(jQuery);