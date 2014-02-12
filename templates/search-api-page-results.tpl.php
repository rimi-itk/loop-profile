<?php
/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and the
 * child template are dependent on one another, sharing the markup for
 * definition lists.
 *
 * Note that modules and themes may implement their own search type and theme
 * function completely bypassing this template.
 *
 * Available variables:
 * - $index: The search index this search is based on.
 * - $result_count: Number of results.
 * - $spellcheck: Possible spelling suggestions from Search spellcheck module.
 * - $search_results: All results rendered as list items in a single HTML
 *   string.
 * - $items: All results as it is rendered through search-result.tpl.php.
 * - $search_performance: The number of results and how long the query took.
 * - $sec: The number of seconds it took to run the query.
 * - $pager: Row of control buttons for navigating between pages of results.
 * - $keys: The keywords of the executed search.
 * - $classes: String of CSS classes for search results.
 * - $page: The current Search API Page object.
 * - $no_results_help: Help text to display under the header if no results were
 *   found.
 *
 * View mode is set in the Search page settings. If you select
 * "Themed as search results", then the child template will be used for
 * theming the individual result. Any other view mode will bypass the
 * child template.
 *
 * @see template_preprocess_search_api_page_results()
 */

?>

<?php if ($result_count) : ?>
  <div class="layout--inner">
    <div class="layout-element-alpha">
      <h1 class="page-title"><?php print t('Search results');?></h1>
      <?php //print render($search_performance); ?>
      <?php print render($spellcheck); ?>
      <div class="search-result">
        <?php print render($search_results); ?>
      </div>
      <?php print render($pager); ?>
    </div>
    <div class="layout-element-beta">
    </div>
  </div>
<?php else : ?>
  <div class="layout--inner">
    <div class="layout-element-alpha">
      <h1 class="page-title"><?php print t('Search results');?></h1>
      <?php //print render($search_performance); ?>
      <div class="search-result">
        <div class="search-result--lead">
          <p><?php print t('You searched for:');?> <strong><?php print $keys;?></strong></p>
          <div class="messages warning"><?php print t('No results found');?></div>
          <?php print render($spellcheck); ?>
        </div>
        Hvis du ikke mener dit spørgsmål er besvaret før, kan du <a href="#ask-question">oprette spørgsmålet</a> i formularen. Du kan også prøve at <a href="#search-block-form">søge igen</a>.
      </div>
    </div>
    <div class="layout-element-beta">
    </div>
  </div>
  <div class="layout--inner" id="ask-question">
    <div class="layout-element-epsilon">
      <h3 class="page-title"><?php print t('Create question');?></h3>
      <?php print render($node_form); ?>
    </div>
  </div>
<?php endif; ?>