<?php 
$connexion = getConnexionBD(); // connexion à la BD
mysqli_set_charset ($connexion,"utf8"); //Modifie le jeu de caratères en UTF-8 

// Insertion d'une configuration par défaut
$dateConf = date("Y-m-d");
$req_conf = "INSERT INTO p1908794.Configuration(idConf, nomConf, dateConf, strategieConf)
VALUES(1, 'défaut', '".$dateConf."', 'basique')";
mysqli_query($connexion, $req_conf);

$affichage_tours = [3, 8, 13, 18]; // Tableau des tours où le quartier de MisterX sera dévoilé (utilisé plus tard dans le code)

$valider=TRUE;
if(isset($_POST['boutonValider1'])) // formulaire soumis
{ 

	$nomJ = mysqli_real_escape_string($connexion, $_POST['nomJ']); // recuperation des valeurs saisies
	$email = mysqli_real_escape_string($connexion, $_POST['email']);

	//Vérifie si la base contient déjà la joueuse
	$requete1 = "SELECT idJ, nomJ, emailJ
	FROM p1908794.Joueuses
	WHERE nomJ='".$nomJ."' AND emailJ='".$email."';";
	if ($idJ = mysqli_fetch_assoc(mysqli_query($connexion, $requete1)))
	{
		$message = "Connexion à votre compte réussi. Bienvenue !";
		$valider = TRUE;

		$_SESSION['idJ'] = $idJ['idJ']; // Stocke l'ID de la joueuse en session
	}
	//Sinon, l'ajoute dans la base
	else
	{
		$requete4 = "SELECT MAX(idJ) FROM p1908794.Joueuses;";
		$idJ = mysqli_fetch_assoc(mysqli_query($connexion, $requete4));
		$requete2 = "INSERT INTO p1908794.Joueuses(idJ, nomJ, emailJ) VALUES(".($idJ['MAX(idJ)']+1).", '".$nomJ."', '".$email."');";
		$insertion = mysqli_query($connexion, $requete2);
		if($insertion == TRUE)
		{
			$message = "Vous avez bien été inscrit. Bienvenue !";
			$valider = TRUE;
			$_SESSION['idJ'] = ($idJ['MAX(idJ)']+1); // Stocke l'ID de la joueuse en session
		}
		else 
		{
			$message = "Erreur lors de l'insertion des données dans la base. Veuillez réessayer.";
			$valider = FALSE;
		}
	}
}

if(isset($_POST['boutonValider1']) && $valider)
{

	//Création de la partie en BD
	$nbDetectives = $_POST['nbDetectives'];
	$requete4 = "SELECT MAX(idP) FROM p1908794.Partie;";
	$idP = mysqli_fetch_assoc(mysqli_query($connexion, $requete4));
	$dateP = date("Y-m-d");
	
	$requete5 = "INSERT INTO p1908794.Partie(idP, dateP, nbDetective, victoire, idConf, idJ) 
	VALUES(".($idP['MAX(idP)']+1).", '".$dateP."', ".$nbDetectives.", 0, 1, ".$_SESSION['idJ'].");";
	mysqli_query($connexion, $requete5);

	// Initialisation des positions de la joueuse, des détectives et de MisterX

	$positions = [];
	$requete_init = "SELECT idQDepart FROM p1908794.Routes WHERE isQuartierDepart = 1 GROUP BY idQDepart ORDER BY RAND();";
	$idQDeparts = mysqli_query($connexion, $requete_init);
	for($i=1; $i<=($nbDetectives+2); $i++)
	{
		$idQDepart = mysqli_fetch_assoc($idQDeparts);
		$positions[] = $idQDepart['idQDepart'];

	}

	//Stocke les données dans la session
	$_SESSION['idP'] = $idP['MAX(idP)']+1;
	$_SESSION['nbDetectives'] = $nbDetectives; 
	$_SESSION['positions'] = $positions; // Tableau des idQ indiquant la position de la joueuse (en 0), des détective (entre 1 et nbDetectives) et MisterX (en dernier élément)
	$_SESSION['nbTour'] = 1;

	//1er déplacement de MisterX et update de la BD
	$requete_init = "SELECT idQDepart, idQArrive, transport  FROM p1908794.Routes WHERE idQDepart = ".$_SESSION['positions'][count($_SESSION['positions'])-1]." ORDER BY RAND();";
	$RouteMX = mysqli_fetch_assoc(mysqli_query($connexion, $requete_init));
	$_SESSION['positions'][count($_SESSION['positions'])-1] = $RouteMX['idQArrive'];

	$insert = "INSERT INTO p1908794.Tour(nbTour, idP, idQDepart, idQArrive, transport)
	VALUES(".$_SESSION['nbTour'].", ".$_SESSION['idP'].", ".$RouteMX['idQDepart'].", ".$RouteMX['idQArrive'].", '".$RouteMX['transport']."');";
	mysqli_query($connexion, $insert);

	// --------- AFFICHAGE INITIAL --------- (Tour n°1)
	$requete_init = "SELECT nomQ FROM p1908794.Quartiers WHERE idQ = ".$_SESSION['positions'][0].";";
	$nomQJinit = mysqli_fetch_assoc(mysqli_query($connexion, $requete_init));


	// Affichage des quartiers d'arrivé possible (de la joueuse)
	$requete_init = "SELECT idQArrive, nomQ FROM p1908794.Routes INNER JOIN p1908794.Quartiers ON idQArrive = idQ WHERE idQDepart = ".$_SESSION['positions'][0]." GROUP BY idQArrive;";
	$nomQArrives = mysqli_query($connexion, $requete_init);		

	//Affichage des quartiers des détectives
		$nomQDets = [];
		foreach (array_slice($_SESSION['positions'], 1, $_SESSION['nbDetectives']) as $idQDepart) 
		{
			$requete = "SELECT nomQ FROM p1908794.Quartiers WHERE idQ = ".$idQDepart.";";
			$nomQDets[] = mysqli_fetch_assoc(mysqli_query($connexion, $requete));	
		}
}

if(isset($_POST['selectQuartier']))
{
	if(in_array($_POST['selectQuartier'], array_slice($_SESSION['positions'], 1, $_SESSION['nbDetectives']) )) // si le quartier d'arrivé choisi correspond à celui d'un détective
	{
		echo "<script>alert('Ce quartier présente déjà un détective.');</script>";
		// Affichage du quartier de départ (de la joueuse)
		$requete_init = "SELECT nomQ FROM p1908794.Quartiers WHERE idQ = ".$_SESSION['positions'][0].";";
		$nomQJinit = mysqli_fetch_assoc(mysqli_query($connexion, $requete_init));


		// Affichage des quartiers d'arrivés possibles
		$requete_init = "SELECT idQArrive, nomQ FROM p1908794.Routes INNER JOIN p1908794.Quartiers ON idQArrive = idQ WHERE idQDepart = ".$_SESSION['positions'][0]." GROUP BY idQArrive;";
		$nomQArrives = mysqli_query($connexion, $requete_init);	

		//Affichage des quartiers des détectives
		$nomQDets = [];
		foreach (array_slice($_SESSION['positions'], 1, $_SESSION['nbDetectives']) as $idQDepart) 
		{
			$requete = "SELECT nomQ FROM p1908794.Quartiers WHERE idQ = ".$idQDepart.";";
			$nomQDets[] = mysqli_fetch_assoc(mysqli_query($connexion, $requete));	
		}
	}
	elseif($_POST['selectQuartier'] == $_SESSION['positions'][count($_SESSION['positions'])-1]) // Si le quartier choisi correspond à celui de Mister X
	{
		$req_nomQ = "SELECT nomQ FROM Quartiers WHERE idQ = ".$_POST['selectQuartier'].";";
		$nomQ = mysqli_fetch_assoc(mysqli_query($connexion, $req_nomQ));
		echo "<script>alert('Vous êtes sur le quartier de Mister X. Bravo ! MisterX était sur le quartier ".$nomQ['nomQ']."');</script>";

		//Update de la partie (victoire)
		$req_update = "UPDATE p1908794.Partie SET victoire=true WHERE idP =".$_SESSION['idP'].";";
		mysqli_query($connexion, $req_update);

		header("Refresh:0; url=index.php?page=partie");
	}
	elseif($_SESSION['nbTour']<20)
	{
		$_SESSION['nbTour']++;
		$_SESSION['positions'][0] = $_POST['selectQuartier']; //Changement de la position de la joueuse

		if(in_array($_SESSION['nbTour'], $affichage_tours)) // si le nombre de tour correspond à celui du tour d'affichage du quartier de MisterX
		{
			$req = "SELECT nomQ FROM Quartiers WHERE idQ = ".$_SESSION['positions'][count($_SESSION['positions'])-1].";";
			$nomQMX = mysqli_fetch_assoc(mysqli_query($connexion, $req));
			echo "<script>alert('MisterX est dans le quartier ".$nomQMX['nomQ'].". Retenez bien !');</script>";
		}

		//déplacement de MisterX et update de la BD
		$requete_init = "SELECT idQDepart, idQArrive, transport  FROM p1908794.Routes WHERE idQDepart = ".$_SESSION['positions'][count($_SESSION['positions'])-1]." ORDER BY RAND();"; //Choisis aléatoire un quartier d'arrivé par ceux qui sont possibles
		$RoutesMX = mysqli_query($connexion, $requete_init);
		$RouteMX = mysqli_fetch_assoc($RoutesMX);
		while (in_array($RouteMX['idQArrive'], array_slice($_SESSION['positions'], 0, $_SESSION['nbDetectives']+1))) // Si l'idQ d'arrivé de Mister correspond à celui d'un détective
		{
			$RouteMX = mysqli_fetch_assoc($RoutesMX);
		}

		if($RouteMX == NULL) //Si $RouteMX == NULL alors tous les quartiers d'arrivé possible de MisterX sont occupés
		{
			$req_nomQ = "SELECT nomQ FROM Quartiers WHERE idQ = ".$_POST['selectQuartier'].";";
			$nomQ = mysqli_fetch_assoc(mysqli_query($connexion, $req_nomQ));
			echo "<script>alert('Vous avez encercler Mister X. Bravo ! MisterX était sur le quartier ".$nomQ['nomQ']."');</script>";

			//Update de la partie (victoire)
			$req_update = "UPDATE p1908794.Partie SET victoire=true WHERE idP =".$_SESSION['idP'].";";
			mysqli_query($connexion, $req_update);

			header("Refresh:0; url=index.php?page=partie");
		}
		else
		{
			$_SESSION['positions'][count($_SESSION['positions'])-1] = $RouteMX['idQArrive'];

			$insert = "INSERT INTO p1908794.Tour(nbTour, idP, idQDepart, idQArrive, transport)
			VALUES(".$_SESSION['nbTour'].", ".$_SESSION['idP'].", ".$RouteMX['idQDepart'].", ".$RouteMX['idQArrive'].", '".$RouteMX['transport']."');";
			mysqli_query($connexion, $insert);
			

			//permet de visualiser la position de Mister X //
			/*$affichage = "SELECT nomQ FROM Quartiers WHERE idQ = ".$RouteMX['idQArrive'].";";
			$idQ = mysqli_fetch_assoc(mysqli_query($connexion, $affichage));
			var_dump($insert);
			var_dump($idQ['nomQ']);*/
		}
		
		//déplacement des détectives
		$i=1;
		foreach (array_slice($_SESSION['positions'], 1, $_SESSION['nbDetectives']) as $idQDepart) 
		{
			$requete= "SELECT idQDepart, idQArrive, transport  FROM p1908794.Routes WHERE idQDepart = ".$idQDepart.";";
			$RoutesDet = mysqli_query($connexion, $requete);

			$trouver = FALSE;
			while($RouteDet = mysqli_fetch_assoc($RoutesDet)) //tant que des tuples existent
			{
				if($RouteDet['idQArrive'] == $_SESSION['positions'][count($_SESSION['positions'])-1]) // on vérifie si le quartier d'arrivé est celui de MisterX
				{
					$trouver = TRUE;
					$req_nomQ = "SELECT nomQ FROM Quartiers WHERE idQ = ".$_POST['selectQuartier'].";";
					$nomQ = mysqli_fetch_assoc(mysqli_query($connexion, $req_nomQ));

					echo "<script>alert('Un détective est sur le quartier de MisterX. Bravo ! MisterX était sur le quartier ".$nomQ['nomQ']."');</script>";
					//Update de la partie (victoire)
					$req_update = "UPDATE p1908794.Partie SET victoire=true WHERE idP =".$_SESSION['idP'].";";
					mysqli_query($connexion, $req_update);
					header("Refresh:0; url=index.php?page=partie");
				}
			}
			
			if (!$trouver) // Si aucune route de mène au quartier de MisterX
			{
				$requete= "SELECT idQDepart, idQArrive, transport  FROM p1908794.Routes WHERE idQDepart = ".$idQDepart." ORDER BY RAND();"; // Permet de choisir aléatoire un quartier d'arrivé par ceux qui sont possible
				$RoutesDet = mysqli_query($connexion, $requete);
				$RouteDet = mysqli_fetch_assoc($RoutesDet);
				$_SESSION['positions'][$i] = $RouteDet['idQArrive'];
			}
			$i++;
		}
		
		// Affichage du quartier de départ (de la joueuse)
		$requete_init = "SELECT nomQ FROM p1908794.Quartiers WHERE idQ = ".$_SESSION['positions'][0].";";
		$nomQJinit = mysqli_fetch_assoc(mysqli_query($connexion, $requete_init));


		// Affichage des quartiers d'arrivés possibles
		$requete_init = "SELECT idQArrive, nomQ FROM p1908794.Routes INNER JOIN p1908794.Quartiers ON idQArrive = idQ WHERE idQDepart = ".$_SESSION['positions'][0]." GROUP BY idQArrive;";
		$nomQArrives = mysqli_query($connexion, $requete_init);	

		//Affichage des quartiers des détectives
		$nomQDets = [];
		foreach (array_slice($_SESSION['positions'], 1, $_SESSION['nbDetectives']) as $idQDepart) 
		{
			$requete = "SELECT nomQ FROM p1908794.Quartiers WHERE idQ = ".$idQDepart.";";
			$nomQDets[] = mysqli_fetch_assoc(mysqli_query($connexion, $requete));	
		}
	}
	else
	{
		$_SESSION['nbTour']=0;

		// Initialisation des positions de la joueuse, des détectives et de MisterX
		$positions = [];
		$requete_init = "SELECT idQDepart FROM p1908794.Routes WHERE isQuartierDepart = 1 GROUP BY idQDepart;";
		$idQDeparts = mysqli_query($connexion, $requete_init);
		for($i=1; $i<=($nbDetectives+2); $i++)
		{
			$idQDepart = mysqli_fetch_assoc($idQDeparts);
			$positions[] = $idQDepart['idQDepart'];

		}
		$_SESSION['positions'] = $positions;

		echo "<script>alert('Vous avez perdu...');</script>";
		header("Refresh:0; url=index.php?page=partie");
	}	
}


?>
