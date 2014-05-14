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

    sortByFilter: function(a, b) {
      if (dq.filter.sorting === 'newest') {
        return ((a.ts < b.ts) ? 1 : ((a.ts > b.ts) ? -1 : 0));
      }
      else if (dq.filter.sorting === 'oldest') {
        return ((a.ts < b.ts) ? -1 : ((a.ts > b.ts) ? 1 : 0));
      }
      else if (dq.filter.sorting === 'alphabetic') {
        a = a.title.toLowerCase();
        b = b.title.toLowerCase();
        return ((a < b) ? -1 : ((a > b) ? 1 : 0));
      }
      else if (dq.filter.sorting === 'comments') {
        return ((a.coms < b.coms)) ? -1 : (a.coms > b.coms) ? 1 : 0;
      }
    },

    updateList: function() {
      dq.display = [];

      // Sort according to filter.
      dq.questions.sort(dq.sortByFilter);

      // Get 5 elements according to
      $.each(dq.questions, function(index, obj) {
        var gt_zero_comments = (obj.coms > 0) ? true : false;

        if (obj.title.toLowerCase().indexOf(dq.filter.title.toLowerCase()) >= 0 &&
            gt_zero_comments === dq.filter.answered) {
          dq.display.push(obj);
        }
        if (dq.display.length >= dq.filter.items) {
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

    $('.js-questions-sort-newest').on('click', function(event) {
      event.preventDefault();
      if (!dq.filter.sorting !== 'newest') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-newest').addClass('is-active');

        dq.filter.sorting = 'newest';
        dq.updateList();
      }
    });
    $('.js-questions-sort-oldest').on('click', function(event) {
      event.preventDefault();
      if (dq.filter.sorting !== 'oldest') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-oldest').addClass('is-active');

        dq.filter.sorting = 'oldest';
        dq.updateList();
      }
    });
    $('.js-questions-sort-alphabetic').on('click', function(event) {
      event.preventDefault();
      if (!dq.filter.sorting !== 'alphabetic') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-alphabetic').addClass('is-active');

        dq.filter.sorting = 'alphabetic';
        dq.updateList();
      }
    });
    $('.js-questions-sort-comments').on('click', function(event) {
      event.preventDefault();
      if (!dq.filter.sorting !== 'comments') {
        $('.js-questions-sort-filter').removeClass('is-active');
        $('.js-questions-sort-comments').addClass('is-active');

        dq.filter.sorting = 'comments';
        dq.updateList();
      }
    });
  });

})(jQuery);