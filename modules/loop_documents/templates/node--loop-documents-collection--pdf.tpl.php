<?php

/**
 * @file
 * Document collection template.
 */
?>
<div class="loop-documents loop-documents--collection">
  <div class="loop-documents--content">
    <div class="loop-documents--collection-content">
      <h1 class="page-title loop-documents--collection-title">
        <?php print $title; ?>
      </h1>

      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['documents']);
      print render($content);
      ?>
    </div>

    <?php
    if (isset($loop_documents_menu)) {
      echo render($loop_documents_menu);
    }
    ?>

    <div class="loop-documents--collection-documents">
      <?php print render($content['documents']); ?>
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
