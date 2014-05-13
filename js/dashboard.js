var dashboard = {
  questions: [],
  comments: [],
  other_content: [],

  question_template: '',
  comment_template: '',
  other_content_template: '',

  updateList: function(section) {
    if (section === 'questions') {
      questions.each(function() {
        console.log($(this));
      })
    }
  }
};

jQuery(document).ready(function($) {
  dashboard.question_template = Handlebars.compile(
    $("#js-list-item-template-question").html()
  );
  dashboard.comment_template = Handlebars.compile(
    $("#js-list-item-template-comment").html()
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
    dashboard.updateList('other_content');
  });
});
