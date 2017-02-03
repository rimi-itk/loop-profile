(function($) {
  $(document).ready(function () {
    $(".js-toggle").click(function(){
      $(this).toggleClass("is-shown");
      $(".js-toggle-data").toggleClass("is-shown");
    })
  });
})(jQuery);