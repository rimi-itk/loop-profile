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
  var loopQuestions = new Bloodhound({
    datumTokenizer: function(d) {
      // Tokenize by splitting whitespace.
      return Bloodhound.tokenizers.whitespace(d.value);
    },
    queryTokenizer: Bloodhound.tokenizers.whitespace,
    prefetch:  {
      // URL to fetch.
      url: '/loop_search_nodes',
      // TTL 5 min.
      ttl: 300000
    },
  });

  var loopDocuments = new Bloodhound({
    datumTokenizer: function(d) {
      // Tokenize by splitting whitespace.
      return Bloodhound.tokenizers.whitespace(d.value);
    },
    queryTokenizer: Bloodhound.tokenizers.whitespace,
    prefetch:  {
      // URL to fetch.
      url: '/loop_search_documents/a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,x,y,z,æ,ø,å',
      // TTL 1 day.
      ttl: 86400000
    },
  });

  // Fire up our badboys!
  loopQuestions.initialize();
  loopDocuments.initialize();

  jQuery('.typeahead').typeahead(
    {
      highlight: true,
    },
    {
      // Pick source.
      source: loopDocuments.ttAdapter(),
      // Display field.
      displayKey: 'title',
      // HTML template for output.
      templates: {
        header: '<h3 class="tt-suggestion-header">' + Drupal.t('Documents') + '</h3>',
        suggestion: Handlebars.compile('{{title}}')
      }
    },
    {
      // Pick source.
      source: loopQuestions.ttAdapter(),
        // Display field.
        displayKey: 'title',
      // HTML template for output.
      templates: {
      header: '<h3 class="tt-suggestion-header">' + Drupal.t('Questions') + '</h3>',
        suggestion: Handlebars.compile('{{title}}')
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

  // On search form submit disable submit button.
  $('form.js--search').submit(function () {
    $(this).find('[type=submit]')
      .attr('disabled', true)
      .val(Drupal.t('Searching ...'));
  });
});
