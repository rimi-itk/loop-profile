/**
 * @file
 * Autocomplete attachement for search in Drupal.
 */

/**
 * Default ready function.
 *
 * Prefetch nodes.
 * Start typeahead.
 */
jQuery(document).ready(function($) {
  var settings = {
    highlight: true
  };

  LoopSearch.unshift(settings);

  // Apply our global search Bloodhound(s).
  $('.typeahead').typeahead.apply($('.typeahead'), LoopSearch);

  $('.typeahead').on('typeahead:selected', function (object, datum) {
    // If suggestion contains a link. Redirect.
    if (datum.link !== undefined) {
      var full_host = location.protocol + '//' + location.host;
      alert('1' + full_host);
      alert('2' + url_domain(datum.link)); //         /user
      alert('3' + url_domain(window.location));   //              /test
      // Open external links in a new window.
      if (url_domain(datum.link) != url_domain(window.location)) {
        alert('aaa');
        window.open(datum.link);
      }
      else {
        window.location = datum.link;
        alert('bbb');
      }
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

/**
 * Helper function to get hostname of a link.
 *
 * @param data
 *   Full link.
 *
 * @returns {string}
 *   Hostname of full link.
 */
function url_domain(data) {
  var a = document.createElement('a');
  a.href = data;
  alert('test---' + a.hostname);
  return a.hostname;
}
