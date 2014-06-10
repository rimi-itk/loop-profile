<?php
/**
 * @file
 * loop_user_related_content_competence.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function loop_user_related_content_competence_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'loop_questions_by_user_competence';
  $view->description = 'List of questions based on users professions';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Loop questions by user competence';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['hide_admin_links'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Udfør';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Gendan';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sortér efter';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Stigende';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Faldende';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'block-questions--item';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Opførsel ved ingen resultater: Global: View-område */
  $handler->display->display_options['empty']['view']['id'] = 'view';
  $handler->display->display_options['empty']['view']['table'] = 'views';
  $handler->display->display_options['empty']['view']['field'] = 'view';
  $handler->display->display_options['empty']['view']['empty'] = TRUE;
  $handler->display->display_options['empty']['view']['view_to_insert'] = 'loop_questions_by_user_competence:panel_pane_2';
  /* Forbindelse: Bruger: Area of expertise (field_area_of_expertise) */
  $handler->display->display_options['relationships']['field_area_of_expertise_tid']['id'] = 'field_area_of_expertise_tid';
  $handler->display->display_options['relationships']['field_area_of_expertise_tid']['table'] = 'field_data_field_area_of_expertise';
  $handler->display->display_options['relationships']['field_area_of_expertise_tid']['field'] = 'field_area_of_expertise_tid';
  /* Forbindelse: Ord i ordforråd: Indhold som bruger Subject */
  $handler->display->display_options['relationships']['reverse_field_subject_node']['id'] = 'reverse_field_subject_node';
  $handler->display->display_options['relationships']['reverse_field_subject_node']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['reverse_field_subject_node']['field'] = 'reverse_field_subject_node';
  $handler->display->display_options['relationships']['reverse_field_subject_node']['relationship'] = 'field_area_of_expertise_tid';
  $handler->display->display_options['relationships']['reverse_field_subject_node']['required'] = TRUE;
  /* Forbindelse: Indhold: Forfatter */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'reverse_field_subject_node';
  /* Forbindelse: Kommentar: Nodens kommentarer */
  $handler->display->display_options['relationships']['cid']['id'] = 'cid';
  $handler->display->display_options['relationships']['cid']['table'] = 'node';
  $handler->display->display_options['relationships']['cid']['field'] = 'cid';
  $handler->display->display_options['relationships']['cid']['relationship'] = 'reverse_field_subject_node';
  /* Forbindelse: Flag: ranking tæller */
  $handler->display->display_options['relationships']['flag_count_rel']['id'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['table'] = 'comment';
  $handler->display->display_options['relationships']['flag_count_rel']['field'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['relationship'] = 'cid';
  $handler->display->display_options['relationships']['flag_count_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_count_rel']['flag'] = 'ranking';
  /* Felt: Bruger: Area of expertise */
  $handler->display->display_options['fields']['field_area_of_expertise']['id'] = 'field_area_of_expertise';
  $handler->display->display_options['fields']['field_area_of_expertise']['table'] = 'field_data_field_area_of_expertise';
  $handler->display->display_options['fields']['field_area_of_expertise']['field'] = 'field_area_of_expertise';
  $handler->display->display_options['fields']['field_area_of_expertise']['label'] = 'Excluded - used for template';
  $handler->display->display_options['fields']['field_area_of_expertise']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_area_of_expertise']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_area_of_expertise']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_area_of_expertise']['delta_offset'] = '0';
  /* Felt: Bruger: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'excluded';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Felt: Bruger: First name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_first_name']['label'] = 'excluded';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  /* Felt: Bruger: Job title */
  $handler->display->display_options['fields']['field_job_title']['id'] = 'field_job_title';
  $handler->display->display_options['fields']['field_job_title']['table'] = 'field_data_field_job_title';
  $handler->display->display_options['fields']['field_job_title']['field'] = 'field_job_title';
  $handler->display->display_options['fields']['field_job_title']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_job_title']['label'] = 'excluded';
  $handler->display->display_options['fields']['field_job_title']['exclude'] = TRUE;
  /* Felt: Bruger: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_last_name']['label'] = 'excluded';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  /* Felt: Bruger: User image */
  $handler->display->display_options['fields']['field_user_image']['id'] = 'field_user_image';
  $handler->display->display_options['fields']['field_user_image']['table'] = 'field_data_field_user_image';
  $handler->display->display_options['fields']['field_user_image']['field'] = 'field_user_image';
  $handler->display->display_options['fields']['field_user_image']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_user_image']['label'] = 'excluded';
  $handler->display->display_options['fields']['field_user_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_user_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_user_image']['settings'] = array(
    'image_style' => 'preview',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_user_image']['group_column'] = 'entity_id';
  /* Felt: Indhold: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_subject_node';
  $handler->display->display_options['fields']['title']['label'] = 'excluded';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Felt: Indhold: Oprettelsesdato */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'reverse_field_subject_node';
  $handler->display->display_options['fields']['created']['label'] = 'excluded';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Felt: Global: Tilpasset tekst */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="meta-data--author">
<div class="meta-data--author-image">
<a href="/user/[uid]">[field_user_image]</a>
</div>
<div class="meta-data--author-wrapper">
<a class="meta-data--author-link" href="/user/[uid]">[field_first_name] [field_last_name]</a>
<span class="meta-data--author-title">[field_job_title]</span>
</div>
</div>
<span class="meta-data--date">[created]</span>
[title]';
  $handler->display->display_options['fields']['nothing']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Felt: Kommentar: Comment */
  $handler->display->display_options['fields']['comment_body']['id'] = 'comment_body';
  $handler->display->display_options['fields']['comment_body']['table'] = 'field_data_comment_body';
  $handler->display->display_options['fields']['comment_body']['field'] = 'comment_body';
  $handler->display->display_options['fields']['comment_body']['relationship'] = 'cid';
  $handler->display->display_options['fields']['comment_body']['label'] = 'excluded - used to group results with multiple comments';
  $handler->display->display_options['fields']['comment_body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['comment_body']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['comment_body']['group_columns'] = array(
    'format' => 'format',
  );
  /* Sorteringskriterie: Bruger: Oprettelsesdato */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Kontekstuelt filter: Bruger: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filterkriterie: Bruger: Aktiv */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'uid';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: COUNT(Flag: Flagtæller) */
  $handler->display->display_options['filters']['count']['id'] = 'count';
  $handler->display->display_options['filters']['count']['table'] = 'flag_counts';
  $handler->display->display_options['filters']['count']['field'] = 'count';
  $handler->display->display_options['filters']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['filters']['count']['group_type'] = 'count';
  $handler->display->display_options['filters']['count']['value']['value'] = '0';
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_subject_node';
  $handler->display->display_options['filters']['type']['value'] = array(
    'post' => 'post',
  );
  /* Filterkriterie: Indhold: Kommentarantal */
  $handler->display->display_options['filters']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['filters']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['filters']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['filters']['comment_count']['relationship'] = 'reverse_field_subject_node';
  $handler->display->display_options['filters']['comment_count']['value']['value'] = '0';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');

  /* Display: When empty */
  $handler = $view->new_display('panel_pane', 'When empty', 'panel_pane_2');
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* Opførsel ved ingen resultater: Global: Tekstområde */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No content related to your profession';
  $handler->display->display_options['empty']['area']['format'] = 'editor';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filterkriterie: Bruger: Aktiv */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'uid';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Indhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_subject_node';
  $handler->display->display_options['filters']['type']['value'] = array(
    'post' => 'post',
  );
  $export['loop_questions_by_user_competence'] = $view;

  return $export;
}
