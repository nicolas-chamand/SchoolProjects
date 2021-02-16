
<script type="text/javascript">
	var mymap = L.map('mapid').setView([45.756505, 4.830894], 13);

	L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token={accessToken}', {
	    attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, <a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
	    maxZoom: 18,
	    id: 'mapbox/streets-v11',
	    accessToken: 'pk.eyJ1IjoiZmFudG9tNDQwIiwiYSI6ImNrM3hqZzNsdDAwZjUzbXVzNmJnNGVmZGcifQ.DUglhBudaWxwbV5857I9rA'
	}).addTo(mymap);

	<?php
		$req1 = "SELECT COUNT(idQ) FROM p1908794.Quartiers;";
		$nbQ =  mysqli_fetch_assoc(mysqli_query($connexion, $req1));
	?>
	
	var tab_polygons = []; // Pour stocker les objets polygon Javascript
	<?php for($i = 1; $i<=$nbQ['COUNT(idQ)']; $i++) 
		{
		$req_temp1 = "SELECT COUNT(idCoord)
		FROM Quartiers NATURAL JOIN Localiser NATURAL JOIN Coordonnees
		WHERE idQ = $i;";
		$req_temp2 = "SELECT coordX, coordY
		FROM Quartiers NATURAL JOIN Localiser NATURAL JOIN Coordonnees
		WHERE idQ = $i
		ORDER BY idCoord;";
		$req_temp3 = "SELECT nomQ
		FROM Quartiers
		WHERE idQ = $i;";

		$nbCoord = mysqli_fetch_assoc(mysqli_query($connexion, $req_temp1)); 
		$coords = mysqli_query($connexion, $req_temp2);
		$nomQ = mysqli_fetch_assoc(mysqli_query($connexion, $req_temp3));
	?>
	var latlongs = [
		<?php for($j=1; $j<$nbCoord['COUNT(idCoord)']; $j++) 
			  {?>
			  	<?php $coord = mysqli_fetch_assoc($coords);?>
			  	<?="[".$coord['coordX'].", ".$coord['coordY']."], "?>
			  <?php } ?>
			  <?php $coord = mysqli_fetch_assoc($coords); ?>
			  <?="[".$coord['coordX'].", ".$coord['coordY']."]"?>
		];
		var polygon = L.polygon(latlongs).addTo(mymap);
		tab_polygons.push(polygon);
	<?php } ?>

	<?php 
		$requete_aff = "SELECT idQ, nomQ, nomC, GROUP_CONCAT(idQArrive), GROUP_CONCAT(transport)
		FROM p1908794.Commune NATURAL JOIN p1908794.Quartiers INNER JOIN p1908794.Routes ON idQ = idQDepart
		GROUP BY idQ
		ORDER BY idQ;";

		$quartiers = mysqli_query($connexion, $requete_aff);
		$ind = 0;
		while($quartier = mysqli_fetch_assoc($quartiers))
		{?>
			tab_polygons[<?=$ind?>].bindPopup("<p><span class='info'>ID du quartier : <?=$quartier['idQ']?></span>"+"</br><span class='info'>Nom du quartier : <?=$quartier['nomQ']?></span>"+"</br><span class='info'>Nom de la commune : <?=$quartier['nomC']?></span>"+"</br><span class='info'>Quartiers d'arrivés possible : <?=$quartier['GROUP_CONCAT(idQArrive)']?></span>"+"</br><span class='info'>Transport correspondant : <?=$quartier['GROUP_CONCAT(transport)']?></span></p>", {maxWidth: 600});
			<?php $ind++; ?>
  <?php } ?>
	
</script>
