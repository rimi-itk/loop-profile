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
    </div>
  </form>
  <?php if (isset($is_front)): ?>
    <div class="search--autocomplete-wrapper js-autocomplete-search" style="display: block;">
      <h4 class="autocomplete-header js-autocomplete-header">Spørgsmål andre har stillet</h4>
      <div class="autocomplete-suggestions">
        <div class="autocomplete-suggestion" data-index="0">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?...</div>
        <div class="autocomplete-suggestion" data-index="1">I hvilket special ark skal terapeuter i plejeboliger visitere i?...</div>
        <div class="autocomplete-suggestion" data-index="2">Skal der oprettes et Fokusområder der hedder ernæring, hvis en borger scorer 0 i en ernæringsvurdering?...</div>
        <div class="autocomplete-suggestion" data-index="3">Skal køkkenpersonale, som samarbejder tæt med beboere, plejepersonale og terapeuter omkring ernæring dokumentere om ernærings indsatser?...</div>
        <div class="autocomplete-suggestion" data-index="4">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?...</div>
      </div>
    </div>
  <?php endif ?>
</div>
