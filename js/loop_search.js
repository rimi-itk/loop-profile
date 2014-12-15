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
      // Open external links in a new window.
      alert(url_domain(datum.link));
      alert(url_domain(window.location));
      if (url_domain(datum.link) !== url_domain(window.location)) {
        alert('1');
        window.open(datum.link);
      }
      else {
        alert('2');
        window.location = datum.link;
      }
    }
    else {
      alert('3');
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
  var full_host = location.protocol + '//' + location.host;
  if (data.indexOf('http') < 0) {
    data = full_host + data;
  }
  var a = document.createElement('a');
  a.href = data;
  return a.hostname;
}
