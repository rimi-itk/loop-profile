<?php

/**
 * @file
 * Document collection template.
 */
?>
<div class="loop-documents loop-documents--collection">
	<div class="loop-documents--sidebar">
		<div class="loop-documents--navigation">
			<?php if (!empty($loop_documents_menu)): ?>
				<div class="loop-documents--collection-navigation">
					<h1 class="loop-documents--collection-title">
						<?php echo $node->title; ?>
					</h1>

					<?php echo render($loop_documents_menu); ?>

					<?php
					$metadata_view = node_view($loop_documents_collection, 'metadata');
					echo render($metadata_view);
					?>

					<?php if (!empty($loop_documents_collection_print_url)): ?>
						<div class="loop-documents--collection-print">
							<?php echo l(t('Print collection'), $loop_documents_collection_print_url); ?>
						</div>
					<?php endif ?>
				</div>
			<?php endif ?>
		</div>
	</div>

	<div class="loop-documents--main">
		<div class="loop-documents--content loop-documents--collection-content">
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
  </div>
</div>
