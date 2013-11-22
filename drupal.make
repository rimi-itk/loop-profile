api = 2
core = 7.x

; Download Drupal core and apply core patches if needed.
projects[drupal][type] = "core"

; Install profile.
projects[loopdk][type] = "profile"
projects[loopdk][download][type] = "git"
projects[loopdk][download][url] = "git@github.com:loopdk/profile.git"
projects[loopdk][branch] = "master"
