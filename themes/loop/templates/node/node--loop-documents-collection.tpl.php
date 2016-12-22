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
          echo '<h2>', t('Contents'), '</h2>';

          echo render($loop_documents_menu);
        }
        ?>
      </div>
    <?php endif ?>
  </div>

  <div class="loop-documents--content">
    <div class="loop-documents--collection-content">
      <?php include drupal_get_path('theme', 'loop') . '/templates/node/node--page.tpl.php'; ?>
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
