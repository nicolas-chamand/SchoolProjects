<?php
	
	// CHAMAND Nicolas n° étudiant 11908794
	// et OKOUNLOLA BIAOU Olaniran n° étudiant 11925826

	session_start(); // démarre ou reprend une session
	require('inc/constantes.php');
	require('inc/includes.php'); // inclut le fichier avec fonctions (notamment celles du modele)
	require('inc/routes.php'); // fichiers de routes

	if(isset($_GET['page'])) 
	{
		$nomPage = $_GET['page'];
		
		if(isset($routes[$nomPage])) 
		{
			$controleur = $routes[$nomPage]['controleur'];
			$vue = $routes[$nomPage]['vue'];
			include('controleurs/' . $controleur . '.php');
			include('vues/' . $vue . '.php');
		}
	}
	else 
	{
		include('controleurs/controleurAccueil.php');
		include('vues/vueAccueil.php');
	}
?>
