<?php

/**
 * @file
 * Document template.
 */
?>
<div class="loop-documents loop-documents--document">
	<div class="loop-documents--sidebar">
		<div class="loop-documents--navigation">
			<?php if (!empty($loop_documents_collection)): ?>
				<div class="loop-documents--collection-print">
					<h1 class="loop-documents--collection-title">
						<?php echo l($loop_documents_collection->title, 'node/' . $loop_documents_collection->nid); ?>
					</h1>
				</div>

				<?php if (!empty($loop_documents_menu)) { echo render($loop_documents_menu); } ?>

				<?php
				$metadata_view = node_view($loop_documents_collection, 'metadata');
				echo render($metadata_view);
				?>

				<?php if (!empty($loop_documents_collection_print_url)): ?>
					<div class="loop-documents--collection-print">
						<?php echo l(t('Print collection'), $loop_documents_collection_print_url); ?>
					</div>
				<?php endif ?>

			<?php elseif (!empty($loop_documents_collections)): ?>
				<h1><?php echo t('Document collections'); ?></h1>
				<?php echo render($loop_documents_roots); ?>
			<?php endif ?>
		</div>
	</div>

	<div class="loop-documents--main">
		<div class="loop-documents--content loop-documents--document-content">
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

		<?php
		$metadata_view = node_view($node, 'metadata');
		echo render($metadata_view);
		?>
  </div>
</div>
