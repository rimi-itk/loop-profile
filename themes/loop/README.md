Loop theme
==========

This repository is the default theme for the Loop web application.

Sass is based on ITK Designs boilerplate found here,
https://github.com/aakb/frontend-boilerplate


Building the stylesheet
-----------------------

First, install requirements:

```
npm install
```

Then build the stylesheet by running this command

```
gulp sass
```

To continuosly update the stylesheet when editing the source scss
files you can run

```
gulp watch sass
```

Add `--env=dev` to the command to include source maps in the generated
stylesheet:

```
gulp watch sass --env=dev
```

Finally, you should build the stylesheet for production like this
```
gulp build
```


Building the icon font
----------------------

A custom font is used for icons on the site. The font is built using
[Fontello](http://fontello.com/).

Perform these steps to update the font:

1. `cd icons/`
2. `make fontopen`
3. Make any changes on the opened web page and click `Save session`.
4. `make fontsave`
