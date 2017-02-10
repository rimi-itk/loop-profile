<?php

/**
 * @file
 * Document collection template.
 */
?>
<div class="loop-documents loop-documents--collection">
  <div class="loop-documents--content loop-documents--collection-content">
    <h1 class="page-title">
      <?php print $title; ?>
      <?php
      // Check if the user is allowed to edit the page.
      if ($router_item = menu_get_item('node/' . $node->nid . '/edit')) {
        if ($router_item['access']) {
          print '<span class="page-title--edit-link">(<a href="/node/' . $node->nid . '/edit">' . t('edit page') . '</a>)</span>';
        }
      }
      ?>
    </h1>

    <?php print render($content['body']); ?>
  </div>
</div>
