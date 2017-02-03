<?php

/**
 * @file
 * Document (collection) navigation template.
 */
?>

<?php if (!empty($loop_documents_menu) || !empty($loop_documents_collection)): ?>

  <div class="loop-documents--navigation">
    <div class="loop-documents--collection-navigation">
      <h2 class="loop-documents--collection-title">
        <?php if ($node->type === 'loop_documents_collection'): ?>
          <?php echo $node->title; ?>
        <?php elseif (!empty($loop_documents_collection)): ?>
          <?php echo l($loop_documents_collection->title, 'node/' . $loop_documents_collection->nid); ?>
        <?php endif ?>
      </h2>

      <?php if (!empty($loop_documents_menu)): ?>
        <?php echo render($loop_documents_menu); ?>
      <?php endif ?>

      <?php if (!empty($loop_documents_collection_print_url)): ?>
        <div class="loop-documents--collection-print">
          <?php echo l(t('Print collection'), $loop_documents_collection_print_url); ?>
        </div>
      <?php endif ?>
    </div>
  </div>
  
  <div class="loop-documents--box">
    <h2 class="loop-documents--document-meta-title no-margin">
      <?php echo t('Document metadata'); ?>
    </h2>
    <?php echo theme('loop_documents_document_metadata', array('document' => $node)); ?>
  </div>


  <div class="loop-documents--box">
    <h2 class="loop-documents--collection-meta-title no-margin js-toggle">
      <?php echo t('Collection metadata'); ?>
    </h2>

    <div class="loop-documents--metadata js-toggle-data">
      <?php if (!empty($loop_documents_collection)): ?>
        <?php echo theme('loop_documents_collection_metadata', array('collection' => $loop_documents_collection)); ?>
      <?php endif ?>
    </div>
  </div>

<?php elseif (!empty($loop_documents_collections)): ?>

  <div class="loop-documents--navigation">
    <div class="loop-documents--collection-navigation">
      <h2 class="loop-documents--document-meta-title no-margin">
        <?php echo t('Document collections'); ?>
      </h2>
      <ul><?php echo render($loop_documents_collections); ?></ul>
    </div>
  </div>

<?php endif ?>
