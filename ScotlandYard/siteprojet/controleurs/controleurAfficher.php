<?php

$connexion = getConnexionBD(); // connexion à la BD
mysqli_set_charset ($connexion,"utf8"); //Modifie le jeu de caratères en UTF-8 


$requete4 = "SELECT coords
FROM dataset.Quartiers
ORDER BY idQ;";

$geometries = mysqli_query($connexion, $requete4);

$i = 1;
$j = 0;

$req1 = "INSERT INTO p1908794.Coordonnees(idCoord, coordX, coordY)";
$req2 = "INSERT INTO p1908794.Localiser(idCoord, idQ)";
while ($geometrie = mysqli_fetch_assoc($geometries))
{
	$json_object = json_decode(substr($geometrie['coords'], 1, strlen($geometrie['coords'])-2));
	foreach ($json_object as $point) 
	{
		mysqli_query($connexion, $req1." VALUES(".($j+1).", ".$point[1].", ".$point[0].");");
		mysqli_query($connexion, $req2." VALUES(".($j+1).", ".$i.");");
		$j++;
	}
	$i++;
}


?>