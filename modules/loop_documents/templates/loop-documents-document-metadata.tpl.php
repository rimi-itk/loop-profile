<?php

/**
 * @file
 * Document metadata template.
 */
?>
<?php
$metadata_values = array_map(function ($field_name) use ($document) {
  $field = field_view_field('node', $document, $field_name, array('label' => 'hidden'));
  return render($field);
}, array(
  'author' => 'field_loop_documents_author',
));
?>

<div class="loop-documents--document-metadata">
  <p class="loop-documents--meta-title">
    <?php echo t('Author') ?>
  </p>
  <?php echo $metadata_values['author'] ? $metadata_values['author'] : t('No author specified'); ?>
</div>
