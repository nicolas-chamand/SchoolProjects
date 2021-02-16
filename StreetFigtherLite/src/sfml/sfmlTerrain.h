#ifndef _SFMLTERRAIN_H
#define _SFMLTERRAIN_H

#include "SFML/Graphics.hpp"
#include <string>

using namespace std;

class sfmlTerrain
{
	private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::IntRect rectSourceSprite;
	sf::Clock clock;
	int dimX, dimY;

	/**
    * @brief Charge les dimensions du terrain depuis le fichier dimTerrain.txt
    * @details Postcondition: les données dimX et dimY sont intialisées.
    */
	void getDimensionsTerrain(const string &nomTerrain);
	public:
	
	/**
    * @brief Charge la texture depuis le disque dur et initialise la camera.
    * @details Precondition : idTerrain doit correspondre a l'identifiant d'un terrain valide.
    * Postcondition: le sfmlTerrain est prêt pour l'affichage.
    */
	void charger(int idTerrain);
	
	/**
    * @brief Procédure d'affichage et animation du terrain.
    */
	void afficher(sf::RenderTarget &render);

	/**
    * @brief Fonction pour deplacer la camera.
    * param float deplacement : nombre de pixels max à scroll (positif pour un scroll droite, negatif pour un scroll gauche)
    * @details Retourne le nombre de pixels de difference entre l'ancienne et la nouvelle position de la camera.
    */
	float cameraScroll(float deplacement);
};
#endif