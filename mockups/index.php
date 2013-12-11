<?php
$path_to_theme = "/profiles/loopdk/themes/loop/";
?>
<?php include('inc/head.inc') ?>
<title>LOOP frontpage</title>
</head>

<body>
<?php include('inc/debug.inc') ?>

<header class="header" role="banner">
  <div class="header--inner">
    <a href="/" class="logo--link"><img src="../logo.png" alt="" class="logo--image"></a>
    <nav class="nav">
      <a href="#" title="Min konto" class="nav--link">
        <i class="icon-user"></i>
        <span class="nav--text">Min konto</span>
      </a>
      <a href="#" title="Notifikationer" class="nav--link-mail">
        <i class="icon-mail"></i>
        <span class="nav--text">Notifikationer</span>
        <span class="notification">3</span>
      </a>
      <a href="#" title="Menu" class="nav--link-menu">
        <i class="icon-menu"></i>
        <span class="nav--text">Menu</span>
      </a>
    </nav>
  </div>
</header>
<?php include('inc/search-block.inc') ?>
</body>
</html>
