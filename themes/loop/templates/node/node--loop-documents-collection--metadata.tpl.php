<?php
$metadata_values = array_map(function ($field_name) use ($node) {
	$field = field_view_field('node', $node, $field_name, array('label' => 'hidden'));
	return render($field);
}, array(
	'owner' => 'field_loop_documents_owner',
  'version' => 'field_loop_documents_version',
  'approver' => 'field_loop_documents_approver',
	'approval_date' => 'field_loop_documents_approv_date',
	'review_date' => 'field_loop_documents_review_date',
));
?>

<fieldset class="loop-documents--metadata loop-documents--collection-metadata">
	<legend><?php echo t('Collection metadata'); ?></legend>

	<dl>
		<dt><?php echo t('Owner') ?></dt>
		<dd><?php echo $metadata_values['owner']; ?></dd>

		<dt><?php echo t('Version') ?></dt>
		<dd><?php echo $metadata_values['version']; ?></dd>

		<dt><?php echo t('Approver') ?></dt>
		<dd><?php echo $metadata_values['approver']; ?></dd>

		<dt><?php echo t('Approval date') ?></dt>
		<dd><?php echo $metadata_values['approval_date']; ?></dd>

		<dt><?php echo t('Review date') ?></dt>
		<dd><?php echo $metadata_values['review_date']; ?></dd>
	</dl>
</fieldset>
