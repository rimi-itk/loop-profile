drush user-create administrator --mail="administrator@example.com" --password="administrator"
drush user-add-role 'administrator' administrator

drush user-create document-author --mail="document-author@example.com" --password="document-author"
drush user-add-role 'document author' document-author

drush user-create document-collection-editor --mail="document-collection-editor@example.com" --password="document-collection-editor"
drush user-add-role 'document collection editor' document-collection-editor
