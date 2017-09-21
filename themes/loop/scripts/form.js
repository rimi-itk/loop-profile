(function($) {
  $(function () {
    // Disable all submit buttons on submit to prevent multiple
    // submits.
    $('form').on('submit', function() {
      $(this).find('[type="submit"]').prop('disabled', true);
    });
  });
})(jQuery);
