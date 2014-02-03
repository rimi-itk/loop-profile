/**
 * @file
 * Autocomplete attachement for search in Apache Solr.
 */

/**
 * Default ready function.
 *
 * Prefetch nodes.
 * Start typeahead.
 */
jQuery(document).ready(function($) {
  var testing = new Bloodhound({
    datumTokenizer: function(d) {
      // Tokenize by splitting whitespace.
      return Bloodhound.tokenizers.whitespace(d.value);
    },
    queryTokenizer: Bloodhound.tokenizers.whitespace,
    prefetch:  {
      // URL for prefetch!
      url: '/loop_search_nodes'
    },
    name: 'search'
  });

  testing.initialize();

  jQuery('.typeahead').typeahead(null,
    {
      // Bloodhound source.
      source: testing.ttAdapter(),

      // Name of search.
      name: 'search',

      // Display field.
      displayKey: 'title',

      // The template we are building suggestion list from.
      template: [
        '<span>{{link}}</span>',
        '<span>{{title}}</span>'
      ].join(''),

      // Template enigne.
      engine: Hogan
    }
  );


  $('.typeahead').on('typeahead:selected', function (object, datum) {
    // If suggestion contains a link. Redirect.
    if (datum['link'] != undefined) {
      window.location = datum['link'];
    }
    else {
      // Suggestion is clicked. Display the results.
      $('.typeahead').blur().focus();
    }
  });
});