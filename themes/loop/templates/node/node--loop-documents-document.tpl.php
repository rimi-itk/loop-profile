<?php

/**
 * @file
 * Document template.
 */
?>
<div class="loop-documents loop-documents--document">
  <div class="loop-documents--navigation">
    <?php if (!empty($loop_documents_menu) || !empty($loop_documents_roots)): ?>
      <div class="loop-documents--document-navigation guide--nav-wrapper">
        <?php
        if (!empty($loop_documents_menu)) {
          if (isset($loop_documents_menu['#root'])) {
            $root = $loop_documents_menu['#root'];
            echo '<div class="loop-documents--collection-print">', l(t('Print PDF'), 'entityprint/node/' . $root->nid), '</div>';

            echo '<h2>', l($root->title, 'node/' . $root->nid), '</h2>';
          }

          echo render($loop_documents_menu);

          if (isset($loop_documents_menu['#root'])) {
            $root = $loop_documents_menu['#root'];

            echo '<fieldset><legend>' . t('Metadata') . '</legend>';
            foreach (array(
              'field_loop_documents_owner',
              'field_loop_documents_version',
              'field_loop_documents_approver',
              'field_loop_documents_approv_date',
              'field_loop_documents_review_date',
            ) as $field_name) {
              $field = field_view_field('node', $root, $field_name);
              echo render($field);
            }
            echo '</fieldset>';
          }
        }
        ?>

        <?php
        if (!empty($loop_documents_roots)) {
          echo '<h2>' . t('Document collections') . '</h2>';
          echo render($loop_documents_roots);
        }
        ?>
      </div>
    <?php endif ?>
  </div>

  <div class="loop-documents--content">
    <div class="loop-documents--document-content">
      <h1 class="page-title">
        <?php print $title; ?>
        <?php
        // Check if the user is allowed to edit the page.
        if ($router_item = menu_get_item('node/' . $node->nid . '/edit')) {
          if ($router_item['access']) {
            print '<span class="page-title--edit-link">(<a href="/node/' . $node->nid . '/edit">' . t('edit page') . '</a>)</span>';
          }
        }
        ?>
      </h1>
      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
      ?>
    </div>

    <div class="loop-documents--metadata">
      <?php
      $field = field_view_field('node', $node, 'field_loop_documents_author', array('_label' => 'hidden'));
      echo render($field);
      ?>
    </div>
  </div>
</div>
