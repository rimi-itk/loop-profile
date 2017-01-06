<?php
$metadata_values = array_map(function ($field_name) use ($node) {
	$field = field_view_field('node', $node, $field_name, array('label' => 'hidden'));
	return render($field);
}, array(
	'author' => 'field_loop_documents_author',
));
?>

<fieldset class="loop-documents--metadata loop-documents--document-metadata">
	<legend><?php echo t('Document metadata'); ?></legend>

	<dl>
		<dt><?php echo t('Author') ?></dt>
		<dd><?php echo $metadata_values['author']; ?></dd>
	</dl>
</fieldset>
