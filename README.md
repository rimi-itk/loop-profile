# Installation
This README assumes that you have install a configured your server with a
working Apache/Nginx. The stack should be optimized to run a Drupal site.

## Dependencies
* [Drush 6.1.0](https://github.com/drush-ops/drush)

# Production
```sh
  ~$ drush make https://raw.github.com/loopdk/profile/master/drupal.make loop
```

# Development
If you want a developer version with _working copies_ of the Git repositories,
run this command instead.
```sh
  ~$ drush make --working-copy https://raw.github.com/loopdk/profile/master/drupal.make loop
```

## Apache Solr
If you have an Apache Solr on your local dev environment you should name the core: _loop_stg_ for seamless integration.
