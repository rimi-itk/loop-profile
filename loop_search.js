/**
 * @file
 * Autocomplete attachement for search in Apache Solr.
 */


/**
 * Adds the custom autocomplete widget behavior.
 */
Drupal.behaviors.loop_search = {
  attach: function(context) {
    jQuery('.typeahead', context).typeahead(
      {
        // The autocomplete url.
        remote: '/loop_search_autocomplete/%QUERY',

        // Name of search.
        name: 'search',

        // The template we are building suggestion list from.
        template: [
          '<span>{{link}}</span>',
          '<span>{{value}}</span>',
          '<span>{{suggestion}}</span>'
        ].join(''),

        // Template enigne.
        engine: Hogan
      }
    );
  }
};

jQuery(document).ready(function($) {
  $('.typeahead').on('typeahead:selected', function (object, datum) {
    // If suggestion contains a link. Redirect.
    if (datum['link'] != undefined) {
      window.location = datum['link'];
    }
    else {
      // Suggestion is clicked. Display the results.
      $('.typeahead').blur();
      $('.typeahead').focus();
    }
  });
});