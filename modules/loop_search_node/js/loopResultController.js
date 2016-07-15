/**
 * @file
 * This is the controller for the search result application.
 *
 * It simply updates the view when hits have been received.
 */

angular.module('searchResultApp').controller('loopResultController', ['CONFIG', 'communicatorService', '$scope', '$window', '$http',
  function (CONFIG, communicatorService, $scope, $window, $http) {
    'use strict';

    // Set template to use.
    $scope.template = CONFIG.templates.result;

    // Scope variable that can be used to make indications on the current
    // process. E.g display spinner.
    $scope.searching = false;

    // Check if the provider supports an pager.
    if (CONFIG.provider.hasOwnProperty('pager')) {
      // Add pager information to the scope.
      $scope.pager = angular.copy(CONFIG.provider.pager);
    }

    /**
     * Expose the Drupal.t() function to angular templates.
     *
     * @param str
     *   The string to translate.
     * @returns string
     *   The translated string.
     */
    $scope.Drupal = {
      "t": function t(str, args, options) {
        return $window.Drupal.t(str, args, options);
      }
    };

    /**
     * Update pager information.
     */
    $scope.search = function search() {
      communicatorService.$emit('pager', $scope.pager);
    };

    /**
     * Hanled search results hits from the search box application.
     */
    $scope.hits = [];
    communicatorService.$on('hits', function onHits(event, data) {
      // Ensure that hits titles are stream lined.
      var hits = data.hits;
      for (var i in hits.results) {
       if (hits.results[i].hasOwnProperty('_highlight')) {
          hits.results[i].title = hits.results[i]._highlight.title[0];
        }
      }

      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        $scope.hits = hits;
        $scope.searching = false;

        if ($scope.hits.hits === 0) {
          no_results_post_form();
        }
      }
      else {
        $scope.$apply(function () {
          $scope.hits = hits;
          $scope.searching = false;

          if ($scope.hits.hits === 0) {
            no_results_post_form();
          }
        });
      }
    });

    /**
     * Hanled searching message, send when search is called.
     */
    communicatorService.$on('searching', function onSearching(event, data) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        $scope.searching = true;
      }
      else {
        $scope.$apply(function () {
          $scope.searching = true;
        });
      }
    });

    /**
     * Handled pager updates.
     */
    communicatorService.$on('pager', function onPager(event, data) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        $scope.pager = data;
      }
      else {
        $scope.$apply(function () {
          $scope.pager = data;
        });
      }
    });

    /**
     * Callback to get the "no results found" create new post form.
     */
    function no_results_post_form() {
      $http({
        method: 'GET',
        url: '/loop_search_node/not_found'
      }).then(function successCallback(response) {
        document.getElementById('no_result_form').innerHTML = response.data.form;

        jQuery('.js-chosen-select-area-of-expertise').chosen({
          no_results_text: "Angiv værdi.",
          placeholder_text : "Angiv værdi."
        });

        jQuery('.js-chosen-select-profession').chosen({
          no_results_text: "Angiv værdi.",
          placeholder_text : "Angiv værdi."
        });

        // Make auto-comaple delux work (hackise).
        Drupal.settings.autocomplete_deluxe = response.data.settings[1].data.autocomplete_deluxe;
        jQuery.getScript(response.data.settings[0], function() {
          Drupal.attachBehaviors();
        });
      });
    }
  }
]);
