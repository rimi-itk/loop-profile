<?php

/**
 * @file
 * Document collection print header template.
 */
?>
<!DOCTYPE html>

<html>
  <head>
    <meta charset="utf-8"/>
    <title>print – header – <?php echo $collection->title; ?></title>
    <style>
     .metadata {
       display: flex;
       flex-flow: row wrap;

       align-items: center;
       justify-content: space-between;
     }

     .metadata .item {
       width: 50%;
     }

     .metadata .label, .metadata .value {
       display: inline-block;
     }

     .metadata .label::after {
       content: ':';
     }

    </style>
  </head>
  <body>
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

    <div class="metadata">
      <div class="item">
        <div class="label"><?php echo t('Owner') ?></div>
        <div class="value"><?php echo $metadata_values['owner']; ?></div>
      </div>

      <div class="item">
        <div class="label"><?php echo t('Version') ?></div>
        <div class="value"><?php echo $metadata_values['version']; ?></div>
      </div>

      <div class="item">
        <div class="label"><?php echo t('Approver') ?></div>
        <div class="value"><?php echo $metadata_values['approver']; ?></div>
      </div>

      <div class="item">
        <div class="label"><?php echo t('Approval date') ?></div>
        <div class="value"><?php echo $metadata_values['approval_date']; ?></div>
      </div>

      <div class="item">
        <div class="label"><?php echo t('Author') ?></div>
        <div class="value"><div id="document-author"></div></div>
      </div>

      <div class="item">
        <div class="label"><?php echo t('Review date') ?></div>
        <div class="value"><?php echo $metadata_values['review_date']; ?></div>
      </div>
    </div>
  </body>
</html>
