

$(function()
{
	// ------- Les variables et constantes ------- //
	var z_width = $('.box')[0].offsetWidth;
	const src__red = ["../images/left-arrow-red.png", "../images/right-arrow-red.png"];
	const src__black = ["../images/left-arrow.png", "../images/right-arrow.png"];

		// ------ Objet Slider ------ //
	function Slider(li_list, content_zone)
	{
		this.li_list = $(li_list);
		this.content_zone = $(content_zone);
		this.idScreenSelected = 0;
	}

	Slider.prototype.changeSlide = function(id)
	{
		$('#menu').css('transform', `translateZ(-${z_width/2}px)`);
		this.li_list.eq(this.idScreenSelected).removeClass('selected');
		this.idScreenSelected = id;
	}

	Slider.prototype.view = function()
	{
		let self = this;
		this.li_list.eq(this.idScreenSelected).addClass('selected');
		this.content_zone.each(function(i)
		{
			$(this).css('transform', `rotateY(${(i-self.idScreenSelected)*90}deg)`);
		});
		setTimeout(function()
			{
				$('#menu').css('transform', 'translateZ(0px)');	
			}, 800);
	}
	Slider.prototype.bindEvents = function()
	{
		let self = this;
		$('li').each(function(index)
			{
				$(this).click(function()
				{
					$Slider.changeSlide(index);
					$Slider.view();
				});
			});

		$('#left_arrow').click(function()
			{
				$Slider.changeSlide((self.idScreenSelected-1)%4);
				$Slider.view();
			});

		$('#right_arrow').click(function()
			{
				$Slider.changeSlide((self.idScreenSelected+1)%4);
				$Slider.view();
			});

		$(document).keydown(function(e)
		{
			if (e.which == 37)
			{
				$Slider.changeSlide((self.idScreenSelected-1)%4);
				$Slider.view();	
			}
			if (e.which == 39)
			{
				$Slider.changeSlide((self.idScreenSelected+1)%4);
				$Slider.view();
			}
		})
	}

	function bindEvents()
	{
		// -------- Au suvol des flèches de navigation -------- //
		$('#left_arrow,#right_arrow').each(function(i,elt)
		{
			$(elt).hover(function()
			{
				$(elt).attr('src', `${src__red[i]}`);
			}, function()
			{
				$(elt).attr('src', `${src__black[i]}`);
			});
		});

		$(window).resize(function()
		{
			z_width = $('.box')[0].offsetWidth;
			$('.box').css('transform-origin', `center center -${(z_width/2)}px`);
		});
	}

	/*______________Objet Timer_________________*/

	function Timer(content){
		this.content = content;     // Le conteneur où écrire la date
		this.date_en_ce_moment;     // La date actuelle
		this.tab_date;				// Tableau contenant le temps restant à afficher
	}

	/*_____________FONCTION UTILITAIRE____________*/

	function calcul_temps_restant(temps){
		let jours = parseInt(temps / 86400) - 1;
		let reste_jours = temps % 86400;
		let heure = parseInt(reste_jours / 3600) - 4;
		let reste_heure = reste_jours % 3600;
		let mn = parseInt(reste_heure / 60);
		let sec = reste_heure % 60;
		return [jours, heure, mn, sec];
	}

	/*_____________METHODES___________*/

	Timer.prototype.mis_a_jour_temps = function(){
		this.date_en_ce_moment = parseInt(Date.now()*0.001);    
	}

	Timer.prototype.mis_a_jour_tab = function(){
		let dif = 1559347200 - this.date_en_ce_moment;
		this.tab_date = calcul_temps_restant(dif);
	}

	/*_____________LES AFFICHAGES____________*/

	Timer.prototype.view = function()
	{
		let self = this;
		$('.modif').each(function(index)
		{
		$(this).text(self.tab_date[index]);
		});
	}

	
	// ------ Premier affichage de l'IA ------ //
	let tab_txt = ["On a là un coriace ! Bravo... Je ne sais pas comment tu as fait mais ça doit rester SECRET !", "Bref, bienvenu sur le menu des mini-jeux !",
		"Tu peux naviguer à l'aide des boutons en haut de la page, des flèches affichées à l'écran, ou des flèches de ton clavier.",
		"Amuses-toi bien ! :)", "Note : Le dernier mini-jeu sortira le 31.05.2019 ! (:"];
	let Elia = new IA('#help_text');

	setTimeout(function()
	{
		Elia.view(tab_txt);
		$('.fixed').toggleClass('toggle');
		$('#global').css('filter', 'blur(5px)');
		$('#arrow').css('transform', 'rotate(0deg)');
	}, 	500);

	let $Slider = new Slider('li', '.box');
	$Slider.bindEvents();
	$('.box').css('transform-origin', `center center -${(z_width/2)}px`);
	bindEvents();

	let timer_1 = new Timer($('#timer'));
	var time = setInterval(function(){
		timer_1.mis_a_jour_temps();
		timer_1.mis_a_jour_tab();
		timer_1.view();
	},1000);


	
});