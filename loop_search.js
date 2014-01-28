/**
 * @file
 * Autocomplete attachement for search in Apache Solr.
 */


/**
 * Adds the custom autocomplete widget behavior.
 */
Drupal.behaviors.loop_search = {
  attach: function(context) {
    jQuery('.js-autocomplete-search--field', context).typeahead(
      {
        // The autocomplete url.
        remote: Drupal.settings.loop_search_autocomplete.path + '/%QUERY',

        // Name of search.
        name: 'search',

        // The template we are building suggestion list from.
        template: [
          '<p class="repo-link">{{link}}</p>',
          '<p class="repo-desc">{{value}}</p>',
          '<p class="repo-click">{{suggestion}}</p>'
        ].join(''),

        // Template enigne.
        engine: Hogan
      }
    );
  }
};

jQuery(document).ready(function($) {
  $('.js-autocomplete-search--field').on('typeahead:selected', function (object, datum) {
    // If suggestion contains a link. Redirect.
    if (datum['link'] != undefined) {
      window.location = datum['link'];
    }
    else {
      // Suggestion is clicked. Display the results.
      $('.js-autocomplete-search--field').blur();
      $('.js-autocomplete-search--field').focus();
    }
  });
});