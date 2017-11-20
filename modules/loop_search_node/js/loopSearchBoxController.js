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
    $scope.selectedFilterCount = 0;
    $scope.filterActive = 'all';
    $scope.sortActive = 'desc';
    $scope.showSort = false;
    $scope.newSubjects = false;

    /**
     * Handle toggling of the search filter.
     */
    $scope.isFiltersShown = false;
    $scope.toggleFilter = function () {
      $scope.isFiltersShown = !$scope.isFiltersShown;

      if ($scope.newSubjects) {
        $scope.newSubjects = false;
        $scope.searchClicked(true);
      }
    };

    /**
     * Set flag when new subject filters are selected.
     */
    $scope.filterNewSelection = function filterNewSelection() {
      $scope.newSubjects = true;
    };

    // Defines the document filter type.
    var documentFilter = {
      'loop_documents_document': true,
      'loop_documents_collection': true,
      'external_sources': true
    };

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
         $window.location.reload();
      }
    });

    /**
     * Execute the search and emit the results.
     *
     * @param {boolean} scrollToTop
     *   If TRUE the page i scrolled to the top else not.
     */
    function search(scrollToTop) {
      // Send info to results that a new search have started.
      communicatorService.$emit('searching', {});

      // Scroll to top.
      if (scrollToTop) {
        window.scrollTo(0, 0);
      }

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
          // Update filter counts.
          $scope.selectedFilterCount = countSelectedFilters();

          // Send results.
          $scope.searchBtnText = 'Search';
          $scope.searching = false;
          $scope.showSort = true;
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
        'hits': []
      };

      // Get filters.
      $scope.filters = state.filters;

      // Set template to use.
      $scope.template = CONFIG.templates.box;

      // Init the query object.
      $scope.query = {
        'text': '',
        'sort': {
          'created': $scope.sortActive
        }
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

        // Correct active classes in UI based on query for filters.
        if ($scope.query.hasOwnProperty('filters') && $scope.query.filters.hasOwnProperty('taxonomy') && $scope.query.filters.taxonomy.hasOwnProperty('type')) {
          for (var type in $scope.query.filters.taxonomy.type) {
            if ($scope.query.filters.taxonomy.type[type]) {
              switch (type) {
                case 'loop_documents_document':
                case 'loop_documents_collection':
                case 'external_sources':
                  $scope.filterActive = 'docs';
                  break;

                case 'post':
                  $scope.filterActive = 'post';
                  break;

                default:
                  $scope.filterActive = 'all';
                  break;
              }
            }

          }
        }
        else {
          $scope.filterActive = 'all';
        }

        search(true);
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
          search(false);
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
      search(true);
    }

    /**
     * Update search result after filter request from result controller.
     *
     * @param {object} data
     *   The filter and selection made as strings.
     */
    function filterUpdated(data) {
      $scope.query.text = '';

      // Ensure that data structure exists in the search query before accessing
      // it.
      if (!$scope.query.hasOwnProperty('filters')) {
        $scope.query.filters = {
          'taxonomy': {}
        }
      }
      if (!$scope.query.filters.hasOwnProperty('taxonomy')) {
        $scope.query.filter.taxonomy = { }
      }

      if ($scope.query.filters.taxonomy.hasOwnProperty(data['filter'])) {
        delete $scope.query.filters['taxonomy'][data['filter']];
      }
      $scope.query.filters['taxonomy'][data['filter']] = {};
      $scope.query.filters['taxonomy'][data['filter']][data['selection']] = true;

      search(true);
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
     * Update the search to filter on the selected filter in the results
     * controller.
     */
    communicatorService.$on('filterUpdate', function (event, data) {
      var phase = this.$root.$$phase;
      if (phase === '$apply' || phase === '$digest') {
          filterUpdated(data);
      }
      else {
        $scope.$apply(function () {
          filterUpdated(data);
        });
      }
    });

    /**
     * Search click handler.
     *
     * Simple wrapper for search that resets the pager before executing the
     * search.
     *
     * @param {boolean} scrollToTop
     *   If TRUE the page i scrolled to the top else not.
     */
    $scope.searchClicked = function searchClicked(scrollToTop) {
      $scope.searchBtnText = 'Searching...';
      $scope.searching = true;

      // Hide suggestions.
      $scope.suggestToggle(false);

      // Reset pager.
      if ($scope.query.hasOwnProperty('pager')) {
        $scope.query.pager = angular.copy(CONFIG.provider.pager);
      }

      search(scrollToTop);
    };

    /**
     * Auto-complete callback.
     */
    $scope.autocomplete = function autocomplete() {
      if (CONFIG.provider.hasOwnProperty('autocomplete')) {
        $scope.autocompleteString = '';
        if ($scope.query.text.length >= CONFIG.provider.autocomplete.minChars) {
          searchProxyService.autocomplete($scope.query.text).then(
            function (data) {
              if (data.hits) {
                // Use regex to ensure cases (letters) are matched.
                var re = new RegExp('^' + $scope.query.text, 'i');
                var res = data.results[0][CONFIG.provider.autocomplete.field];
                $scope.suggestions.hits = data.results;
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
            // ?????
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
      return $scope.suggestions['hits'].length;
    };

    /**
     * Simply count the number of selected filters.
     *
     * @return {number}
     *   The number of selected filters.
     */
    function countSelectedFilters() {
      var count = 0;

      if ($scope.query.hasOwnProperty('filters') && $scope.query.filters.hasOwnProperty('taxonomy')) {
        for (var i in $scope.query.filters.taxonomy) {
          if (i === 'type') {
            // Skip the special type filter.
            continue;
          }
          for (var j in $scope.query.filters.taxonomy[i]) {
            if ($scope.query.filters.taxonomy[i][j]) {
              count++;
            }
          }
        }
      }

      return count
    }

    /**
     * Filter based on content type.
     *
     * @param type
     *   The type to filter on.
     */
    $scope.filterType = function filterType(type) {
      if (!$scope.query.hasOwnProperty('filters')) {
        $scope.query['filters'] = { };
      }
      if (!$scope.query.filters.hasOwnProperty('taxonomy')) {
        $scope.query.filters['taxonomy'] = { };
      }

      $scope.filterActive = type;

      switch (type) {
        case 'all':
          delete $scope.query.filters['taxonomy']['type'];
          break;

        case 'docs':
          $scope.query.filters['taxonomy']['type'] = documentFilter;
          break;

        case 'post':
          $scope.query.filters['taxonomy']['type'] = {
            'post': true
          };
          break;
      }

      $scope.searchClicked(false);
    };

    /**
     * Set the sort order for current search.
     *
     * @param order
     *   The order to sort.
     */
    $scope.sortOrder = function sortOrder(order) {
      $scope.sortActive = order;

      switch (order) {
        case 'desc':
        case 'asc':
          $scope.query['sort'] = {
            'created': order
          };
          break;

        case 'alpha':
          $scope.query['sort'] = {
            'title': 'asc'
          };
          break;

        default:
          // Remove sort order and default to score order from ES.
          if ($scope.query.hasOwnProperty('sort')) {
            delete $scope.query['sort'];
          }
          break;
      }

      $scope.searchClicked(false);
    };

    // Get the show on the road.
    init();
  }
]);
