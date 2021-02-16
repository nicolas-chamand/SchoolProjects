<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title><?= $nomSite ?></title>

    <link href="css/stylegeneral.css" rel="stylesheet" media="all" type="text/css">
    <link href="css/stylePartie.css" rel="stylesheet" media="all" type="text/css">
    <link rel="shortcut icon" type="image/x-icon" href="img/scotlandyard_logo.png" />

    <link rel="shortcut icon" type="image/x-icon" href="LOGO SITE/LOGO SCOTLAND YARD 1.0.jpg" />
</head>
<body>
    <?php include('static/header.php'); ?>
    <div id="divCentral">
		<?php include('static/menu.php'); ?>
		<main>

			<?php if(isset($_POST['boutonValider1']) && $valider || isset($_POST['boutonValider2']))
			{
				if(isset($message)) 
				{
					echo "<script type='text/javascript'>alert('$message');</script>";
				}
				echo "<script type='text/javascript'>window.addEventListener('DOMContentLoaded', function() 
				{
		        	document.getElementById('form1').classList.add('cache');
		        	document.getElementById('form2').classList.remove('cache');
		    	}, false);</script>";
	   		}
			else 
			{
				if(isset($message)) 
				{
					echo "<script type='text/javascript'>alert('$message');</script>";
				}
	   		}?>
	   		<?php if( ($valider && isset($_POST['boutonValider1'])) || isset($_POST['boutonValider2']) ) 
				{?>
					<h1 id="nbTour">Tour n°<?=$_SESSION['nbTour']?></h1>
		  <?php } ?>
	   		<div id="form1">
				<h2>Identifiant de connexion</h2>
				<form method="post" action="#">
					<div>
						<label for="nomJ">Saisissez votre prénom : </label>
						<input type="text" name="nomJ" id="nomJ" placeholder="Prénom..." required />
					</div>
					<div>
						<label for="nomJ">Saisissez votre adresse email : </label>
						<input type="text" name="email" id="email" placeholder="nom@domaine.com" required />
					</div>
					<div>
						<h2> Configuration de la partie </h2>
						<input type="radio" id="nbDetectives3" name="nbDetectives" value="3" checked>
						<label for="nbDetectives3">3 détectives</label>
						<input type="radio" id="nbDetectives4" name="nbDetectives" value="4">
						<label for="nbDetectives4">4 détectives</label>
						<input type="radio" id="nbDetectives5" name="nbDetectives" value="5">
						<label for="nbDetectives5">5 détectives</label>
					</div>
					<div>
						<input type="submit" name="boutonValider1" value="Valider"/>
					</div>
					
				</form>
			</div>
			<div class="cache" id="form2">
				<form method="post" action="">
					<p>
						Vous êtes sur le quartier : <?php if(isset($nomQJinit['nomQ'])){ echo $nomQJinit['nomQ'];} ?>
					</p>
					<?php $i=1;
					if(isset($nomQDets))
					{
						foreach($nomQDets as $nomQDet)
						{
							echo "<p>Position du détectives n°".$i.": ".$nomQDet['nomQ']."</p>";
							$i++;
						} 
					} ?>
					<p>Choisissez votre quartier d'arrivé : </p>
					<div>
						<?php while($nomQArrive = mysqli_fetch_assoc($nomQArrives))
						{?>
							<div>
								<input type="radio" name="selectQuartier" value="<?= $nomQArrive['idQArrive']?>" required>
								<label><?php if(isset($nomQArrive['nomQ'])){ echo $nomQArrive['nomQ'];} ?></label>
							</div>
			      <?php } ?>
						</select>
					</div>
					<div>
						<input type="submit" name="boutonValider2" value="Valider"/>
					</div>
					
				</form>
			</div>
			</form>
		</main>
	</div>
    <?php include('static/footer.php'); ?>
    <script type="text/javascript" src="js/pagePartie.js"></script>
</body>
</html>