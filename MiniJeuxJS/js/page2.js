

$(function()
{
	function getRandomInt(min, max) {
	  return parseInt(Math.random() * ((max - min)) + min); //The maximum is exclusive and the minimum is inclusive
	}

	function Snake(taille){
		this.taille = taille;
		this.coordonne = [11,11];
		this.tabCoordonne = [[11,9],[11,10],[11,11]];
		this.direction = 'ArrowRight';
		this.longueur = 3;
		this.onoff = 0;
		this.vitesse = 150;
		this.score = 0;
		this.level = 0;
		this.point_level = [1,2,5];
		this.highscore = 0;
	};

	Snake.prototype.initialisation_pomme = function(){
		let self = this;
		self.coordonne_inutilisable = self.tabCoordonne.slice(self.tabCoordonne.length - self.longueur, self.tabCoordonne.length);
		do{
			self.coordonne_pomme = [getRandomInt(0,self.taille[0]-1),getRandomInt(0,self.taille[1]-1)];
		}while(self.coordonne_inutilisable.includes(self.coordonne_pomme));
		$('tr').eq(self.coordonne_pomme[0]).find('td').eq(self.coordonne_pomme[1]).toggleClass('yellow');
	}

	function modulo(x,y){
		if (x >= 0){
			return x%y;
		}else{
			return x+y;
		}
	}

	Snake.prototype.creationGraphe = function(){ 
		for (let i = 0; i < this.taille[0]; i++){
			let mainTr = document.createElement('tr');
			for (let j = 0; j < this.taille[1]; j++){
				let mainTd = document.createElement('td');
				mainTr.appendChild(mainTd);
			}
			document.getElementById('table').appendChild(mainTr);
		}	
	}

	Snake.prototype.changement = function(position){
		$('tr').eq(position[0]).find('td').eq(position[1]).toggleClass('white');
	}

	Snake.prototype.changeDirection = function(){
		let self = this;
		let touches = ['ArrowLeft','ArrowUp','ArrowRight','ArrowDown'];
		$(document).on('keydown',function(e){
			if (touches.includes(e.key)){
				if (self.direction != touches[(touches.indexOf(e.key)+2)%4]){
					self.direction = e.key;
				}
				e.preventDefault();
			}
		});
		$('#div_d_pad div').each(function(i, elt)
		{
			$(elt).click(function()
			{
				if (self.direction != touches[(i+2)%4])
				{
					self.direction = touches[i];
				}
			});
		});
	}

	Snake.prototype.mis_a_jour_position = function(){
		let self = this;
		let touches = ['ArrowLeft','ArrowUp','ArrowRight','ArrowDown'];
		let deplacement = [[0,-1],[-1,0],[0,1],[1,0]]
		let x = deplacement[touches.indexOf(this.direction)];
		self.coordonne = [(self.coordonne[0] + x[0]),((self.coordonne[1] + x[1]))]
		self.tabCoordonne.push(self.coordonne);
	}

	Snake.prototype.pomme = function(){
		let self = this;
		self.coordonne_inutilisable_string = []
		self.coordonne_inutilisable = self.tabCoordonne.slice(self.tabCoordonne.length - self.longueur, self.tabCoordonne.length);
		self.coordonne_inutilisable.forEach(function(elt,index){
			self.coordonne_inutilisable_string.push(elt.toString());
		});
		if ((self.coordonne[0] == self.coordonne_pomme[0]) && (self.coordonne[1] == self.coordonne_pomme[1])){
			self.longueur++;
			self.score+=self.point_level[self.level];
			$('tr').eq(self.coordonne_pomme[0]).find('td').eq(self.coordonne_pomme[1]).toggleClass('yellow');
			do{
				self.coordonne_pomme = [getRandomInt(0,self.taille[0]-1),getRandomInt(0,self.taille[1]-1)];
				self.coordonne_pomme_string = self.coordonne_pomme.toString();
			}while(self.coordonne_inutilisable_string.includes(self.coordonne_pomme_string));
			$('tr').eq(self.coordonne_pomme[0]).find('td').eq(self.coordonne_pomme[1]).toggleClass('yellow');
		}
	}

	Snake.prototype.controlleur = function(){
		let self = this;
		let tab = self.coordonne_inutilisable_string.slice(0,self.coordonne_inutilisable_string.length-1);
		let x = self.coordonne.toString();
		if (self.coordonne[0] == self.taille[0] || self.coordonne[0] == -1 || self.coordonne[1] == self.taille[1] || self.coordonne[1] == -1 || tab.includes(x)){
			alert('Game Over');
			self.onoff = 0;
			self.reset();
			self.mouvement();
			$('#div_niveau').toggleClass('hide_niv');
		}
	}

	Snake.prototype.reset = function(){
		let self = this;
		this.coordonne = [11,11];
		this.tabCoordonne = [[11,9],[11,10],[11,11]];
		this.direction = 'ArrowRight';
		this.longueur = 3;
		this.score = 0;
	}

	Snake.prototype.start = function(){
		let self = this;
		self.changeDirection();
		self.mis_a_jour_niveau();
		$(document).on('keydown',function(e){
			if (e.key == 'Enter'){
				self.onoff = (self.onoff+1)%2;
				self.reset();
				self.mouvement();
				$('#div_niveau').toggleClass('hide_niv');
			}
		});
		$('table').click(function(e){
			self.onoff = (self.onoff+1)%2;
			self.reset();
			self.mouvement();
			$('#div_niveau').toggleClass('hide_niv');
		});
	}

	Snake.prototype.mis_a_jour_niveau = function(){
		let self = this;
		let niveau = ['Normal','Rapide','Eclair'];
		let vitesse = [150,100,50]
		$("#niveau").on('input',function(){
			self.level = niveau.indexOf($('#niveau').val());
			self.onoff = 0;
			self.vitesse = vitesse[self.level];
			self.reset();
			self.mouvement();
		})
	}

	Snake.prototype.mis_a_jour_score = function(){
		let self = this;
		if (self.score > self.highscore){
			self.highscore = self.score;
			$('#div_score div').eq(1).text(self.highscore);
		}
		$('#div_score div').eq(0).text(self.score);
	}

	Snake.prototype.mouvement = function(){
		let self = this;
		if (self.onoff == 1){
			self.initialisation_pomme();
			self.changement(self.coordonne);
			self.changement(self.tabCoordonne[self.tabCoordonne.length - 2]);
			self.changement(self.tabCoordonne[self.tabCoordonne.length - 3]);
			self.pomme();
			let repere = self.longueur;
			self.mouv = setInterval(function(){
				if (self.longueur != repere){
					self.changement(self.tabCoordonne[self.tabCoordonne.length - self.longueur]);
					repere = self.longueur;
				}
				self.changement(self.coordonne);
				for (let i = 2; i <= self.longueur; i++){
					self.changement(self.tabCoordonne[self.tabCoordonne.length - i]);
				}
				self.mis_a_jour_position();
				self.changement(self.coordonne);
				for (let i = 2; i <= self.longueur; i++){
					self.changement(self.tabCoordonne[self.tabCoordonne.length - i]);
				}
				self.pomme();
				self.controlleur();
				self.mis_a_jour_score();
			},self.vitesse);
		}else{
			$('td').removeClass('white');
			$('td').removeClass('yellow');
			clearInterval(self.mouv);
		}
	};

	/*PROGRAMME PRINCIPAL*/
	// Premier affichage de l'IA ------ //
	let tab_txt = [ "Bienvenue sur le jeu du Snake !",
		"Règles du jeu : pour marquer des points, 'manges' une case jaune. C'est simple non ? :)",
		"Plus le niveau est élévé, plus tu gagnes de points !",
		"Attention, tu perds en cas de contact avec les bords ou avec le corps du Snake.",
		"Pour commencer et pour arrêter la partie, appuyes sur le bouton 'Entrée' ou clique sur la zone de jeu.",
		"Good game !"];
	let Elia = new IA('#help_text');
	setTimeout(function()
	{
		Elia.view(tab_txt);
		$('.fixed').toggleClass('toggle');
		$('#global').css('filter', 'blur(5px)');
		$('#arrow').css('transform', 'rotate(0deg)');
	}, 	500);

	let snake = new Snake([20,20]);
	snake.creationGraphe();
	snake.start();
});