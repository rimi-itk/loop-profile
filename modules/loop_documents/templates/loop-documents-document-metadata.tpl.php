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
  'keyword' => 'field_keyword',
  'subject' => 'field_subject',
));
?>

<div class="loop-documents--document-metadata">
	<p class="loop-documents--meta-title">
		<?php echo t('Author') ?>
	</p>
	<?php echo $metadata_values['author'] ? $metadata_values['author'] : t('No author specified'); ?>
</div>

<?php if (!empty($metadata_values['keyword'])): ?>
	<div class="loop-documents--document-metadata">
		<p class="loop-documents--meta-title">
			<?php echo t('Tags') ?>
		</p>
		<?php echo $metadata_values['keyword']; ?>
	</div>
<?php endif ?>

<?php if (!empty($metadata_values['subject'])): ?>
	<div class="loop-documents--document-metadata">
		<p class="loop-documents--meta-title">
			<?php echo t('Subject') ?>
		</p>
		<?php echo $metadata_values['subject']; ?>
	</div>
<?php endif ?>
