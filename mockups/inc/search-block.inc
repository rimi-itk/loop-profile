<?php
$path_to_theme = "/profiles/loopdk/themes/loop/";
?>
<div class="panel-pane pane-block pane-search-form loop-frontpage--search-block search-block">
  <div class="panel-pane--inner">
    <div class="pane-content">
      <form action="<?php echo $path_to_theme; ?>mockups/search-result.php" method="post" id="search-block-form" accept-charset="UTF-8">
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
    </div>
    <?php if (isset($is_front)): ?>
    <div class="search--autocomplete">
      <h4 class="search--autocomplete-header">Spørgsmål andre har stillet</h4>
      <a href="#" class="search--autocomplete-link">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?</a>
      <a href="#" class="search--autocomplete-link">I hvilket special ark skal terapeuter i plejeboliger visitere i?</a>
      <a href="#" class="search--autocomplete-link">Skal der oprettes et Fokusområder der hedder ernæring, hvis en borger scorer 0 i en ernæringsvurdering?</a>
      <a href="#" class="search--autocomplete-link">Skal køkkenpersonale, som samarbejder tæt med beboere, plejepersonale og terapeuter omkring ernæring dokumentere om ernærings indsatser?</a>
    </div>
    <?php endif ?>
  </div>
</div>
