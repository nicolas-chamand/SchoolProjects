<!DOCTYPE html>
<html>
	<head>
	    <meta charset="utf-8" />
	    <title><?= $nomSite ?></title>
	    <link href="css/stylegeneral.css" rel="stylesheet" media="all" type="text/css">
	    <link rel="stylesheet" type="text/css" href="css/styleAccueil.css">
	    <!-- ajoute une image favicon (dans l'onglet du navigateur) -->
	    <link rel="shortcut icon" type="image/x-icon" href="img/scotlandyard_logo.png" />
	</head>
	<body>
	    <?php include('static/header.php'); ?>
	    <div id="divCentral">
			<?php include('static/menu.php'); ?>
			<main>
				<div class = "center">
					<h2>Êtes-vous à la recherche de Mister X ? Nous aussi !</h2>
					<p class = "welcomemsg"> Bienvenue sur notre site ! </p>
				<p>Poursuivez Mister X dans une course mouvementée à travers la ville lumière. 
				Aidez-vous de 3,4 ou même 5 détectives autant devoués à la cause que vous !</p>
				<p>Grâce à nos radars, nous pourrons vous aidez à identifier la position de Mister X à certains tours et surtout les 
				moyens de transports qu'il emprunte!</p>
				<p class = "welcomemsg" >À VOUS DE JOUER BRAVE DÉTECTIVE!!! </p> </div>
				
			</main>
		</div>
	    <?php include('static/footer.php'); ?>
	</body>
</html>