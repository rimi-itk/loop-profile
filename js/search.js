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
      url: '/loop_external_soruces/a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,x,y,z,æ,ø,å',
      // TTL 5 min.
      ttl: 30
    },
  });
  loopExternalSources.initialize();

  var documents = {
    // Pick source.
    source:  loopExternalSources.ttAdapter(),
    // Display field.
    displayKey: 'title',
    // HTML template for output.
    templates: {
      header: '<h3 class=\"tt-suggestion-header\">' + Drupal.t('External documents') + '</h3>',
      suggestion: Handlebars.compile('{{title}}')
    }
  };
  LoopSearch.push(documents);
});
