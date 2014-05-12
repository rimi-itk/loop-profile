var LoopSearch = LoopSearch || [];
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
  loopQuestions.initialize();

  var questions = {
    // Pick source.
    source:  loopQuestions.ttAdapter(),
    // Display field.
    displayKey: 'title',
    // HTML template for output.
    templates: {
      header: '<h3 class=\"tt-suggestion-header\">' + Drupal.t('Questions') + '</h3>',
      suggestion: Handlebars.compile('{{title}}')
    }
  };
  LoopSearch.push(questions);
});
