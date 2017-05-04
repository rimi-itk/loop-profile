<?php

/**
 * @file
 * Document template.
 */
?>
<div class="loop-documents loop-documents--document">
  <div class="loop-documents--content">
    <div class="loop-documents--document-content">
      <h1 class="page-title loop-documents--document-title">
        <?php print $title; ?>
      </h1>

      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['children']);
      hide($content['field_keyword']);
      hide($content['field_subject']);
      print render($content);
      print render($content['children']);
      ?>
    </div>
  </div>
</div>
