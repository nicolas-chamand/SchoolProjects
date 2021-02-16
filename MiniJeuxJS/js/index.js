$(function()
{
	function bindEvents()
	{
		$("#button").one('click', function()
		{
			if($("[name='Prénom']").val() != '')
			{
				Elia.view(["Bon, pas le temps de te ré-expliquer, j'ai beaucoup de monde à accueillir, j'imagine que tu sais ce qui t'attends ! ", 
					`Eh bien ${$("[name='Prénom']").val()} ! Ne reste pas planté là ! Si tu es prêt, dépêche toi de cliquer sur <a id="real_bt" href='html/menu.html'>continuer</a>`]);
				let $img = $("<div id='txt_align'><img class='continue_button' src='images/button_continue.png' alt='bouton continuer'></div>");
				$('#welcome').append($img.css('display', 'none').delay(2000).fadeIn(1000));
				$('.continue_button').hover(function()
				{
					$('.continue_button').attr('src', 'images/button_continue_red.png');
				}, function()
				{
					$('.continue_button').attr('src', 'images/button_continue.png');
				});
				$('.continue_button').click(function()
				{
					$('.continue_button').css('position', 'absolute');
					$('.continue_button').css('left', `${Math.floor(Math.random()*101)}%`);
					$('.continue_button').css('top', `${Math.floor(Math.random()*101)}%`);
				});
			}

		});
	}

	// Premier affichage de l'IA ------ //
	let tab_txt = ["Bonjour je suis Elia.", "Bienvenu sur notre site web interactif de mini-jeux !", 
		"Tu es peut-être nouveau ici ? Rappel-moi ton prénom.",
		"Ah oui, je me souviens ! Tu t'appelles <input type='text' name='Prénom'> <input id='button' type='button' name='Valider' value='Valider'>"];
	let Elia = new IA('#welcome');

	setTimeout(function()
	{
		Elia.view(tab_txt);
	}, 	800);
	setTimeout(function()
	{
		bindEvents();
	}, 7000);
		
});