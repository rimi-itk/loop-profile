# Loop saml

## Post-installation configuration

Users must be created automatically after signing in through ADFS. To
enable this, go to `/admin/config/people/accounts > Registration and
cancellation > Who can register accounts?` and check "Visitors".


## Special needs for Aarhus municipality

Aarhus municipality does not support RequestedAuthnContext so we need
to apply the patch
[Aarhus-municipality-does-not-support-RequestedAuthnContext.patch](https://raw.githubusercontent.com/os2loop/profile/396e43eefdf47d140230f39c5d97bd91053e7538/patches/Aarhus-municipality-does-not-support-RequestedAuthnContext.patch)
to the contrib module
[saml_sp](https://www.drupal.org/project/saml_sp):

```
cd profiles/loopdk/modules/contrib/saml_sp/
curl --location --silent https://raw.githubusercontent.com/os2loop/profile/396e43eefdf47d140230f39c5d97bd91053e7538/patches/Aarhus-municipality-does-not-support-RequestedAuthnContext.patch | patch --strip=1
```
