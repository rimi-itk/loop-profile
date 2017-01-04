<?php

/**
 * @file
 * Document collection template.
 */
?>
<div class="loop-documents loop-documents--collection">
  <div class="loop-documents--navigation">
    <?php if (!empty($loop_documents_menu)): ?>
      <div class="loop-documents--collection-navigation guide--nav-wrapper">
        <?php
        if (isset($loop_documents_menu)) {
          echo '<div class="loop-documents--collection-print">';
          echo l('Print PDF', 'entityprint/node/' . $node->nid);
          echo '</div>';

          echo '<h2>', $node->title, '</h2>';

          echo render($loop_documents_menu);
        }
        ?>
      </div>
    <?php endif ?>
  </div>

  <div class="loop-documents--content">
    <div class="loop-documents--collection-content">
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

    <div class="loop-documents--metadata">
      <fieldset>
        <legend><?php echo t('Metadata'); ?></legend>
        <?php foreach (array(
          'field_loop_documents_owner',
          'field_loop_documents_version',
          'field_loop_documents_approver',
          'field_loop_documents_approv_date',
          'field_loop_documents_review_date',
        ) as $field_name) {
          $field = field_view_field('node', $node, $field_name);
          echo render($field);
        }
        ?>
      </fieldset>
    </div>
  </div>
</div>
