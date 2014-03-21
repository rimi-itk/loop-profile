<h3><?php print t('Your reply'); ?></h3>
<div class="meta-data--author">
  <?php if(!empty($user_obj->picture)) : ?>
    <div class="meta-data--author-image">
      <a href="/user/<?php print $user->uid;?>"><img src="<?php print image_style_url('profile', $user_obj->picture->uri); ?>"/></a>
    </div>
  <?php endif;?>
  <div class="meta-data--author-wrapper">
    <a href="/user/<?php print $user->uid;?>"><?php print $user_name; ?></a>
    <span class="meta-data--author-title"><?php print $jobtitle; ?></span>
  </div>
</div>