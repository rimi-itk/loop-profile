<?php
/**
 * @file
 * loop_editor_pages.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function loop_editor_pages_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'editor_dashboard';
  $page->task = 'page';
  $page->admin_title = 'Editor dashboard';
  $page->admin_description = '';
  $page->path = 'editor/dashboard';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 3,
            1 => 4,
            2 => 5,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Dashboard',
    'name' => 'menu-loop-primary-menu',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_editor_dashboard_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'editor_dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Editor dashboard',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'dashboard';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'alpha' => NULL,
      'beta' => NULL,
      'gamma' => NULL,
      'delta' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Dashboard';
  $display->uuid = '5c4610bd-d98d-4392-833f-1c60080f8cba';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ea557ba6-d98e-4c10-ad61-0bdfe3812279';
    $pane->panel = 'alpha';
    $pane->type = 'views_panes';
    $pane->subtype = 'loop_editor_content-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ea557ba6-d98e-4c10-ad61-0bdfe3812279';
    $display->content['new-ea557ba6-d98e-4c10-ad61-0bdfe3812279'] = $pane;
    $display->panels['alpha'][0] = 'new-ea557ba6-d98e-4c10-ad61-0bdfe3812279';
    $pane = new stdClass();
    $pane->pid = 'new-08dc774a-0d9f-4464-9b0c-fafef23c5657';
    $pane->panel = 'beta';
    $pane->type = 'views_panes';
    $pane->subtype = 'loop_editor_content-panel_pane_3';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '08dc774a-0d9f-4464-9b0c-fafef23c5657';
    $display->content['new-08dc774a-0d9f-4464-9b0c-fafef23c5657'] = $pane;
    $display->panels['beta'][0] = 'new-08dc774a-0d9f-4464-9b0c-fafef23c5657';
    $pane = new stdClass();
    $pane->pid = 'new-e97ff7b7-bed1-48d8-80b5-559396980454';
    $pane->panel = 'delta';
    $pane->type = 'views_panes';
    $pane->subtype = 'loop_editor_users-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 0,
      'override_title_text' => 'Latest users',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e97ff7b7-bed1-48d8-80b5-559396980454';
    $display->content['new-e97ff7b7-bed1-48d8-80b5-559396980454'] = $pane;
    $display->panels['delta'][0] = 'new-e97ff7b7-bed1-48d8-80b5-559396980454';
    $pane = new stdClass();
    $pane->pid = 'new-4df95cc5-2bc8-4625-97af-ce17c0699b15';
    $pane->panel = 'gamma';
    $pane->type = 'views_panes';
    $pane->subtype = 'loop_editor_comments-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'use_pager' => 0,
      'pager_id' => '0',
      'items_per_page' => '10',
      'offset' => '0',
      'override_title' => 0,
      'override_title_text' => 'Latest comments',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4df95cc5-2bc8-4625-97af-ce17c0699b15';
    $display->content['new-4df95cc5-2bc8-4625-97af-ce17c0699b15'] = $pane;
    $display->panels['gamma'][0] = 'new-4df95cc5-2bc8-4625-97af-ce17c0699b15';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['editor_dashboard'] = $page;

  return $pages;

}
