<div class="guide--nav-wrapper">
  <select class="guide--nav" onchange="alert(this.value); if (this.value) window.location.href='/node/' + this.value">
    <?php foreach ($forest['childs'] as $tree): ?>
      <?php print render($tree); ?>
    <?php endforeach; ?>
  </select>
</div>
