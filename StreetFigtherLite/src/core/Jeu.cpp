#include "Jeu.h"
#include <assert.h>
#include <iostream>
#include <cmath>
#include <cstdlib>

Jeu::Jeu()
{
	joueur1.regardeDroite = true;
	joueur2.regardeDroite = false;
	mode = true;
	winJ1 = 0;
	winJ2 = 0;
	debut = true;
	fin = false;
	delayDebut = 0;
	delayFin = 0;
}

void Jeu::initEnvironnement(int dim_X, int dim_Y, int hauteur_Sol, int epaisseur_bordure, float gravite, float saut, float vitesse, float delai)
{
	env.DIMX = dim_X;
	env.DIMY = dim_Y;
	env.hauteurSol = hauteur_Sol;
	env.epaisseurBordure = epaisseur_bordure;
	env.v_gravitation = gravite;
	env.v_saut = saut;
	env.deplacement = vitesse;
	env.maxDelay = delai;
}

void Jeu::collisionProjectile()
{
	if(joueur1.projectile.vivant && (joueur1.projectile.position.x <= 0 || joueur1.projectile.position.x >= env.DIMX))
		joueur1.projectile.vivant = false;
	if(joueur2.projectile.vivant && (joueur2.projectile.position.x <= 0 || joueur2.projectile.position.x >= env.DIMX))
		joueur2.projectile.vivant = false;
	if(joueur1.projectile.vivant && joueur2.projectile.vivant)
	{
		if(abs(joueur1.projectile.position.x - joueur2.projectile.position.x) <= joueur1.projectile.taille)
		{
			joueur1.projectile.vivant = false;
			joueur2.projectile.vivant = false;
		}
	}
	else if(joueur1.projectile.vivant)
	{
		if(abs(joueur1.projectile.position.x - joueur2.getPosition().x) <= joueur1.projectile.taille/2 + joueur1.tailleX)
			if((abs(joueur1.projectile.position.y - (joueur2.getPosition().y-joueur2.tailleY/2))) <= joueur2.tailleY/2 -joueur2.tailleY/10)
			{
				joueur1.projectile.vivant = false;
				if(!joueur2.parade)
				{
					joueur2.encaisseDegats(10);
					joueur2.currentAction = 93;
				}
			}	
	}
	else if(joueur2.projectile.vivant)
	{
		if(abs(joueur2.projectile.position.x - joueur1.getPosition().x) <= joueur2.projectile.taille/2 + joueur2.tailleX)
			if((abs(joueur2.projectile.position.y - (joueur1.getPosition().y-joueur1.tailleY/2))) <= joueur1.tailleY/2 -joueur1.tailleY/10)
			{
				joueur2.projectile.vivant = false;
				if(!joueur1.parade)
				{
					joueur1.encaisseDegats(10);
					joueur1.currentAction = 93;
				}
			}	
	}
}

bool Jeu::collision()
{
	// en cas de proximite sur l'axe horizontal
	// et en cas de proximite sur l'axe vertical
	// nb : la taille d'un psng en saut n'est pas aussi importante que debout
	// c'est pourquoi on autorise une marge
	if(abs(joueur1.getPosition().x-joueur2.getPosition().x) <= joueur1.tailleX+joueur2.tailleX)
		if(abs(joueur1.getPosition().y-joueur2.getPosition().y) <= joueur1.tailleY/2)
			return true;
	return false;
}

void Jeu::collisionPersonnage(Personnage & joueur1, Personnage & joueur2)
{
	float distance = joueur1.tailleX+joueur2.tailleX - abs(joueur1.getPosition().x-joueur2.getPosition().x);
	// definit la direction à corriger
	if(joueur1.regardeDroite)
	{
		if(joueur1.getVel().x == 0 && joueur2.getVel().x == 0)
		{
			joueur1.setPosition(make_vec2(joueur1.getPosition().x - distance/6,joueur1.getPosition().y));
			joueur2.setPosition(make_vec2(joueur2.getPosition().x + distance/6,joueur2.getPosition().y));
		}
		else if(joueur1.getVel().x > 0  && joueur2.getVel().x >= 0)
		{
			if(joueur2.getPosition().x == env.DIMX-3-env.epaisseurBordure)
			{
				joueur1.setPosition(make_vec2(joueur1.getPosition().x - distance/6,joueur1.getPosition().y));
				joueur1.setVel(make_vec2(0,joueur1.getVel().y));
			}
			else
			{
				joueur2.setPosition(make_vec2(joueur2.getPosition().x + env.deplacement/2,joueur2.getPosition().y));
				joueur1.setVel(make_vec2(joueur1.getVel().x/2, joueur1.getVel().y));
				joueur1.setPosition(make_vec2(joueur1.getPosition().x - distance/6,joueur1.getPosition().y));
			}
		}
		else if(joueur2.getVel().x < 0 && joueur1.getVel().x <= 0)
		{

			if(joueur1.getPosition().x == env.epaisseurBordure+2)
			{	
				joueur2.setPosition(make_vec2(joueur2.getPosition().x + distance/6,joueur2.getPosition().y));
				joueur2.setVel(make_vec2(0,joueur2.getVel().y));
			}
			else
			{
				joueur1.setPosition(make_vec2(joueur1.getPosition().x - env.deplacement/2,joueur1.getPosition().y));
				joueur2.setVel(make_vec2(joueur2.getVel().x/2, joueur2.getVel().y));
				joueur2.setPosition(make_vec2(joueur2.getPosition().x + distance/6,joueur2.getPosition().y));
			}
		}
		else if(joueur1.getVel().x > 0 && joueur2.getVel().x < 0)
		{
			joueur1.setPosition(make_vec2(joueur1.getPosition().x - distance/6,joueur1.getPosition().y));
			joueur2.setPosition(make_vec2(joueur2.getPosition().x + distance/6,joueur2.getPosition().y));
			joueur1.setVel(make_vec2(0,joueur1.getVel().y));
			joueur2.setVel(make_vec2(0,joueur2.getVel().y));
		}
	}
}

void Jeu:: updateProjectiles()
{
	joueur1.projectile.miseAJourPosition(env.deplacement * 0.8);
	joueur2.projectile.miseAJourPosition(env.deplacement * 0.8);
	collisionProjectile();
}

void Jeu::update()
{
	// Si un joueur à gagner le combat
	if(joueur1.vie == 0)
	{
		if(joueur1.currentAction == 0 || joueur1.currentAction == 10)
			joueur1.currentAction = 99;
		if(joueur2.currentAction == 0 || joueur2.currentAction == 10)
			joueur2.currentAction = 100;
		if(fin == false && delayFin == 0)
		{
			winJ2++;
			fin = true;
		}
	}
	if(joueur2.vie == 0)
	{
		if(joueur1.currentAction == 0 || joueur1.currentAction == 10)
			joueur1.currentAction = 100;
		if(joueur2.currentAction == 0 || joueur2.currentAction == 10)
			joueur2.currentAction = 99;
		if(fin == false && delayFin == 0)
		{
			winJ1++;
			fin = true;
		}
	}

	// MAJ de l'orientations des personnages
	if(joueur1.getPosition().x < joueur2.getPosition().x)
		joueur1.regardeDroite = true;
	else if(joueur1.getPosition().x > joueur2.getPosition().x)
		joueur1.regardeDroite = false;
	joueur2.regardeDroite = !joueur1.regardeDroite;
	 // maj du booleen de deplacement pour l'affichage
  	joueur1.deplacement = (joueur1.getVel().x != 0);
  	joueur2.deplacement = (joueur2.getVel().x != 0);

	// MAJ + collisions des projectiles
	updateProjectiles();

	// prise en compte des collisions
	if(collision())
	{
		collisionPersonnage(joueur1, joueur2);
		collisionPersonnage(joueur2, joueur1);
	}

	// MAJ de la position des personnages
	joueur1.update(env.v_gravitation, env.hauteurSol, env.DIMX, env.epaisseurBordure);
	joueur2.update(env.v_gravitation, env.hauteurSol, env.DIMX, env.epaisseurBordure);


	// Vérifier le nombre de rounds et applique un delai avant de lancer le 
	// nouveau
	if(fin && winJ1 < 2 && winJ2 < 2)
	{
		delayFin = clock();
		fin = false;
	}
	if(!fin && delayFin != 0 && (float(clock()-delayFin)/CLOCKS_PER_SEC) > env.maxDelay)
	{
		restartRound();
		delayFin = 0;
		debut = true;
		delayDebut = clock();
	}

	if(delayDebut != 0 && (float(clock()-delayDebut)/CLOCKS_PER_SEC) > env.maxDelay)
	{
		debut = false;
		delayDebut = 0;
	}

}

void Jeu::restartRound()
{
	//Initialisation des personnages et leurs textures
	joueur1.setPosition(make_vec2(env.DIMX/4,env.hauteurSol));
	joueur2.setPosition(make_vec2(3*env.DIMX/4,env.hauteurSol));
	
	//Reset de la vie des personnafe
	joueur1.vie = 100;
	joueur2.vie = 100;

	joueur1.setVel(make_vec2(0.0,0.0));
	joueur2.setVel(make_vec2(0.0,0.0));

	joueur1.currentAction = 0;
	joueur2.currentAction = 0;

	joueur1.regardeDroite = true;
	joueur2.regardeDroite = false;	
}

void Jeu::actionClavier(const char action)
{
	// DEPLACEMENTS

		// Joueur 1
		if(action == 'w') // DEPLACEMENT GAUCHE
			joueur1.deplacementGauche(env.deplacement);
		if(action == 'd') // DEPLACEMENT DROITE
			joueur1.deplacementDroite(env.deplacement);
		if(action == ' ') // SAUT
			joueur1.sauter(env.v_saut);
		if(action == 's') // ACCROUPI
			joueur1.accroupir();
		if(action == 'x') // ACCROUPI PERSISTANT
			joueur1.accroupirPersistant();

		// Joueur 2
		if(action == 'k') // DEPLACEMENT GAUCHE
			joueur2.deplacementGauche(env.deplacement);
		if(action == 'l') // DEPLACEMENT DROITE
			joueur2.deplacementDroite(env.deplacement);
		if(action == 'm') // SAUT
			joueur2.sauter(env.v_saut);
		if(action == 'n') // ACCROUPI
			joueur2.accroupir();
		if(action == 'b') // ACCROUPI PERSISTANT
			joueur2.accroupirPersistant();

	// DEFENSE

		// Joueur 1
		if(action == 't') // PARADE
			joueur1.blocking();
		if(action == 'a') // PARADE PERSISTANTE
			joueur1.blockingPersistant();

		// Joueur 2
		if(action == 'u') // PARADE
			joueur2.blocking();
		if(action == 'y') // PARADE PERSISTANTE
			joueur2.blockingPersistant();
	
	// ATTAQUE

		// Joueur 1
		if(action == 'e') // COUP DE POING
			joueur1.coupPoing(joueur2);
		if(action == 'r') // COUP DE PIED
			joueur1.coupPied(joueur2);
		if(action == 'z') // HADOUKEN
			joueur1.hadoken();

		// Joueur 2 
		if(action == 'p') // COUP DE POING
			joueur2.coupPoing(joueur1);
		if(action == 'o') // COUP DE PIED
			joueur2.coupPied(joueur1);
		if(action == 'h') // HADOKEN
			joueur2.hadoken();
}

void Jeu::comportementAutoJoueur2()
{
	float distanceEntrePersonnage;
	distanceEntrePersonnage = abs(joueur1.getPosition().x - joueur2.getPosition().x) - joueur2.tailleX*2;
	if(distanceEntrePersonnage > joueur2.taillePoing/2)
	{
		int random = rand()%101;
		if(random >= 30)
		{
			if(joueur2.regardeDroite)
				joueur2.deplacementDroite(env.deplacement);
			else
				joueur2.deplacementGauche(env.deplacement);
			if(rand()%101 > 99)
				joueur2.sauter(env.v_saut);
		}
		else if(random >= 27)
			joueur2.hadoken();
	}
	else
	{
		int random = rand()%101;
		if(random < 3)
			joueur2.coupPoing(joueur1);
		else if(random < 6)
			joueur2.coupPied(joueur1);
	}
}

void Jeu::restartGame()
{
	restartRound();

	//reset du nombre de victoire
	winJ1 = 0;
	winJ2 = 0;

	//reset des délais
	debut = true;
	fin = false;
	delayDebut = 0;
	delayFin = 0;
}

void Jeu::testRegression()
{
	int DIMX = 1100;
	int DIMY = 550;
	int hauteurSol = DIMY-40;
	int bordure = 150;

	float v_gravitation = 1.0f; // constante de gravite
	float vitesse = 10.0f;
	float v_saut = -22.0f;
	float delai = 5.0;

	//Initialisation de l'environnement
	initEnvironnement(DIMX,DIMY,hauteurSol,bordure,v_gravitation,v_saut,vitesse, delai);


	for(int i = 0; i < 100000; i++)
	{
		assert(joueur1.vie >= 0);
		assert(joueur2.vie >= 0);
		assert(joueur1.getPosition().x >= 0);
		assert(joueur1.getPosition().y >= 0);
		assert(joueur1.getPosition().x <= DIMX);
		assert(joueur1.getPosition().y <= hauteurSol);
		int action = rand()%256;
		actionClavier(action);
		update();
	}
	std::cout << "Tous les tests du module Jeu ont réussit" << std::endl;
}