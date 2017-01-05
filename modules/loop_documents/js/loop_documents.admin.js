if (typeof(Drupal.ajax) !== 'undefined') {
    Drupal.ajax.prototype.commands.loop_documents_setDocumentOptions = function(ajax, response, status) {
        var $ = jQuery;
        var selector = response.arguments.selector;
        var options = response.arguments.options;

        var $el = $(selector);
        $el.empty();
        $.each(options, function(value, key) {
            $el.append($("<option></option>")
                       .attr('value', value).text(key));
        });
    };
}
