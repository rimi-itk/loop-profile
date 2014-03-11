<div class="guide--nav-wrapper">
  <div class="guide--nav-wrapper-inner">
    <?php foreach ($forest['childs'] as $tree): ?>
      <?php print render($tree); ?>
    <?php endforeach; ?>
  </div>
</div>

