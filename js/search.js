var LoopSearch = LoopSearch || [];
jQuery(document).ready(function($) {

  var loopExternalSources = new Bloodhound({
    datumTokenizer: function(d) {
      // Tokenize by splitting whitespace.
      return Bloodhound.tokenizers.whitespace(d.value);
    },
    queryTokenizer: Bloodhound.tokenizers.whitespace,
    prefetch:  {
      // URL to fetch.
      url: '/loop_knowledge',
      // TTL 30 sec.
      ttl: 30000
    }
  });
  loopExternalSources.initialize();

  var documents = {
    // Pick source.
    source:  loopExternalSources.ttAdapter(),
    // Display field.
    displayKey: 'title',
    // HTML template for output.
    templates: {
      header: '<h3 class=\"tt-suggestion-header\">' + Drupal.t('Vejledning') + '</h3>',
      suggestion: Handlebars.compile('{{title}}')
    }
  };
  LoopSearch.push(documents);
});
