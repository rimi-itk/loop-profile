Please review the [guidelines for
contributing](https://github.com/os2loop/guidelines) to this
repository.

All code submitted must follow the [Drupal coding
standard](https://www.drupal.org/docs/develop/standards/coding-standards).

Before making any pull requests, make sure to check your code by
running

```
phpcs
```

in the `loopdk` profile root folder.

To check only your own changes use something along the lines of

```
phpcs $(git diff master --name-only)
```

See [Installing Coder Sniffer](https://www.drupal.org/node/1419988)
for details on how to install `phpcs`.
