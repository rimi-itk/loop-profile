<ul>
  <?php foreach ($forest['#trees'] as $tree): ?>
    <li>
      <?php if (is_array($tree)): ?>
        <ul>
          <?php foreach ($tree as $child): ?>
            <li>
              <?php if (is_array($child)): ?>
                <ul>
                  <?php foreach ($child as $leaf): ?>
                    <li>
                      <?php if (is_string($leaf)): ?>
                        <?php print $leaf; ?>
                      <?php else: ?>
                        <?php print $leaf->title; ?>
                        <?php print $leaf->body[LANGUAGE_NONE][0]['safe_value']; ?>
                      <?php endif; ?>
                    </li>
                  <?php endforeach; ?>
                </ul>
              <?php elseif (is_string($child)): ?>
                <?php print $child; ?>
              <?php else: ?>
                <?php print $child->title; ?>
                <?php print $child->body[LANGUAGE_NONE][0]['safe_value']; ?>
              <?php endif; ?>
            </li>
          <?php endforeach; ?>
        </ul>
      <?php endif; ?>
    </li>
  <?php endforeach; ?>
</ul>
