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
    <a href="/" class="logo--link"><img src="<?php echo $path_to_theme; ?>/logo.png" alt="" class="logo--image"></a>
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
<div class="search--autocomplete">
  <h4 class="search--autocomplete-header">Spørgsmål andre har stillet</h4>
  <a href="#" class="search--autocomplete-link">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?</a>
  <a href="#" class="search--autocomplete-link">I hvilket special ark skal terapeuter i plejeboliger visitere i?</a>
  <a href="#" class="search--autocomplete-link">Skal der oprettes et Fokusområder der hedder ernæring, hvis en borger scorer 0 i en ernæringsvurdering?</a>
  <a href="#" class="search--autocomplete-link">Skal køkkenpersonale, som samarbejder tæt med beboere, plejepersonale og terapeuter omkring ernæring dokumentere om ernærings indsatser?</a>
</div>
</body>
</html>
