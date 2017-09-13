/**
 * Created with JetBrains PhpStorm.
 * User: martinydegranath
 * Date: 07/04/14
 * Time: 10.22
 * To change this template use File | Settings | File Templates.
 */



(function ($) {
  // Start the show.
  Drupal.behaviors.subscriptions = {
    attach: function (context, settings) {
      $(".subscriptions--item").each(function ()  //<-- start of new scope block
      {
        var label = $(this).find(".label");
        var text = label.text();
        $(this).find("a").text(text);

        label.hide();
      });
    }
  }
})(jQuery);