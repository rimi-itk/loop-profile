/**
 *
 * Mobile navigation
 *
 */

(function($) {

  function show_answers_sort() {
    // Add answers button
    $('.js-dashboard-answers').removeClass('is-hidden');
    $('.js-dashboard-alphabetical').removeClass('is-last');

    // Adjust width
    $('.js-sort-link').toggleClass('js-has-answers-removed');
  }

  function hide_answers_sort() {
    // Remove answers button
    $('.js-dashboard-answers').addClass('is-hidden');
    $('.js-dashboard-alphabetical').addClass('is-last');

    // Adjust width
    $('.js-sort-link').toggleClass('js-has-answers-removed');
  }


  // Toggle mobile navigation
  function set_active() {
    // When answered questions link is clicked
    $('.js-dashboard-answers-show').click(function() {
      show_answers_sort();

      // Set/remove active class
      $('.dashboard--filter-link').toggleClass('is-active');
    });


    // When unanswered questions link is clicked
    $('.js-dashboard-answers-hide').click(function() {
      hide_answers_sort();

      // Set/remove active class
      $('.dashboard--filter-link').toggleClass('is-active');
    });


    // When a sort link link is clicked
    $('.dashboard--sort-link').click(function() {

      // Set / remove active class
      $('.dashboard--sort-link').removeClass('is-active');
      $(this).addClass('is-active');
    });
  }

  // Start the show
  /*$(document).ready(function () {
    alert('123');
    // Hide and store answers button
    $('.js-dashboard-answers').addClass('is-hidden');
    $('.js-dashboard-alphabetical').addClass('is-last');

    // Add class to links to define width in css
    $('.js-sort-link').toggleClass('js-has-answers-removed');

    // Add som click events
    set_active();
  });*/

  Drupal.behaviors.myBehavior = {
    attach: function (context, settings) {
      // Hide and store answers button
      $('.js-dashboard-answers').addClass('is-hidden');
      $('.js-dashboard-alphabetical').addClass('is-last');

      // Add class to links to define width in css
      $('.js-sort-link').toggleClass('js-has-answers-removed');

      // Add som click events
      set_active();

      // First we use the settings object to get the views' details
      var views = settings.views.ajaxViews;

      // view_dom_id is an unique value, it's unique per view and per pageload
      var view = view_dom_id = view_name = undefined;
      for (var viewsName in views) {
        if (views.hasOwnProperty(viewsName)) {
          view = views[viewsName];
          // I used view_display_id to actually identify my view
          // and store it in the view variable
          if (view['view_display_id'] == "panel_pane_1") {
            view_name = view["view_name"];
            view_dom_id = view["view_dom_id"];
          }
        }
      }
      console.log(view_name);
      console.log(view_dom_id);
    }
  };
})(jQuery);
