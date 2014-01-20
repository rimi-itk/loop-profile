<?php
$path_to_theme = "/profiles/loopdk/themes/loop/";
?>
<div class="search-block">
  <div class="search--inner">
    <form action="<?php echo $path_to_theme; ?>mockups/search-result.php" method="post" id="search-block-form" accept-charset="UTF-8" autocomplete="off">
      <div>
        <div class="search--field-wrapper">
          <div class="form-item form-type-searchfield form-item-search-block-form">
            <label for="edit-search-block-form--2">Search for an answer</label>
            <span class="field-prefix"><i class="search--icon icon-search"></i></span>
            <input title="Skriv f.eks. &quot;Hvordan dokumenteres delvis aktindsigt&quot;" placeholder="Skriv f.eks. &quot;Hvordan dokumenteres delvis aktindsigt&quot;"" class="search--field form-text form-search" type="search" id="edit-search-block-form--2" name="search_block_form" value="" size="15" maxlength="128">
          </div>
          <div class="form-actions form-wrapper" id="edit-actions">
            <input class="search--button form-submit" type="submit" id="edit-submit" name="op" value="Søg">
          </div>
        </div>
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
</div>
