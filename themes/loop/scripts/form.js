(function($) {
  $(function () {
    // Disable all submit buttons on submit to prevent multiple
    // submits.
    // Using the "submit" event on the form is too slow (late), so we
    // use the "click" event on the button itself.
    $('form [type="submit"]').on('click', function() {
      $(this).closest('form').find('[type="submit"]').prop('disabled', true);
    });
  });
})(jQuery);
