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
  var loopSearch = new Bloodhound({
    datumTokenizer: function(d) {
      // Tokenize by splitting whitespace.
      return Bloodhound.tokenizers.whitespace(d.value);
    },
    queryTokenizer: Bloodhound.tokenizers.whitespace,
    prefetch:  {
      // URL for prefetch!
      url: '/loop_search_nodes',
      ttl: 300000
    },
    name: 'search'
  });

  loopSearch.initialize();

  jQuery('.typeahead').typeahead(
    {
      highlight: true,
    },
    {
      // Bloodhound source.
      source: loopSearch.ttAdapter(),

      // Name of search.
      name: 'search',

      // Display field.
      displayKey: 'title',

      templates: {
        suggestion: Handlebars.compile(
          '{{title}}'
        )
      }
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