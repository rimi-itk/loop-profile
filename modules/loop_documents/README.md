Loop documents
==============

Documents and document collections.

# Installation

Activate the `loop_documents` module:

```
drush --yes pm-enable loop_documents
```

## Post installation

Rebuild secure permissions:

```
drush secure-permissions-rebuild
```

You may also have to rebuild node access:

```
drush php-eval 'node_access_rebuild();'
```

# Settings

A few setting are available on the configuration page *Administration » Configuration » Content authoring »
Loop documents settings* (/admin/config/content/loop_documents)
