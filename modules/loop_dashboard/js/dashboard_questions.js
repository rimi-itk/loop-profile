/**
 * @file
 * Containing class for the functionality of the filter.
 */
(function ($) {
  "use strict";

  var dashboardQuestions = {
    unansweredCount: 0,
    answeredCount: 0,
    questions: [],
    display: [],
    template: '',
    filter: {
      title: '',
      answered: false,
      sorting: 'newest',
      items: 5
    },

    /**
     * Defines the different filters.
     */
    sortByFilter: function(a, b) {
      if (dashboardQuestions.filter.sorting === 'newest') {
        return ((a.ts < b.ts) ? 1 : ((a.ts > b.ts) ? -1 : 0));
      }
      else if (dashboardQuestions.filter.sorting === 'oldest') {
        return ((a.ts < b.ts) ? -1 : ((a.ts > b.ts) ? 1 : 0));
      }
      else if (dashboardQuestions.filter.sorting === 'alphabetic') {
        a = a.title.toLowerCase();
        b = b.title.toLowerCase();
        return ((a < b) ? -1 : ((a > b) ? 1 : 0));
      }
      else if (dashboardQuestions.filter.sorting === 'comments') {
        return ((a.coms < b.coms)) ? 1 : (a.coms > b.coms) ? -1 : 0;
      }
    },

    /**
     * Function to call every time the display list should be updated.
     */
    updateList: function() {
      dashboardQuestions.display = [];

      // Sort according to filter.
      dashboardQuestions.questions.sort(dashboardQuestions.sortByFilter);

      // Get 5 elements according to
      $.each(dashboardQuestions.questions, function(index, obj) {
        var gt_zero_comments = (obj.coms > 0) ? true : false;

        if (obj.title.toLowerCase().indexOf(dashboardQuestions.filter.title.toLowerCase()) >= 0 &&
            gt_zero_comments === dashboardQuestions.filter.answered) {
          dashboardQuestions.display.push(obj);
        }
        if (dashboardQuestions.display.length >= dashboardQuestions.filter.items) {
          // Break each.
          return false;
        }
      });

      $(".js-dashboard-questions").html("");
      $.each(dashboardQuestions.display, function(index, obj) {
        $(".js-dashboard-questions").append(dashboardQuestions.template(obj));
      });
    },

    /**
     * Helper function to set the class of the filter buttons.
     * This depends on whether answered/unanswered questions should be displayed.
     */
    setFilterButtonSizes: function() {
      if (!dashboardQuestions.filter.answered) {
        $('.js-questions-sort-filter').addClass('js-has-answers-removed');
        $('.js-questions-sort-comments').addClass('is-hidden');
        $('.js-questions-sort-alphabetic').addClass('is-last');
      } else {
        $('.js-questions-sort-filter').removeClass('js-has-answers-removed');
        $('.js-questions-sort-comments').removeClass('is-hidden');
        $('.js-questions-sort-alphabetic').removeClass('is-last');
      }
    }
  };


  $(document).ready(function($) {
    // Load the template for each entry.
    dashboardQuestions.template = Handlebars.compile(
      $("#js-list-item-template-questions").html()
    );

    // Load the data from the backend.
    $.get("/loop_dashboard_search_questions", function(data) {
      dashboardQuestions.questions = data;

      dashboardQuestions.answeredCount = 0;
      dashboardQuestions.unansweredCount = 0;

      for (var question in dashboardQuestions.questions) {
        question = dashboardQuestions.questions[question];
        if (question.coms > 0) {
          dashboardQuestions.answeredCount++;
        }
        else {
          dashboardQuestions.unansweredCount++;
        }
      }

      console.log(dashboardQuestions.unansweredCount);
      console.log(dashboardQuestions.answeredCount);

      $(".dashboard--questions-count-unanswered").replaceWith('<span>' + dashboardQuestions.unansweredCount + '</span>');
      $(".dashboard--questions-count-answered").replaceWith('<span>' + dashboardQuestions.answeredCount + '</span>');
      
      dashboardQuestions.updateList();
    });

    // Register event listeners for filters.
    $('.js-questions-unanswered').on('click', function(event) {
      event.preventDefault();
      if (dashboardQuestions.filter.answered) {
        $('.js-questions-answer-filter').removeClass('is-active');
        $('.js-questions-unanswered').addClass('is-active');
        $('.js-questions-sort-comments').addClass('is-hidden');
        if (dashboardQuestions.filter.sorting === 'comments') {
          dashboardQuestions.filter.sorting = 'newest';

        }

        dashboardQuestions.filter.answered = false;
        dashboardQuestions.setFilterButtonSizes();
        dashboardQuestions.updateList();
      }
    });
    $('.js-questions-answered').on('click', function(event) {
      event.preventDefault();
      if (!dashboardQuestions.filter.answered) {
        $('.js-questions-answer-filter').removeClass('is-active');
        $('.js-questions-answered').addClass('is-active');

        dashboardQuestions.filter.answered = true;
        dashboardQuestions.setFilterButtonSizes();
        dashboardQuestions.updateList();
      }
    });
    $('.js-questions-sort-newest').on('click', function(event) {
      event.preventDefault();
      if (!dashboardQuestions.filter.sorting !== 'newest') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-newest').addClass('is-active');

        dashboardQuestions.filter.sorting = 'newest';
        dashboardQuestions.updateList();
      }
    });
    $('.js-questions-sort-oldest').on('click', function(event) {
      event.preventDefault();
      if (dashboardQuestions.filter.sorting !== 'oldest') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-oldest').addClass('is-active');

        dashboardQuestions.filter.sorting = 'oldest';
        dashboardQuestions.updateList();
      }
    });
    $('.js-questions-sort-alphabetic').on('click', function(event) {
      event.preventDefault();
      if (!dashboardQuestions.filter.sorting !== 'alphabetic') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-alphabetic').addClass('is-active');

        dashboardQuestions.filter.sorting = 'alphabetic';
        dashboardQuestions.updateList();
      }
    });
    $('.js-questions-sort-comments').on('click', function(event) {
      event.preventDefault();
      if (!dashboardQuestions.filter.sorting !== 'comments') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-comments').addClass('is-active');

        dashboardQuestions.filter.sorting = 'comments';
        dashboardQuestions.updateList();
      }
    });

    $('.js-questions-text-filter').on('keyup', function(event) {
      event.preventDefault();
      dashboardQuestions.filter.title = $(this).val();
      dashboardQuestions.updateList();
    });
  });

})(jQuery);
