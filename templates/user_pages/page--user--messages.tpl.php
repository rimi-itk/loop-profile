<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

<?php
/*
 * Insert Loop primary menu if module is enabled.
 * Must be placed here to work on small screen devices.
 */
if (isset($loop_primary_menu)): ?>
  <nav class="nav-mobile js-mobile-nav">
    <?php print theme('links__system_primary_menu_mobile', array('links' => $main_menu)); ?>
  </nav>
<?php endif ?>

<header class="header">
  <div class="header--inner">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo" class="logo--link">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="logo--image">
      </a>
    <?php endif; ?>
    <?php print render($page['header']); ?>
    <div class="nav--wrapper">
      <?php print theme('links__system_primary_menu', array('links' => $main_menu, 'attributes' => array('class' => array('nav')))); ?>
    </div>
  </div>
</header>

<?php if (isset($search)): ?>
<div class="typeahead-block">
  <form>
    <div class="typeahead-block--wrapper">
      <label for="typeahead">Search for an answer</label>
      <i class="typeahead-block--icon icon-search"></i>
      <input type="text" id="typeahead" title="<?php print t('E.g. &quot;How do you document a subject&quot;'); ?>" placeholder="<?php print t('E.g. &quot;How do you document a subject&quot;'); ?>" class="typeahead tt-query" style="position: relative; vertical-align: top; background-color: transparent;">
      <input type="submit" value="<?php print t('Search'); ?>" class="typeahead-block--button">
    </div>
  </form>
</div>
<?php endif ?>

<div class="layout-default-inverted">
  <div class="layout--inner">
    <?php if ($messages): ?>
      <?php print $messages; ?>
    <?php endif; ?>
    <div class="layout-element-alpha">
      <?php if ($tabs): ?>
        <aside class="block-user-links">
          <div class="block-module--inner">
            <h2 class="block-module--user-links-header"><?php print t('My account'); ?></h2>
            <?php print render($tabs); ?>
          </div>
        </aside>
        <?php print render($loop_user_my_content['content']); ?>
      <?php endif; ?>
    </div>
    <div class="layout-element-beta">
      <h1><?php print t('Notifications'); ?></h1>
      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
      <?php print render($page['content']); ?>
    </div>
  </div>
</div>

<footer class="footer">
  <div class="section">
    <?php print render($page['footer']); ?>
  </div>
</footer>
