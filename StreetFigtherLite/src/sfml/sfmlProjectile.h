#ifndef _SFMLPROJECTILE_H
#define _SFMLPROJECTILE_H

#include "SFML/Graphics.hpp"
#include "Projectile.h"

class sfmlProjectile
{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::IntRect rectSourceSprite;
		sf::Clock clock;
		Projectile *projectile;
	public:
		/**
	    * @brief Procédure qui dessine dans le fenêtre la sprite du projectile.
	    * details Affiche le projectile dans la fenêtre en fonction de sa 
	    * direction
	    * @param sf::RenderTarget &render : La fenêtre de rendu SFML
	    */
		void afficher(sf::RenderTarget &render);

		/**
	    * @brief Procédure qui initialise l'affichage du projectile et l'associe
	    * au Projectile. 
	    * @details La sprites est initialisées.
	    */
		void init(Projectile *prjctle);
};
#endif