<?php

$connexion = getConnexionBD(); // connexion à la BD
mysqli_set_charset ($connexion,"utf8"); //Modifie le jeu de caratères en UTF-8 

// Supprime toutes les données de notre base
$req_delete1 = "DELETE FROM p1908794.Routes;";
$req_delete2 = "DELETE FROM p1908794.Quartiers;";
$req_delete3 = "DELETE FROM p1908794.Commune;";

mysqli_query($connexion, $req_delete1); 
mysqli_query($connexion, $req_delete2);
mysqli_query($connexion, $req_delete3);


//MIGRATIONS DES DONNEES DE LA BASE DATASET VERS NOTRE BASE
$requete1 = "INSERT INTO p1908794.Commune(CP, nomC, departement)
SELECT cpCommune, nomCommune, departement
FROM dataset.Quartiers
GROUP BY cpCommune;";

$requete2 = "INSERT INTO p1908794.Quartiers(idQ, nomQ, codeInsee, typeQ, CP)
SELECT idQ, nomQ, codeInsee, typeQ, cpCommune
FROM dataset.Quartiers
GROUP BY idQ;";

$requete3 = "INSERT INTO p1908794.Routes(idQDepart, idQArrive, transport, isQuartierDepart)
SELECT idQuartierDepart, idQuartierArrivee, transport, isQuartierDepart
FROM dataset.Routes
GROUP BY idQuartierDepart, idQuartierArrivee, transport;";

mysqli_query($connexion, $requete1);
mysqli_query($connexion, $requete2);
mysqli_query($connexion, $requete3);


?>