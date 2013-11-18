api = 2
core = 7.x

; Core
projects[drupal][type] = "core"

; Install profile.
projects[loopdk][type] = "profile"
projects[loopdk][download][type] = "git"
projects[loopdk][download][url] = "https://github.com/loopdk/profile"
projects[loopdk][branch] = "master"

; Modules
projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.6"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.3"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[entity][subdir] = "contrib"
projects[entity][version] = "1.2"

projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.3"

projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[field_group][subdir] = "contrib"
projects[field_group][version] = "1.3"

projects[flag][subdir] = "contrib"
projects[flag][version] = "3.2"

projects[globalredirect][subdir] = "contrib"
projects[globalredirect][version] = "1.5"

projects[google_analytics][subdir] = "contrib"
projects[google_analytics][version] = "1.4"

projects[html5_tools][subdir] = "contrib"
projects[html5_tools][version] = "1.2"

projects[jquery_update][subdir] = "contrib"
projects[jquery_update][version] = "2.3"

projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "1.0-beta3"

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.1"

projects[link][subdir] = "contrib"
projects[link][version] = "1.1"

projects[memcache][subdir] = "contrib"
projects[memcache][version] = "1.0"

projects[menu_block][subdir] = "contrib"
projects[menu_block][version] = "2.3"

projects[messaging][subdir] = "contrib"
projects[messaging][version] = "1.0-alpha2"

projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.0-beta7"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "1.8"

projects[notifications][subdir] = "contrib"
projects[notifications][version] = "1.0-alpha2"

projects[og][subdir] = "contrib"
projects[og][version] = "2.3"

projects[page_title][subdir] = "contrib"
projects[page_title][version] = "2.7"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[redirect][subdir] = "contrib"
projects[redirect][version] = "1.0-rc1"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[token][subdir] = "contrib"
projects[token][version] = "1.5"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.1"

projects[rules][subdir] = "contrib"
projects[rules][version] = "2.6"

projects[views][subdir] = "contrib"
projects[views][version] = "3.7"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.1"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.2"

; Libraries
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.2/ckeditor_3.6.2.zip"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][destination] = "libraries"
