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
    if (datum.link != undefined) {
      if (navigator.userAgent.indexOf('MSIE') !== -1 || navigator.appVersion.indexOf('Trident/') > 0) {
        var is_msie = 1;
        var domain = 'stg-loop.etek.dk';
      } else {
        var domain = url_domain(datum.link);
      }
      alert('1' + window.location.hostname);
      alert('2' + domain);
      alert('3' + url_domain(window.location));
      // Open external links in a new window.
      if (domain != url_domain(window.location)) {
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
  return a.hostname;
}
