<?php
$path_to_theme = "/profiles/loopdk/themes/loop/";
?>
<?php include('inc/head.inc') ?>
<title>LOOP - question</title>
</head>

<body>

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
<div class="search--wrapper">
  <form>
    <label class="form-label">Søg efter svar</label>
    <div class="search--field-wrapper">
      <i class="search--icon icon-search"></i>
      <input type="text" placeholder="Skriv f.eks. &quot;Hvordan dokumenteres delvis aktindsigt&quot;" class="search--field">
      <input type="submit" class="search--button" value="Søg">
    </div>
  </form>
</div>
<div class="layout--wrapper">
  <div class="layout--inner">
    <h1 class="page-title">Søgeresultater</h1>
    <div class="search-result">
      <div class="search-result--lead">
        Du søgte på: <strong>Dokumentation</strong>
      </div>
      <?php
        for ($i=1;$i<=10;$i++) {
          echo '
      <div class="search-result--item">
        <span class="meta-data--date">Oprettet den 28. marts 2013</span>
        <a href="question.php" class="search-result--link">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?</a>
        <a href="#" class="search-result--comments">12 svar</a>
      </div>
          ';
        }
      ?>
    </div>
  </div>
</div>
</body>
</html>
