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
          '<p class=""repo-desc">{{value}}</p>'
        ].join(''),

        // Template enigne.
        engine: Hogan
      }
    );
  }
};

jQuery(document).ready(function($) {
  // When a suggestion is clicked/selected. Redirect to that item.
  $('.js-autocomplete-search--field').on('typeahead:selected', function (object, datum) {
    window.location = datum['link'];
  });
});