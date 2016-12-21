<?php

/**
 * @file
 * Document collection template.
 */
?>
<div class="loop-documents loop-documents--collection">
  <div class="loop-documents--navigation loop-documents--collection-navigation guide--nav-wrapper">
    <?php
		if (isset($loop_documents_menu)) {
			echo render($loop_documents_menu);
		}
		?>
  </div>

  <div class="loop-documents--content loop-documents--collection-content">
    <?php include drupal_get_path('theme', 'loop') . '/templates/node/node--page.tpl.php'; ?>
  </div>
</div>
