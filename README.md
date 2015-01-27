Special needs for Aarhus municipality

Two patches:  
`https://www.drupal.org/files/issues/2316693-make-version2-compatible-11.patch`
`https://www.drupal.org/files/issues/2316693-make-version2-compatible-12.patch`

As Aarhus municipality isn't supporting RequestedAuthnContext this should be removed from: includes/saml_sp.AuthnRequest.inc:

`
<samlp:RequestedAuthnContext Comparison="exact">
	<saml:AuthnContextClassRef>{$idpData['AuthnContextClassRef']}</saml:AuthnContextClassRef>
</samlp:RequestedAuthnContext>
`
