<div class="guide--nav-wrapper">
  <h2><?php print t('Index'); ?></h2>
  <div class="guide--nav-wrapper-inner">
    <ul class="guide--nav-list">
      <?php foreach ($forest['childs'] as $tree): ?>
        <?php print render($tree); ?>
      <?php endforeach; ?>
    </ul>
  </div>
</div>
