<div class="">
  <div class="dashboard-list--filter">
    <form class="dashboard-list--form" accept-charset="UTF-8">
      <div class="views-exposed-widgets">
        <input placeholder="<?php print t('Type parts of title or content to filter the list');?>" class="dashboard-list--filter-field form-text js-comments-text-filter" type="text" id="edit-combine" name="combine" value="" size="30" maxlength="128">
      </div>
      <div class="">
        <input class="dashboard-list--submit form-submit" type="submit" id="edit-submit-loop-editor-content" name="" value="Udfør">
      </div>
    </form>
    <div class="dashboard--sorting">
      <label class="dashboard--filter-label"><?php print t('Sort by');?></label>
      <div class="dashboard--sort-links">
        <a href="#" class="js-has-answers-removed dashboard--sort-link js-comments-sort-filter js-comments-sort-newest is-active"><?php print t('Newest');?></a>
        <a href="#" class="js-has-answers-removed dashboard--sort-link js-comments-sort-filter js-comments-sort-oldest "><?php print t('Oldest');?></a>
        <a href="#" class="js-has-answers-removed dashboard--sort-link js-comments-sort-filter js-comments-sort-alphabetic is-last"><?php print t('Alphabetical');?></a>
      </div>
    </div>
  </div>

  <div class="dashboard-list js-dashboard-comments">
    <div class="dashboard--spinner">
    </div>
  </div>

  <div class="dashboard-list--more-link">
    <a href="/editor/dashboard/content?combine="><?php print t('show all content');?></a>
  </div>
</div>


<?php
// This is used to enrich the above results.
?>
<script id="js-list-item-template-comments" type="text/x-handlebars-template">
  <div class="dashboard-list--item">
    <div class="">
      <a href="/user/{{uid}}"><img src="{{uri}}" width="192" height="192" alt=""></a>
    </div>
    <a href="/comment/{{cid}}#comment-{{cid}}" class="dashboard-list--icon"> </a>
    <p class="dashboard-list--text">
      <a href="/comment/{{cid}}#comment-{{cid}}">{{subject}}</a>
    </p>
    <span class="dashboard-list--meta-data">
      <p><?php print t('Question');?>: {{content-title}}</p>
    <?php print t('Content, created');?> {{date}}
    </span>
  </div>
</script>