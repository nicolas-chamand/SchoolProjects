#ifndef SFML_MENU_H
#define SFML_MENU_H

#include "SFML/Graphics.hpp"

class sfmlMenu
{
	private:
		sf::Texture texture;
		sf::Texture textureSelect;
		sf::Sprite spriteHome;
		sf::Sprite spriteMode;
		sf::Sprite spriteBackground;
		sf::Sprite spriteFlag;
		sf::IntRect rectSourceSprite;
		sf::RectangleShape backgroundColor;
		sf::Clock clock;
		int idTerrain;

		/**
	    * @brief Procédure qui charge le drapeau correspondant au idTerrain.
	    * @details Charge et positione le drapeau correspondaut au terrain 
	    * d'idTerrain.
	    */
		void updateFlag();

		/**
	    * @brief Procédure qui permet l'animation de séléction d'un drapeau.
	    * @details Modifie l'opacité de la spriteFlag pour permetre 
	    * l'animation de séléction d'un drapeau.
	    */
		void animationSelect();

	public:

		/**
	    * @brief Procédure charge le menu principale
	    * @details Initialise la sprite du menu principale.
	    */
		sfmlMenu();

		/**
	    * @brief Met à jour le rendu de sélection du terrain.
	    * @param sf::RenderTarget &render : La fenêtre de rendu SFML  
	    */
		void update(sf::RenderTarget &render);

		/**
	    * @brief Procédure qui modifie l'idTerrain lorsque qu'on appuie sur 
	    * flèche haut
	    * @details Modifie l'idTerrain et met à jour la spriteFl
	    */
		void deplacementHaut();

		/**
	    * @brief Procédure qui modifie l'idTerrain lorsque qu'on appuie sur 
	    * flèche bas
	    * @details Modifie l'idTerrain et met à jour la spriteFl
	    */
		void deplacementBas();

		/**
	    * @brief Procédure qui modifie l'idTerrain lorsque qu'on appuie sur 
	    * flèche droite
	    * @details Modifie l'idTerrain et met à jour la spriteFl
	    */
		void deplacementDroite();

		/**
	    * @brief Procédure qui modifie l'idTerrain lorsque qu'on appuie sur 
	    * flèche gauche
	    * @details Modifie l'idTerrain et met à jour la spriteFl
	    */
		void deplacementGauche();

		/**
	    * @brief Procédure qui permet l'animation du menu principale.
	    * @details Modifie toutes les 0.03 secondes spriteHome pour
	    * permettre l'animation du menu principale.
	    */
		void animationStart();

		/**
	    * @brief Procédure qui initialise l'affichage du menu de sélection 
	    * des modes
	    * @details Les sprites spriteHome et spriteMode sont initialisées.
	    */
		void initHomeSelect();

		/**
	    * @brief Procédure qui initialise l'affichage du menu de sélection 
	    * des terrains.
	    * @details Les sprites backgroundColor, spriteBackground et spriteFlag
	    * sont initialisées.
	    */
		void initStageSelect();

		/**
	    * @brief Procédure qui affiche la sélection du mode 1 joueur.
	    * @details Modifie la spriteMode.
	    */
		void animationSuperBattle();

		/**
	    * @brief Procédure qui affiche la sélection du mode 2 joueur.
	    * @details Modifie la spriteMode.
	    */
		void animationVersusBattle();

		/**
	    * @brief Procédure qui initialise l'affichage du menu restart.
	    * @details La spritea spriteBackground est initialisée.
	    */
		void initRestartSelect();

		/**
	    * @brief Procédure qui affiche la sélection REJOUER.
	    * @details Modifie la spriteBackground.
	    */
		void animationRestartSelect();

		/**
	    * @brief Procédure qui affiche la sélection MENU PRINCIPAL.
	    * @details Modifie la spriteBackground.
	    */
		void animationHomeSelect();

		/**
	    * @brief Procédure qui dessine dans le fenêtre la spriteHome.
	    * @param sf::RenderTarget &render : La fenêtre de rendu SFML
	    */
		void dessineHome(sf::RenderTarget &render);

		/**
	    * @brief Procédure qui dessine dans le fenêtre la spriteMode.
	    * @param sf::RenderTarget &render : La fenêtre de rendu SFML
	    */
		void dessineMode(sf::RenderTarget &render);

		/**
	    * @brief Procédure qui dessine dans le fenêtre la spriteBackground.
	    * @param sf::RenderTarget &render : La fenêtre de rendu SFML
	    */
		void dessineBackground(sf::RenderTarget &render);

		/**
	    * @brief Accesseur de la donnée idTerrain
	    */
		int getIdTerrain() const;	
};



#endif