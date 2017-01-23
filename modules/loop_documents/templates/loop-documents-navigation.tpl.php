<?php

/**
 * @file
 * Document (collection) navigation template.
 */
?>

<?php if (!empty($loop_documents_menu)): ?>

  <div class="guide--nav-wrapper loop-documents--navigation">
    <div class="loop-documents--collection-navigation">
      <h1 class="loop-documents--collection-title">
        <?php if ($node->type === 'loop_documents_collection'): ?>
          <?php echo $node->title; ?>
        <?php elseif (!empty($loop_documents_collection)): ?>
          <?php echo l($loop_documents_collection->title, 'node/' . $loop_documents_collection->nid); ?>
        <?php endif ?>
      </h1>

      <?php echo render($loop_documents_menu); ?>

      <?php echo theme('loop_documents_collection_metadata', array('collection' => $loop_documents_collection)); ?>

      <?php if (!empty($loop_documents_collection_print_url)): ?>
        <div class="loop-documents--collection-print">
          <?php echo l(t('Print collection'), $loop_documents_collection_print_url); ?>
        </div>
      <?php endif ?>
    </div>
  </div>

<?php elseif (!empty($loop_documents_collections)): ?>

  <div class="guide--nav-wrapper loop-documents--collections">
    <div class="loop-documents--collections">
      <h1 class="loop-documents--collections-title">
        <?php echo t('Document collections'); ?>
      </h1>

      <?php echo render($loop_documents_collections); ?>
    </div>
  </div>

<?php endif ?>
