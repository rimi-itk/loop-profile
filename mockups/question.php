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
<div class="search">
  <div class="search--inner">
    <form>
      <label class="form-label">Søg efter svar</label>
      <div class="search--field-wrapper">
        <i class="search--icon icon-search"></i>
        <input type="text" placeholder="Skriv f.eks. &quot;Hvordan dokumenteres delvis aktindsigt&quot;" class="search--field">
        <input type="submit" class="search--button" value="Søg">
      </div>
    </form>
  </div>
</div>
<div class="layout--wrapper">
  <div class="layout--inner">
    <section class="question--wrapper">
      <div class="question--author">
        <a href="#" class="question--author-image">
          <img src="https://s3.amazonaws.com/uifaces/faces/twitter/jackiesaik/128.jpg">
        </a>
        <a href="#" class="question--author-link">Ribena Hutsitove</a>
        <div class="question--author-title">SOSU, AUH, HUH</div>
      </div>
      <div class="question--meta">
        <div class="question--meta-date">Oprettet den 27. februar 2013</div>
        <span class="question--meta-category">Kategori:</span> <a href="#">Dokumentationspraksis</a>
      </div>
      <div class="question--inner">
        <span class="question--header-label">Spørgsmål:</span>
        <h1 class="question--header">Hvordan dokumenteres delvis aktindsigt? Og findes der en vejledning i dokumentation af aktindsigt?</h1>
      </div>
      <div class="question--terms">
        <a href="#" class="question--term">Stamdata</a>
        <a href="#" class="question--term">Partsrepræsentant</a>
        <a href="#" class="question--term">Funktionsvurdering</a>
      </div>
    </div>
  </section>
</div>
</body>
</html>
