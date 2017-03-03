<?php
/**
 * @file
 * Default template for the search box.
 */
?>
<div id="searchBoxApp" data-ng-strict-di data-ng-controller="loopSearchBoxController" data-ng-include="template">
  <div class="search-box-block">
    <div class="search-box-block--wrapper">
      <p class="no-js"><?php echo t('Search requires javascript enabled'); ?></p>
    </div>
  </div>
</div>