(function($) {
  $(function () {
    // Disable all submit buttons on submit to prevent multiple
    // submits.
    $('form.comment-form, form.node-post-form').on('submit', function() {
      $(this).find(':submit').prop('disabled', true);
    });
  });
})(jQuery);
