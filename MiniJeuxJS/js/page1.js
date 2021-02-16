
$(function()
{
	// ------- Les variables et constantes ------- //
	const mots = ['INTERLUDE', 'ÉTAMINE', 'IMPAVIDE', 'FONTINAL', 'CALLIPYGE', 'CENACLE', 'ORNITHORYNQUE', 'COCCYX',
	'OMBRELLE', 'PROCRASTINATION', 'INCARNADIN', 'ALANGUIR', 'AIGUAIL', 'ÉCHALIER'];
	const alph_maj = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X','Y', 'Z'];
	const alph_code = [65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90];
	var errors = 0;
	var NaL = 0;

	// ------- L'objet pendu et ses méthodes ------- //
	function pendu(id_p, div_img)
	{
		this.id_p = id_p;
		this.div_img = div_img;
	}

	pendu.prototype.reset = function()
	{
		// Initialisation // 
		let self = this;
		errors = 0;
		$(this.id_p).html('');
		$(this.div_img +' img').attr('src', `../images/pendu0.png`);
		$('.letter').css('background-color', 'rgba(0,0,0,0)');
		$('.letter').off('click');
		$(document).off('keydown');
		let tab_l = mots[Math.floor(Math.random()*(mots.length-1))].split('');

		this.parse(tab_l);
		this.events(tab_l);
		this.refresh_button_events();
	}

	pendu.prototype.refresh_button_events = function()
	{
		$('#refresh_button').click(function()
		{
			$pendu.reset();
		});

		$('#refresh_button').hover(function()
		{
			$(this).attr('src', "../images/refresh_button_red.png");
		}, function()
		{
			$(this).attr('src', "../images/refresh_button.png");
		});
	}
	
	pendu.prototype.events = function(tab_l)
	{
		let self = this;
		let pendu = tab_l.slice(1, tab_l.length-1);

		$(document).keydown(function(e)
		{
			let key = alph_maj[alph_code.indexOf(e.keyCode)];
			if(e.keyCode>=65 && e.keyCode<=90)
			{
			$pendu.controller(pendu, key);
			}
			else
			{
				NaL++;
				if (NaL ==3)
				{
					alert('Attention ! Vérifiez que vous appuyez sur des lettres !');
					NaL=0;
				}
			}
		});
		$('.letter').each(function(i)
		{
			$(this).hover(function()
			{
				$(this).css('background-color', 'rgba(0,0,0,0.2)');
			}, function()
			{
				$(this).css('background-color', 'rgba(0,0,0,0)');
			});
			let key = $(this).text();
			$(this).click(function()
				{
					$pendu.controller(pendu, key);
				});
		});
	}

	pendu.prototype.parse = function(tab_l)
	{
		let self = this;
		$(tab_l).each(function(i, elt)
		{
			if (i==0 || i==(tab_l.length-1))
			{
				$(self.id_p).append(`<span>${elt}</span>`);
			}
			else
			{
				$(self.id_p).append(`<span class='l_pendu cache'></span>`);
			}
		});
		$(self.id_p).html($(self.id_p).html()+'<img id="refresh_button" src="../images/refresh_button.png">');
	}

	// ------- LE CONTROLLEUR ------- //
	pendu.prototype.controller = function(pendu, key)
	{
		if(pendu.includes(key))
		{
			$('.letter').each(function(i)
			{
				if ($(this).text() == key)
				{
					$(this).off('mouseenter mouseleave');
					$(this).css('background-color', 'green');
				}
			});	

			let i = 0;
			let index_tab = [];
			while (pendu.indexOf(key, i) != -1)
			{
				index_tab.push(pendu.indexOf(key, i));
				i = pendu.indexOf(key, i)+1;
			}
			for (let j of index_tab)
			{
				$('.l_pendu').eq(j).removeClass('cache');
				$('.l_pendu').eq(j).text(key);
			}

			let pendu_answer = [];
			$('.l_pendu').each(function()
			{
				pendu_answer.push($(this).text());
			});
			if(pendu.join() === pendu_answer.join())
			{
				alert('Vous avez gagné !')
				$('.letter').off('click');
				$(document).off('keydown');
			}
		}
		else
		{
			$('.letter').each(function(i)
			{
				if ($(this).text() == key)
				{
					$(this).off('click mouseenter mouseleave');
					$(this).css('background-color', 'red');
				}
			});

			errors++;
			if(errors<11)
			{
			$(this.div_img +' img').attr('src', `../images/pendu${errors}.png`);
			}
			else
			{
				$(this.div_img +' img').attr('src', `../images/pendu${errors}.png`);
				$('.letter').off('click mouseenter mouseleave');
				$(document).off('keydown');
				alert('Vous avez perdu !');
				$('.l_pendu').each(function(i)
				{
					$(this).removeClass('cache');
					$(this).text(pendu[i]);
				});
			}	
		}
	}

	// ------- Programme principale ------- //
	// Premier affichage de l'IA //
	let tab_txt = ["Bienvenu sur le jeu du pendu !", "Les règles sont simples.", 
		"Trouves le mot mystère, à l'aide des boutons de ton clavier ou des lettres à l'écran, avant la pendaison du personnage !",
		"Attention, 11 coups te sont permis ! A toi de jouer ! ", "Note : Je suis un peu occupé en ce moment, donc je te laisse chercher la signification des mots que tu n'as pas trouvé... :'D"];
	let Elia = new IA('#help_text');
	setTimeout(function()
	{
		Elia.view(tab_txt);
		$('.fixed').toggleClass('toggle');
		$('#global').css('filter', 'blur(5px)');
		$('#arrow').css('transform', 'rotate(0deg)');
	}, 	500);

	let $pendu = new pendu('#p_pendu', '#div_img_pendu');
	$pendu.reset();
});