<?php

/**
 * @file
 * Default template for the search results.
 */
?>
<div id="searchResultApp" data-ng-controller="loopResultController" data-ng-hide="no_hits_yet" class="block block-system search-result--block">
    <div class="content" >
        <div class="contextual-links-region">  <div class="layout-full-width">
                <div class="layout--inner">
                    <div class="layout-element-alpha">
                        <div data-ng-strict-di data-ng-include="template">
                            <p class="no-js"><?php echo t('Search requires javascript enabled'); ?></p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
