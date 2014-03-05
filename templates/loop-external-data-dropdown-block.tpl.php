<select>
  <?php foreach ($forest['childs'] as $tree): ?>
    <?php print render($tree); ?>
  <?php endforeach; ?>
</select>
