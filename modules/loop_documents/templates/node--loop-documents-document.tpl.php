<?php

/**
 * @file
 * Document template.
 */
?>
<div class="loop-documents loop-documents--document">
  <div class="loop-documents--content loop-documents--document-content">
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
    <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print render($content);
    ?>
  </div>
</div>
