This module contains a default configuration for search node.

The API keys and indexes can be overridden in the settings.php using these 
variables.

```php
$conf['search_api_loop_search_node_apikey'] = '';
$conf['search_api_loop_search_node_apikey_readonly'] = '';
$conf['search_api_loop_search_node_host'] = 'https://localhost';

$conf['search_api_loop_search_node_index_posts'] = '';
$conf['search_api_loop_search_node_index_auto_complete'] = '';
```

# Search node mappings`
This is the mappings/configuration used inside serarch node.

```json
{
  "bd6f534b05ab6073e04afef2c67e7e44": {
    "name": "LOOP typeahead",
    "fields": [
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "analyzer_startswith",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "title",
        "default_indexer": "analyzed"
      }
    ],
    "dates": [],
    "tag": "private"
  }
}
```

```json
{
  "833bc3ffdcd187e4bf72945e7fe4a08d": {
    "name": "LOOP posts",
    "fields": [
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": true,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "title"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analysed",
        "sort": false,
        "indexable": false,
        "raw": false,
        "geopoint": false,
        "field": "status"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "comments"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "body:value"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "body:summary"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "field_description:value"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "field_keyword:name"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "field_profession:name"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "field_subject:name"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": false,
        "geopoint": false,
        "field": "comments:comment_body:value"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analysed",
        "sort": false,
        "indexable": false,
        "raw": false,
        "geopoint": false,
        "field": "url"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analysed",
        "sort": false,
        "indexable": false,
        "raw": false,
        "geopoint": false,
        "field": "field_external_link:url"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "analyzed",
        "sort": false,
        "indexable": true,
        "raw": true,
        "geopoint": false,
        "field": "field_subject"
      },
      {
        "type": "string",
        "country": "DK",
        "language": "da",
        "default_analyzer": "string_index",
        "default_indexer": "not_analyzed",
        "sort": false,
        "indexable": true,
        "raw": true,
        "geopoint": false,
        "field": "type"
      }
    ],
    "dates": [
      "created",
      "changed"
    ],
    "tag": "private",
    "suggesters": [
      {
        "field": "title",
        "type": "completion"
      }
    ]
  }
}
```
