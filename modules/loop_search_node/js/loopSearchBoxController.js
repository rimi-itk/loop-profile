/**
 * @file
 * This is the main controller for the application.
 *
 * It controls the search box and filters.
 */

angular.module('searchBoxApp').controller('loopSearchBoxController', ['CONFIG', 'communicatorService', 'searchProxyService', '$scope', '$location', '$rootScope', '$window', '$document',
  function (CONFIG, communicatorService, searchProxyService, $scope, $location, $rootScope, $window, $document) {
    'use strict';

    // Set default search button text and state.
    $scope.searchBtnText = 'Search';
    $scope.searching = false;

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
     * Listen to location change event to handle (back/forward button).
     */
    $rootScope.$on('$locationChangeSuccess', function(newLocation, oldLocation) {
      $rootScope.actualHash = $location.hash();
    });

    /**
     *
     */
    $rootScope.$watch(function () {
      return $location.hash();
    }, function (newHash, oldHash) {
      if($rootScope.actualHash === newHash) {
        // @TODO: Figure out why promises stop working when the back/forward
        // buttons in the browser have been user. This is a HACK and hence the
        // code below is dead until we find a solution to promises.
        $window.location.reload();

        //// Get state from previous search.
        //var state = searchProxyService.getState();
        //
        //// Get filters.
        //$scope.filters = state.filters;
        //
        //// Set template to use.
        //$scope.template = CONFIG.templates.box;
        //
        //// Init the query object.
        //$scope.query = {
        //  'text': '',
        //  'filters': {}
        //};
        //
        //// Check if any intervals have been configured.
        //if (CONFIG.provider.hasOwnProperty('intervals')) {
        //  $scope.intervals = CONFIG.provider.intervals;
        //  $scope.query.intervals = {};
        //}
        //
        //// Check if any dates have been configured.
        //if (CONFIG.provider.hasOwnProperty('dates')) {
        //  $scope.dates = CONFIG.provider.dates;
        //  $scope.query.dates = {};
        //}
        //
        //// Check if any search query have been located from the hash tag.
        //if (state.hasOwnProperty('query')) {
        //  // Query found in state, so execute that search.
        //  $scope.query = state.query;
        //}
        //
        //search();
      }
    });

    /**
     * Execute the search and emit the results.
     */
    function search() {
      // Send info to results that a new search have started.
      communicatorService.$emit('searching', {});

      // Add sorting to the search query. It's added here to make it possible to
      // override or add sorting in search queries from the UI. If it was added
      // in the provider it would limit further sorting from the UI.
      if (CONFIG.provider.hasOwnProperty('sorting')) {
        $scope.query.sort = {};
        $scope.query.sort[CONFIG.provider.sorting.field] = CONFIG.provider.sorting.order;
      }

      // Start the search request.
      searchProxyService.search($scope.query).then(
        function (data) {
          // Updated filters.
          searchProxyService.getFilters().then(
            function (filters) {
              $scope.filters = filters;
            },
            function (reason) {
              console.error(reason);
            }
          );

          // Send results.
          $scope.searchBtnText = 'Search';
          $scope.searching = false;
          communicatorService.$emit('hits', {"hits": data});
        },
        function (reason) {
          console.error(reason);
        }
      );
    }

    /**
     * Initialize the controller and configure the basic scope.
     */
    function init() {
      // Get state from previous search.
      var state = searchProxyService.getState();

      // Set suggestion to empty.
      $scope.suggestions = {
        'show': false,
        'post': [],
        'external_sources': []
      };

      // Get filters.
      $scope.filters = state.filters;

      // Set template to use.
      $scope.template = CONFIG.templates.box;

      // Init the query object.
      $scope.query = {
        'text': '',
        'filters': {}
      };

      // Check if any intervals have been configured.
      if (CONFIG.provider.hasOwnProperty('intervals')) {
        $scope.intervals = CONFIG.provider.intervals;
        $scope.query.intervals = {};
      }

      // Check if any dates have been configured.
      if (CONFIG.provider.hasOwnProperty('dates')) {
        $scope.dates = CONFIG.provider.dates;
        $scope.query.dates = {};
      }

      // Check if any search query have been located from the hash tag.
      if (state.hasOwnProperty('query')) {
        // Query found in state, so execute that search.
        $scope.query = state.query;
        search();
      }
      else {
        // Check if the provider supports an pager.
        if (CONFIG.provider.hasOwnProperty('pager')) {
          // Add pager information to the search query.
          $scope.query.pager = angular.copy(CONFIG.provider.pager);
        }

        // Check if an initial search should be executed.
        if (CONFIG.hasOwnProperty('initialQueryText')) {
          $scope.query.text = angular.copy(CONFIG.initialQueryText);

          // Execute the search.
          search();
        }
        else {
          // Get filters based on search content (maybe slow).
          searchProxyService.getFilters().then(
            function (filters) {
              $scope.filters = filters;
            },
            function (reason) {
              console.error(reason);
            }
          );
        }
      }

      /**
       * Handle click event outside search area.
       *
       * Hide the suggestions box.
       */
      $document.bind('click', function(event){
        var element = angular.element('.search-box-block').find(event.target);
        if (element.length === 0 || element.hasClass('js-hide-suggest')) {
         $scope.suggestToggle(false);
        }
      });
    }

    /**
     * Updated search based on pager.
     */
    function pagerUpdated(data) {
      $scope.query.pager = {
        'size': data.size,
        'page': data.page
      };
      search();
    }

    /**
     * Communication listener for pager changes from the search results
     * application.
     */
    communicatorService.$on('pager', function (event, data) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        pagerUpdated(data);
      }
      else {
        $scope.$apply(function () {
          pagerUpdated(data);
        });
      }
    });

    /**
     * Search click handler.
     *
     * Simple wrapper for search that resets the pager before executing the
     * search.
     */
    $scope.searchClicked = function searchClicked() {
      $scope.searchBtnText = 'Searching...';
      $scope.searching = true;

      // If this is not the search page redirect to the search page with the
      // query.
      if (window.location.pathname != '/search') {
        window.location = '/search#/#text=' + $scope.query.text;
        return;
      }

      // Reset pager.
      if ($scope.query.hasOwnProperty('pager')) {
        $scope.query.pager = angular.copy(CONFIG.provider.pager);
      }

      search();
    };

    /**
     * Auto-complete callback.
     */
    $scope.autocomplete = function autocomplete() {
      // Update suggestion box.
      _suggestionSearch('external_sources');
      _suggestionSearch('post');

      if (CONFIG.provider.hasOwnProperty('autocomplete')) {
        $scope.autocompleteString = '';
        if ($scope.query.text.length >= CONFIG.provider.autocomplete.minChars) {
          searchProxyService.autocomplete($scope.query.text).then(
            function (data) {
              if (data.hits) {
                // Use regex to ensure cases (letters) are matched.
                var re = new RegExp('^' + $scope.query.text, 'i');
                var res = data.results[0][CONFIG.provider.autocomplete.field];
                $scope.autocompleteString = res.replace(re, $scope.query.text);
              }
              else {
                $scope.autocompleteString = '';
              }
            },
            function (reason) {
              console.error(reason);
            }
          );
        }
      }
    };

    /**
     * Toggle the suggestions drop-down box.
     */
    $scope.suggestToggle = function suggestToggle(display) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
        $scope.suggestions.show = display;
      }
      else {
        $scope.$apply(function () {
          $scope.suggestions.show = display;
        });
      }

      // Hide/show the auto-complete string based on toggle mode.
      if (!$scope.suggestions.show) {
        $scope.autocompletePrevString = $scope.autocompleteString;
        $scope.autocompleteString = '';
      }
      else {
        if (!$scope.hasOwnProperty('autocompletePrevString')) {
          $scope.autocomplete();
        }
        else {
          // Page may have been reload and no suggestions fetched. So try to execute
          // the current search.
          if (!$scope.suggestionExists()) {
            _suggestionSearch('external_sources');
            _suggestionSearch('post');
          }

          $scope.autocompleteString = $scope.autocompletePrevString;
        }
      }
    };

    /**
     * Helper to check if suggestions exists.
     *
     * @returns {boolean}
     *  If they do true else false.
     */
    $scope.suggestionExists = function suggestionExists() {
      if ($scope.suggestions['post'].length) {
        return true;
      }

      if ($scope.suggestions['external_sources'].length) {
        return true;
      }

      return false;
    };

    /**
     * Helper function to get search suggestions.
     *
     * @param type
     *   The content type to get suggestions for.
     *
     * @private
     */
    function _suggestionSearch(type) {
      var query = {
        index: '',
        query: {
          filtered: {
            query: {
              multi_match: {
                query: $scope.query.text,
                type: 'phrase',
                fields: [ 'body:summary', 'body:value', 'title'  ],
                analyzer: 'string_search'
              }
            },
            filter: {
              bool: {
                must: {
                  term: {
                    'type': type
                  }
                }
              }
            }
          }
        },
        size: 5,
        highlight: {
          pre_tags : [ "<strong>" ],
          post_tags : [ "</strong>" ],
          fields: {
            title: {}
          }
        }
      };

      // Start the search request.
      searchProxyService.rawQuerySearch(query).then(
        function (data) {

          console.log(data);

          var suggestions = [];

          for (var i = 0; i < data.results.length; i++) {
            var current = data.results[i];
            suggestions.push({
              'title': current._highlight.title[0],
              'url': current.url
            });
          }

          // Filter results based on types.
          $scope.suggestions[type] = suggestions;
        },
        function (reason) {
          console.error(reason);
        }
      );
    }

    /**
     * Resets the current search to default.
     */
    $scope.reset = function reset() {
      // Reset pager.
      if (CONFIG.provider.hasOwnProperty('pager')) {
        $scope.query.pager = angular.copy(CONFIG.provider.pager);
      }

      // Check if initial query exists.
      if (CONFIG.hasOwnProperty('initialQueryText')) {
        $scope.query.text = angular.copy(CONFIG.initialQueryText);

        search();
      }
      else {
        // No initial query.
        $scope.query.text = '';

        // Remove hits.
        communicatorService.$emit('hits', {"hits" : {}});
      }
    };

    // Get the show on the road.
    init();
  }
]);
