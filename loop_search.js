/**
 * @file
 * Autocomplete attachement for search in Apache Solr.
 */


/**
 * Adds the custom autocomplete widget behavior.
 */
Drupal.behaviors.loop_search = {
  attach: function(context) {
    jQuery('.js-autocomplete-search--field', context).autocomplete({
      // The autocomplete url.
      serviceUrl: Drupal.settings.loop_search_autocomplete.path,

      // The class we append to.
      appendTo: '.js-autocomplete-search',

      // Fix to remove inline styling.
      beforeRender: function(container) {
        jQuery(container[0]).removeAttr('style');
      },

      // When search is complete, add a header.
      onSearchComplete: function() {
        if (jQuery('.js-autocomplete-header').length === 0) {
          jQuery('.js-autocomplete-search').prepend('<h4 class="autocomplete-header js-autocomplete-header">' + Drupal.t('Questions others have asked') + '</h4>');
        }
        jQuery('.js-autocomplete-search').show();
      },

      // When item is selected, redirect.
      onSelect: function (suggestion) {
          window.location = suggestion.data;
      }
    });
  }
};
