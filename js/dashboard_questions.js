(function ($) {

  var dq = {
  questions: [],
  display: [],
  template: '',
  filter: {
    title: '',
    answered: false,
    sorting: 'newest'
  },

  updateList: function() {
    dq.display = [];
    $.each(dq.questions, function(index, obj) {
      if (obj.title.toLowerCase().indexOf(dq.filter.title.toLowerCase()) >= 0) {
        dq.display.push(obj);
      }
      if (dq.display.length >= 5) {
        // Break each.
        return false;
      }
    });

    $(".js-dashboard-questions").html("");
    $.each(dq.display, function(index, obj) {
      $(".js-dashboard-questions").append(dq.template(obj));
    });
  }
};

$(document).ready(function($) {
  dq.template = Handlebars.compile(
    $("#js-list-item-template-questions").html()
  );
  $.get("/loop_dashboard_search_questions", function(data) {
    dq.questions = data;
    dq.updateList();
  });

  // Register event listeners for filters.
  $('.js-questions-unanswered').on('click', function() {
//    if ()
    dq.filter.answered = false;
    updateList
  });

  //$('.s-questions-answer-filter').removeClass('is-active');

});

})(jQuery);