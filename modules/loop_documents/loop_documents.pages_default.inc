<?php
/**
 * @file
 * loop_documents.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function loop_documents_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_b8e02f43-2538-42f7-9345-cc762064c143';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Loop documents',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'loop_documents_collection' => 'loop_documents_collection',
              'loop_documents_document' => 'loop_documents_document',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'default';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'alpha' => NULL,
      'beta' => NULL,
      'gamma' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '65b2a347-235d-44cb-9d7b-dc9167fe168b';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'node_view__panel_context_b8e02f43-2538-42f7-9345-cc762064c143';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-d47bc92f-ff0f-4f87-b81c-18f2e7941de4';
  $pane->panel = 'alpha';
  $pane->type = 'node_content';
  $pane->subtype = 'node_content';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'links' => 0,
    'no_extras' => 1,
    'override_title' => 1,
    'override_title_text' => '',
    'identifier' => '',
    'link' => 0,
    'leave_node_title' => 1,
    'build_mode' => 'full',
    'context' => 'argument_entity_id:node_1',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'd47bc92f-ff0f-4f87-b81c-18f2e7941de4';
  $display->content['new-d47bc92f-ff0f-4f87-b81c-18f2e7941de4'] = $pane;
  $display->panels['alpha'][0] = 'new-d47bc92f-ff0f-4f87-b81c-18f2e7941de4';
  $pane = new stdClass();
  $pane->pid = 'new-cf7f5491-5b00-4348-9070-bdef0eeb1ee1';
  $pane->panel = 'beta';
  $pane->type = 'block';
  $pane->subtype = 'loop_documents-loop_documents_navigation';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'cf7f5491-5b00-4348-9070-bdef0eeb1ee1';
  $display->content['new-cf7f5491-5b00-4348-9070-bdef0eeb1ee1'] = $pane;
  $display->panels['beta'][0] = 'new-cf7f5491-5b00-4348-9070-bdef0eeb1ee1';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_b8e02f43-2538-42f7-9345-cc762064c143'] = $handler;

  return $export;
}
