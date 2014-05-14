<div class="">
  <div class="dashboard-list--filter">
    <form class="dashboard-list--form jquery-once-1-processed" action="/editor/dashboard/content" method="get" id="views-exposed-form-loop-editor-content-panel-pane-1" accept-charset="UTF-8">
      <div class="views-exposed-widgets">
        <input placeholder="<?php print t('Type parts of title or content to filter the list');?>" class="dashboard-list--filter-field form-text" type="text" id="edit-combine" name="combine" value="" size="30" maxlength="128">
      </div>
      <div class="">
        <input class="dashboard-list--submit form-submit" type="submit" id="edit-submit-loop-editor-content" name="" value="Udfør">
      </div>
    </form>
    <div class="dashboard--sorting">
      <label class="dashboard--filter-label"><?php print t('Sort by');?></label>
      <div class="dashboard--sort-links">
        <a href="#" class="dashboard--sort-link is-active js-sort-link"><?php print t('Newest');?></a>
        <a href="#" class="dashboard--sort-link js-sort-link"><?php print t('Oldest');?></a>
        <a href="#" class="dashboard--sort-link js-sort-link js-dashboard-alphabetical"><?php print t('Alphabetical');?></a>
      </div>
    </div>
  </div>

  <div class="dashboard-list js-dashboard-other-content">
    Insert here
  </div>

  <div class="dashboard-list--more-link">
    <a href="/editor/dashboard/content?combine="><?php print t('show all content');?></a>
  </div>
</div>


<?php
// This is used to enrich the above results.
?>
<script id="js-list-item-template-other-content" type="text/x-handlebars-template">
  <div class="dashboard-list--item">
    <a href="/node/{{nid}}/edit" class="dashboard-list--icon"> </a>
    <p class="dashboard-list--text">
      <a href="/node/{{nid}}">{{title}}</a>
    </p>
    <span class="dashboard-list--meta-data">
    <?php print t('Content, created');?> {{date}}
    </span>
  </div>
</script>