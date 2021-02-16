<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title><?= $nomSite ?></title>
        <link href="css/stylegeneral.css" rel="stylesheet" media="all" type="text/css">
        <link href="css/styleAfficher.css" rel="stylesheet" media="all" type="text/css">
        <link rel="shortcut icon" type="image/x-icon" href="img/scotlandyard_logo.png" />
         <!-- Style permetant le bon fonctionnement de Leaflet -->
        <link rel="stylesheet" href="https://unpkg.com/leaflet@1.6.0/dist/leaflet.css" integrity="sha512-xwE/Az9zrjBIphAcBb3F6JVqxf46+CDLwfLMHloNu6KEQCAWi6HcDUbeOfBIptF7tcCzusKFjFw2yuvEpDL9wQ==" crossorigin=""/>
    </head>
    <body>
        <?php include('static/header.php'); ?>
        <div id="divCentral">
    		<?php include('static/menu.php'); ?>
    		<main>
                <h3>
                    L'affichage des données se fait avec une carte (utilisation de Leaflet). Cliquer sur un polygon représentant un quartier permet de savoir son ID dans la base, son nom, les quartiers d'arrivés possible depuis le quartier en question etc...
                </h3>
    			<div id="mapid">

    			</div>

    		</main>
    	</div>
        <?php include('static/footer.php'); ?>
    </body>
    <!-- Script permetant le bon fonctionnement de Leaflet -->
    <script src="https://unpkg.com/leaflet@1.6.0/dist/leaflet.js" integrity="sha512-gZwIG9x3wUXg2hdXF6+rVkLF/0Vi9U8D2Ntg4Ga5I5BZpVkVxlJWbSQtXPSiUTtC0TjtGOmxa1AJPuV0CPthew==" crossorigin=""></script>
    <?php include('js/scriptAfficher.php'); ?>
</html>

