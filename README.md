# Installation
This README assumes that you have install a configured your server with a
working Apache/Nginx. The stack should be optimized to run a Drupal site.

## Dependencies
* [Drush 6.1.0](https://github.com/drush-ops/drush)

## Production
```sh
  ~$ drush make https://raw.github.com/loopdk/profile/master/drupal.make loop
```

## Development
If you want a developer version with _working copies_ of the Git repositories,
run this command instead.

```sh
  ~$ drush make --working-copy https://raw.github.com/loopdk/profile/development/drupal.make loop
```

## Setting up Loop

After running the make file you should install the site as any other Drupal website.
By default only the core features are enabled so you should visit the features overview and enable any additional features you would need.


### Setup for development

Enable the Loop example content feature and create a demo user account.
You can drush dl and drush en the Devel module and use this for generating content.

## Apache Solr

Loop uses [Apache Solr](http://lucene.apache.org/solr/) for searching (and indexing) content using the "[Search API Solr Search](https://www.drupal.org/project/search_api_solr)" module.

The default Solr server settings are

```
  host: localhost
  port: 8983
  path: /solr/loop_stg
```

After installation these settings should be changed to match the actual Solr server setup (Go to [Home » Administration » Configuration » Search and metadata » Search API](/admin/config/search/search_api)
and edit the server named "Default"). See the documentation on [Search API Solr Search](https://www.drupal.org/project/search_api_solr) for details on how to get Solr up and running.

If you have Apache Solr running on your local development environment you can create a core named "loop_stg" to make searching work out of the box.


## Adding taxonomies

After installing the loopdk profile you should create some taxomony terms in the vocabularies Keyword, Profession and Subject. At lease one term must be defined in the Subject vocabulary before users can create new posts.

Go to [Home » Administration » Structure » Taxonomy](/admin/structure/taxonomy) to add terms to the vocabularies.

As an alternative to manually creating terms, you can install the module [Loop taxonomy terms (loop_taxonomy_terms)](/admin/modules#loop_content) and get the default Loop taxonomy terms.
