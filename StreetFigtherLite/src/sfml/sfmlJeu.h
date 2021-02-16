#ifndef _SFMLJEU_H
#define _SFMLJEU_H

#include "SFML/Graphics.hpp"
#include "Jeu.h"
#include "sfmlTerrain.h"
#include "Ryu.h"
#include "Ken.h"
#include "sfmlProjectile.h"
#include "sfmlMenu.h"

class sfmlJeu
{
	private:
	Jeu jeu;
	Ryu sfmlJoueur1;
	Ken sfmlJoueur2;
	sfmlTerrain terrain;
	sfmlProjectile sfmlPJ1, sfmlPJ2;
	sfmlMenu menu;
	sf::RenderWindow renderWindow;
	sf::Font font;

	/**
    * @brief Procédure d'affichage de texte dans le render passé en paramètre.
    */
	void ecrire(sf::RenderTarget &render, const string &texte, unsigned int fontSize, unsigned int posX, unsigned int posY) const;

	/**
    * @brief Procédure d'affichage d'une barre de vie dans le render passé en paramètre
    * @details Sous-fonction de la procédure drawHUD.
    */
	void drawBarreDeVie(sf::RenderTarget &render, unsigned int posX, unsigned int posY, bool miroir, const Personnage &joueur) const;

	/**
    * @brief Procédure qui affiche le HUD dans le render passé en paramètre.
    * @details Sous-fonction de la procédure sfmlAfficher.
    */
	void drawHUD(sf::RenderTarget &render) const;

	/**
    * @brief Procédure de lecture des entrées clavier pour le joueur 1 et joue le joueur 2 automatiquement.
    */
	void ecouteClavierJoueur1ComportementAutoJoueur2();

	/**
    * @brief Procédure de lecture des entrées clavier pour le mode 2 joueurs.
    */
	void ecouteClavier2Joueurs();

	/**
    * @brief Procédure qui gère la camera du point de vue du Personnage passé comme premier paramètre.
    * @details Sous-fonction de la procédure updateCamera.
    */
	void updateCameraJoueur(const Personnage & joueur1, Personnage & joueur2);

	/**
    * @brief Procédure qui gère les deplacements de la camera.
    */
	void updateCamera();
	/**
    * @brief Procédure d'affichage.
    * @details Affiche le terrain, les personnages, les projectiles et le HUD.
    */
	void sfmlAfficher();

	public:
	sfmlJeu();
	~sfmlJeu();

	/**
    * @brief Procédure de boucle d'affichage du menu de selection de terrain.
    * @details Postcondition : l'utilisateur a choisi terrain.
    */	
	void sfmlBoucleStage();

	/**
    * @brief Procédure de boucle d'affichage de la page de titre.
    * @details Postcondition : la fenêtre d'affichage est crée.
    */
	void sfmlBoucleStart();

	/**
    * @brief Procédure de boucle d'affichage du menu de selection du mode de jeu.
    * @details Postcondition : l'utilisateur a choisi un mode de jeu.
    */
	void sfmlBoucleMode();

	/**
    * @brief Procédure qui initialise le jeu.
    * @details Postcondition : les personnages et la fenêtre sont initialisés pour le mode graphique.
    */
	void sfmlInitJeu();

	/**
    * @brief Procédure de boucle d'affichage de la partie.
    * @details Postcondition : permet l'affichage graphique de la partie et l'écoute d'évenements clavier.
    */
	void sfmlBoucleJeu();
};

#endif