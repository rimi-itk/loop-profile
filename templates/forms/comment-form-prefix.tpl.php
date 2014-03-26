<h3><?php print t('Your reply'); ?></h3>
<div class="meta-data--author">
  <div class="meta-data--author-image">
    <a href="/user/<?php print $user->uid;?>"><?php print $author_image; ?></a>
  </div>
  <div class="meta-data--author-wrapper">
    <a href="/user/<?php print $user->uid;?>"><?php print $user_name; ?></a>
    <span class="meta-data--author-title"><?php print $jobtitle; ?></span>
  </div>
</div>