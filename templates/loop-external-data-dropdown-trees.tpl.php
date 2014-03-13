<ul class="guide--nav-list">
  <li>
    <?php print $title; ?>
    <ul>
      <?php foreach ($childs as $child): ?>
        <?php print render($child); ?>
      <?php endforeach; ?>
    </ul>
  </li>
</ul>
