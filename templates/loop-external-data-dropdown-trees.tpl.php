<li class="guide--nav-list-item"><?php print $title; ?>
<ul class="guide--nav-list">
    <?php foreach ($childs as $child): ?>
      <?php print render($child); ?>
    <?php endforeach; ?>
  </ul>
</li>
