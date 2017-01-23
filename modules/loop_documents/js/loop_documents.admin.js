if (typeof(Drupal.ajax) !== 'undefined') {
    Drupal.ajax.prototype.commands.loop_documents_setValue = function(ajax, response, status) {
        var $ = jQuery;
        var selector = response.arguments.selector;
        var value = response.arguments.value;

        var $el = $(selector);
        $el.val(value);
    };
}

// Prevent caching of autocomplete requests (cf. http://drupal.stackexchange.com/a/215761)
if (typeof(Drupal.ACDB.prototype.search) !== 'undefined') {
    Drupal.ACDB.prototype.search_original = Drupal.ACDB.prototype.search;
    Drupal.ACDB.prototype.search = function (searchString) {
        this.cache = [];
        this.search_original(searchString);
    };
}
