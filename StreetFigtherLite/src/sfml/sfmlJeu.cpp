#include "sfmlJeu.h"
#include <string>
#include <iostream>
#include <stdlib.h>

sfmlJeu::sfmlJeu()
{
	//chargement de la police d'ecriture depuis un fichier sur le disque
	if (!font.loadFromFile("data/font.ttf"))
		if(!font.loadFromFile("../data/font.ttf"))
	    	std::cout << "Erreur de chargement de la police d'ecriture" << std::endl;
}

sfmlJeu::~sfmlJeu()
{}

void sfmlJeu::ecrire(sf::RenderTarget &render, const string &texte, unsigned int fontSize, unsigned int posX, unsigned int posY) const
{
	sf::Text txt;
	txt.setFont(font);
	txt.setCharacterSize(fontSize);
	txt.setStyle(sf::Text::Bold);
	txt.setString(texte.c_str());
	// ombre / contour bleu
	txt.setFillColor(sf::Color(0,26,163));
	txt.setPosition(posX+2,posY+2);
	render.draw(txt);
	// texte
	txt.setFillColor(sf::Color(247,193,40));
	txt.setPosition(posX,posY);
	render.draw(txt);
}

void sfmlJeu::drawBarreDeVie(sf::RenderTarget &render, unsigned int posX, unsigned int posY, bool miroir, const Personnage &joueur) const
{
	// fond de couleur rouge
	sf::RectangleShape fond(sf::Vector2f(400, 25));
	fond.setFillColor(sf::Color(225, 20, 0));
	// contour blanc de 2 pixels d'épaisseur
	fond.setOutlineThickness(2);
	fond.setOutlineColor(sf::Color(255, 255, 255));
	// définit la position du fond
	fond.setPosition(posX,posY);

	// jauge de vie de couleur jaune
	sf::RectangleShape vie(sf::Vector2f(joueur.vie * 4, 25));
	vie.setFillColor(sf::Color(250, 255, 0));
	if(miroir)
	{
		// symetrie d'axe vertical pour que la vie decroit dans le bon sens
		vie.setScale(-1.0f * vie.getScale().x, vie.getScale().y);
		// definit la position de la jauge de vie
		vie.setPosition(posX+400,posY);
	}
	else
		vie.setPosition(posX,posY);
	render.draw(fond);
	render.draw(vie);
}

void sfmlJeu::drawHUD(sf::RenderTarget &render) const
{
	// Ryu (barre de vie + nom)
	drawBarreDeVie(render,25,35,true,jeu.joueur1);
	ecrire(render,"RYU",40,24,55);

	// Ken (barre de vie + nom)
	drawBarreDeVie(render,475,35,false,jeu.joueur2);
	ecrire(render,"KEN",40,jeu.env.DIMX-94,55);

	if(jeu.joueur2.currentAction == 100)
		ecrire(render,"KEN WINS",55,jeu.env.DIMX/3,(jeu.env.DIMY/2)-100);
	else if(jeu.joueur1.currentAction == 100)
		ecrire(render,"RYU WINS",55,jeu.env.DIMX/3,(jeu.env.DIMY/2)-100);

	if(jeu.delayDebut != 0 && (float(clock()-jeu.delayDebut)/CLOCKS_PER_SEC) < 3.0f)
		ecrire(render,"ROUND "+std::to_string(jeu.winJ1+jeu.winJ2+1),55,(jeu.env.DIMX/2)-100,(jeu.env.DIMY/2)-100);
	else if(jeu.delayDebut != 0 && (float(clock()-jeu.delayDebut)/CLOCKS_PER_SEC) <= 4.0f)
		ecrire(render,"FIGHT !",55,(jeu.env.DIMX/2)-100,(jeu.env.DIMY/2)-100);
}

void sfmlJeu::sfmlBoucleStage()
{
	sf::Event event;
	sf::Clock clock;
	sf::Clock Keyboardclock;

	menu.initStageSelect();

	while (renderWindow.isOpen()) // tant que la fenêtre est ouverte
	{
		while (renderWindow.pollEvent(event))
		{
		  if (event.type == sf::Event::Event::Closed) // Si on cliquer sur fermer la fenêtre
		  {
		  	renderWindow.close();
		  	exit(EXIT_SUCCESS);
		  }
		    
		}
		if(clock.getElapsedTime().asSeconds() > (0.017f)) // Fixe l'affichage à 60 ips
		{
			// Empêche la répétition trop rapide des touches
			if(Keyboardclock.getElapsedTime().asSeconds() > (0.3f)) 
			{
				// Actions
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					menu.deplacementHaut();
					Keyboardclock.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					menu.deplacementBas();
					Keyboardclock.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					menu.deplacementGauche();
					Keyboardclock.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					menu.deplacementDroite();
					Keyboardclock.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					if(menu.getIdTerrain() != 8)
					{
						break;
					}
				}
			}
			
		  	// Efface le dernier affichage
			renderWindow.clear();

			menu.update(renderWindow);

			// Affichage tous les changement (draw) effectués
			renderWindow.display();
			clock.restart();
		}
	}
}

void sfmlJeu::sfmlBoucleStart()
{
	sf::Event event;
	sf::Clock clock;
	sf::Clock Keyboardclock;

	//Initialisation de l'environnement
	//(DIMX, DIMY, hauteurSol, epaisseurBordure, gravite, saut, vitesse, delai);
	jeu.initEnvironnement(900, 550, 510, 150, 1.0, -22.0, 10.0, 4.0);
	
	//Initalisation de la fenêtre
	renderWindow.create(sf::VideoMode(jeu.env.DIMX, jeu.env.DIMY), "Street Fighter BETA");

	while (renderWindow.isOpen()) // tant que la fenêtre est ouverte
	{
		while (renderWindow.pollEvent(event))
		{
		  if (event.type == sf::Event::Event::Closed) // Si on cliquer sur fermer la fenêtre
		  {
		  	renderWindow.close();
		  	exit(EXIT_SUCCESS);
		  }
		}
		if(clock.getElapsedTime().asSeconds() > (0.017f)) // Fixe l'affichage à 60 ips
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				break;

		  	// Efface le dernier affichage
			renderWindow.clear();

			menu.animationStart();

			menu.dessineHome(renderWindow);

			// Affichage tous les changement (draw) effectués
			renderWindow.display();
			clock.restart();
		}
	}
}

void sfmlJeu::sfmlBoucleMode()
{
	sf::Event event;
	sf::Clock clock;
	sf::Clock Keyboardclock;

	menu.initHomeSelect();

	while (renderWindow.isOpen()) // tant que la fenêtre est ouverte
	{
		while (renderWindow.pollEvent(event))
		{
		  if (event.type == sf::Event::Event::Closed) // Si on cliquer sur fermer la fenêtre
		  {
		  	renderWindow.close();
		  	exit(EXIT_SUCCESS);
		  }
		    
		}
		if(clock.getElapsedTime().asSeconds() > (0.017f)) // Fixe l'affichage à 60 ips
		{
			// Empêche la répétition trop rapide des touches
			if(Keyboardclock.getElapsedTime().asSeconds() > (0.2f)) 
			{
				// Actions
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					jeu.mode = true;
					menu.animationSuperBattle();
					Keyboardclock.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					jeu.mode = false;
					menu.animationVersusBattle();
					Keyboardclock.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					break;
				}
			}
			
		  	// Efface le dernier affichage
			renderWindow.clear();

			menu.animationStart();
			menu.dessineHome(renderWindow);
			menu.dessineMode(renderWindow);

			// Affichage tous les changement (draw) effectués
			renderWindow.display();
			clock.restart();
		}
	}
}

void sfmlJeu::sfmlInitJeu()
{
	//Initialisation du terrain
	terrain.charger(menu.getIdTerrain());

	//Remise à zéro des valeurs de jeu 
	jeu.restartGame();

	//Initialisation des personnages et leurs textures
	jeu.joueur1.init(47, 230, 100, 118, make_vec2(250,jeu.env.hauteurSol));
	sfmlJoueur1.init(&jeu.joueur1);
	jeu.joueur2.init(47, 230, 100, 118, make_vec2(650,jeu.env.hauteurSol));
	sfmlJoueur2.init(&jeu.joueur2);

	//Initialisation des projectiles et leurs textures
	jeu.joueur1.projectile.init(34);
	sfmlPJ1.init(&jeu.joueur1.projectile);
	jeu.joueur2.projectile.init(34);
	sfmlPJ2.init(&jeu.joueur2.projectile);

	//Initilise la clock de delai pour affichage du round
	jeu.delayDebut = std::clock();

}

void sfmlJeu::updateCameraJoueur(const Personnage & joueur1, Personnage & joueur2)
{
	float offset = 0;
	// Si le joueur1 est en bordure d'écran gauche
    if(joueur1.getPosition().x == jeu.env.epaisseurBordure+2 && 
    	joueur2.getPosition().x != jeu.env.DIMX-3-jeu.env.epaisseurBordure)
    {
    	if(joueur1.getVel().x < 0)
    		offset = terrain.cameraScroll(10.0);
    	else if(joueur2.getVel().x < 0 && jeu.collision())
    		terrain.cameraScroll(5.0);	
    }
    // Si le joueur 1 est en bordure d'écran droit
	else if(joueur1.getPosition().x == jeu.env.DIMX-3-jeu.env.epaisseurBordure &&
		joueur2.getPosition().x != jeu.env.epaisseurBordure+2)
	{
		if(joueur1.getVel().x > 0)
			offset = terrain.cameraScroll(-10.0);
		else if(joueur2.getVel().x > 0 && jeu.collision())
    		terrain.cameraScroll(-5.0);	
	}
	float posX = joueur2.getPosition().x;
	float posY = joueur2.getPosition().y;
	// conserve la position relative du joueur 2
	joueur2.setPosition(make_vec2(posX+offset, posY));
	joueur2.projectile.position.x+=offset;
}

void sfmlJeu::updateCamera()
{
	updateCameraJoueur(jeu.joueur1, jeu.joueur2);
	updateCameraJoueur(jeu.joueur2, jeu.joueur1);
}

void sfmlJeu::ecouteClavier2Joueurs()
{
	// (ici l'ordre de lecture des entrees clavier est importante :
	// 	une parade doit etre lue et activée avant qu'un coup ne soit porté,
	//  de meme pour pouvoir lancer un coup de pied accroupi, 
	//	le mouvement doit etre lu avant le coup)

	// DEPLACEMENTS

	// Joueur 1
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	    jeu.actionClavier('w');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		jeu.actionClavier('d');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
  		jeu.actionClavier(' ');
  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  		jeu.actionClavier('s');

  	// Joueur 2 											
 	if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	    jeu.actionClavier('k');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		jeu.actionClavier('l');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
  		jeu.actionClavier('m');
  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
  		jeu.actionClavier('n');

  	// DEFENSE 

	// Joueur 1
  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) // PARADE JOUEUR 1
  		jeu.actionClavier('t');
  	// Joueur 2
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) // PARADE JOUEUR 2
		jeu.actionClavier('u');

  	// ATTAQUE

  	// Joueur 1
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		jeu.actionClavier('e');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		jeu.actionClavier('r');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // HADOKEN
		jeu.actionClavier('z');
	// Joueur 2
  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))			 
		jeu.actionClavier('p');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		jeu.actionClavier('o');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) // HADOKEN
		jeu.actionClavier('h');
}

void sfmlJeu::ecouteClavierJoueur1ComportementAutoJoueur2()
{
	// DEPLACEMENTS
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	    jeu.actionClavier('w');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		jeu.actionClavier('d');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
  		jeu.actionClavier(' ');
  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  		jeu.actionClavier('s');
  	// DEFENSE 
  	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) // PARADE JOUEUR 1
  		jeu.actionClavier('t');
  	// ATTAQUE
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		jeu.actionClavier('e');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		jeu.actionClavier('r');
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // HADOKEN
		jeu.actionClavier('z');
	// Comportement automatique joueur 2
	jeu.comportementAutoJoueur2();
}

void sfmlJeu::sfmlAfficher()
{
	// Efface la fenêtre
	renderWindow.clear();
	// Dessine le terrain dans le render
	terrain.afficher(renderWindow);
	// Dessine les projectiles dans le render
	if(jeu.joueur1.projectile.vivant)
		sfmlPJ1.afficher(renderWindow);
	if(jeu.joueur2.projectile.vivant)
		sfmlPJ2.afficher(renderWindow);
	// Dessine les personnages dans le render
	sfmlJoueur2.afficher(renderWindow, jeu.env.hauteurSol);
	sfmlJoueur1.afficher(renderWindow, jeu.env.hauteurSol);
	// Dessine le HUD
	drawHUD(renderWindow);
	// Nouvel affichage
	renderWindow.display();
}

void sfmlJeu::sfmlBoucleJeu()
{
	sf::Event event;
	sf::Clock clock;
	
	// tant que la fenêtre est ouverte
	while(renderWindow.isOpen())
	{
		while(renderWindow.pollEvent(event))
		{
			// Si on clique sur fermer la fenêtre
			if(event.type == sf::Event::Event::Closed)
		    	renderWindow.close();
		}
		// Fixe l'affichage à 60 ips
		if(clock.getElapsedTime().asSeconds() > (0.017f))
		{
			// Si le round à commencer
			if(!jeu.debut)
			{
				if(jeu.mode)
					ecouteClavierJoueur1ComportementAutoJoueur2();
				else
					ecouteClavier2Joueurs();
			}
			//MAJ CAMERA
			updateCamera();
			//MAJ JEU
			jeu.update();
			// AFFICHAGE
			sfmlAfficher();

			clock.restart();
		}
	}
}
