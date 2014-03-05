<optgroup label="<?php print $title; ?>">
  <?php foreach ($childs as $child): ?>
    <?php print render($child); ?>
  <?php endforeach; ?>
</optgroup>
