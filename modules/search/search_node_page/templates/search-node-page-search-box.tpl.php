<?php
/**
 * @file
 * Default template for the search box.
 */
?>
<form id="searchBoxApp" data-ng-strict-di data-ng-controller="boxController">
  <span data-ng-include="template">
    <div class="row collapse">
      <div class="small-10 columns">
        <input type="text" placeholder="Søg, f.eks. musik, kursus">
      </div>
      <div class="small-2 columns">
        <a href="#" class="button postfix">Søg</a>
      </div>
    </div>
  </span>
</form>