<?php if (!empty($variables['login_services'])): ?>
<div class="user-profile-wrapper">
  <h2 class="user-profile-header"><?php print t('Use login service'); ?></h2>
  <div class="user-profile--login-text">
  <?php foreach ($variables['login_services'] as $service): ?>
    <a class="user-profile--login-link button--action" href="<?php print $service['url'] ?>"><?php print $service['name']; ?></a>
  <?php endforeach ?>
  </div>
</div>

<div class="loop-user-login-form-wrapper" id="loop-login">
  <div class="form-items">
    <fieldset class="user-profile-module--field-group-fieldset-personal-info">
      <legend class="fieldset-legend"><?php print(t('Loop login')); ?></legend>
      <?php print drupal_render_children($form) ?>
    </fieldset>
  </div>
</div>
<?php else: ?>
<div class="loop-user-login-form-wrapper">
  <div class="form-items">
    <?php print drupal_render_children($form) ?>
  </div>
</div>
<?php endif ?>
