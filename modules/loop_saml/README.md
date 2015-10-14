# Loop saml

## Post-installation configuration

Users must be created automatically after signing in through ADFS. To
enable this, go to `/admin/config/people/accounts > Registration and
cancellation > Who can register accounts?` and check "Visitors".


## Special needs for Aarhus municipality

Aarhus municipality does not support RequestedAuthnContext so we need
to apply the patch
[Aarhus-municipality-does-not-support-RequestedAuthnContext.patch](https://github.com/loopdk/profile/blob/development/patches/Aarhus-municipality-does-not-support-RequestedAuthnContext.patch)
to the contrib module
[saml_sp](https://www.drupal.org/project/saml_sp).
