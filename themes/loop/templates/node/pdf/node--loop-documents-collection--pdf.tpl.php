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
      hide($content['field_keyword']);
      hide($content['field_subject']);
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

    <?php echo theme('loop_documents_collection_metadata', array('collection' => $node)); ?>
  </div>
</div>
