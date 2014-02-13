api = 2
core = 7.x

; Download Drupal core and apply core patches if needed.
projects[drupal][type] = "core"
projects[drupal][patch][] = "https://drupal.org/files/drupal-menu_navigation_links-1018614-83.patch"

; Install profile.
projects[loopdk][type] = "profile"
projects[loopdk][download][type] = "git"
projects[loopdk][download][url] = "git@github.com:loopdk/profile.git"
projects[loopdk][branch] = "development"
