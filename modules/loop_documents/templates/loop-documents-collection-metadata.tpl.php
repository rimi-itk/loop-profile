<?php

/**
 * @file
 * Document collection metadata template.
 */
?>
<?php
$metadata_values = array_map(function ($field_name) use ($collection) {
  $field = field_view_field('node', $collection, $field_name, array('label' => 'hidden'));
  return render($field);
}, array(
  'owner' => 'field_loop_documents_owner',
  'version' => 'field_loop_documents_version',
  'approver' => 'field_loop_documents_approver',
  'approval_date' => 'field_loop_documents_approv_date',
  'review_date' => 'field_loop_documents_review_date',
  'keyword' => 'field_keyword',
  'subject' => 'field_subject',
));
?>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Owner') ?>
      </p>
      <?php echo $metadata_values['owner']; ?>
    </div>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Version') ?>
      </p>
      <?php echo $metadata_values['version']; ?>
    </div>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Approver') ?>
      </p>
      <?php echo $metadata_values['approver']; ?>
    </div>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Approval date') ?>
      </p>
      <?php echo $metadata_values['approval_date']; ?>
    </div>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Review date') ?>
      </p>
      <?php echo $metadata_values['review_date']; ?>
    </div>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Tags') ?>
      </p>
      <?php echo $metadata_values['keyword']; ?>
    </div>

    <div class="loop-documents--collection-metadata">
      <p class="loop-documents--meta-title">
        <?php echo t('Subject') ?>
      </p>
      <?php echo $metadata_values['subject']; ?>
    </div>
</dl>
</fieldset>
