(function ($) {

  var dq = {
  questions: [],
  display: [],
  template: '',
  filter: {
    title: '',
    answered: false,
    sorting: 'newest',
    items: 5
  },

  updateList: function() {
    dq.display = [];

    // Get 5 elements according to
    $.each(dq.questions, function(index, obj) {
      if (obj.title.toLowerCase().indexOf(dq.filter.title.toLowerCase()) >= 0) {
        dq.display.push(obj);
      }
      if (dq.display.length >= dq.filter.items) {
        // Break each.
        return false;
      }
    });

    // Sort according to filter.

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
  $('.js-questions-unanswered').on('click', function(event) {
    event.preventDefault();
    if (dq.filter.answered) {
      $('.js-questions-answer-filter').removeClass('is-active');
      $('.js-questions-unanswered').addClass('is-active');

      dq.filter.answered = false;
      dq.updateList();
    }
  });
  $('.js-questions-answered').on('click', function(event) {
    event.preventDefault();
    if (!dq.filter.answered) {
      $('.js-questions-answer-filter').removeClass('is-active');
      $('.js-questions-answered').addClass('is-active');

      dq.filter.answered = true;
      dq.updateList();
    }
  });


});

})(jQuery);