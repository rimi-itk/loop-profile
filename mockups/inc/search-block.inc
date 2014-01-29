<?php
$path_to_theme = "/profiles/loopdk/themes/loop/";
?>
<div class="typeahead-block">
  <form>
    <div class="typeahead-block--wrapper">
      <label for="typeahead">Search for an answer</label>
      <i class="typeahead-block--icon icon-search"></i>
      <input type="text" id="typeahead" title="E.g. &quot;How do you document a subject&quot;" placeholder="E.g. &quot;How do you document a subject&quot;" class="typeahead tt-query" style="position: relative; vertical-align: top; background-color: transparent;">
      <input type="submit" value="Search" class="typeahead-block--button">
      <?php if (isset($is_front)): ?>
        <span class="tt-dropdown-menu" style="position: absolute; top: 100%; left: 0px; z-index: 100; display: block; right: auto;">
          <div class="tt-dataset-search" style="display: block;">
            <span class="tt-suggestions" style="display: block;">
              <h4 class="tt-suggestion-header">Spørgsmål andre har stillet</h4>
              <div class="tt-suggestion tt-is-under-cursor" style="white-space: nowrap; cursor: pointer;">
                <span style="white-space: normal;">node/5</span><span style="white-space: normal;">&lt;strong&gt;Meget&lt;/strong&gt; lang test titel med special ord</span>
                <span style="white-space: normal;"></span>
              </div>
              <div class="tt-suggestion tt-is-under-cursor" style="white-space: nowrap; cursor: pointer;">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?...</div>
              <div class="tt-suggestion tt-is-under-cursor" style="white-space: nowrap; cursor: pointer;">I hvilket special ark skal terapeuter i plejeboliger visitere i?...</div>
              <div class="tt-suggestion tt-is-under-cursor" style="white-space: nowrap; cursor: pointer;">Skal der oprettes et Fokusområder der hedder ernæring, hvis en borger scorer 0 i en ernæringsvurdering?...</div>
              <div class="tt-suggestion tt-is-under-cursor" style="white-space: nowrap; cursor: pointer;">Skal køkkenpersonale, som samarbejder tæt med beboere, plejepersonale og terapeuter omkring ernæring dokumentere om ernærings indsatser?...</div>
            </span>
          </div>
        </span>
      <?php endif ?>
    </div>
  </form>
</div>
