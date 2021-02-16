#ifndef _JEU_H_
#define _JEU_H_

#include "Personnage.h"
#include "Projectile.h"
#include <ctime>

using namespace std;

struct Environnement
{
	int DIMX;
	int DIMY;
	int hauteurSol;
	int epaisseurBordure;

	float v_gravitation;
	float v_saut;
	float deplacement;
	float maxDelay;
};

class Jeu
{
	public:

		Personnage joueur1, joueur2;
		Environnement env;
		bool mode;
		bool debut, fin;
		unsigned char winJ1, winJ2;
		clock_t delayDebut, delayFin;


		/**
	    * @brief Constructeur par défaut
	    * @details Initialise la direction du regard des Personnages. (seul utilité pour le moment)
	    */
		Jeu();

		/**
	    * @brief Procédure d'initialisation de l'environnement
	    * @param int dim_X : dimension en abscisse du Terrain
	    * @param int dim_Y : dimension en ordonnée du Terrain
	    * @param int hauteur_Sol : hauteur en pixel entre le haut de l'écran et le
	    * sol du terrain
	    * @param int epaisseur_bordure : épaisseur en pixel pour le caméraScroll
	    * @param float gravite : valeur en px pour la gravité
	    * @param float saut : valeur en px pour le saut
	    * @param float vitesse : valeur en px pour les déplacements
	    * @param float delai : delai en seconde pour le début/fin du round
	    */
		void initEnvironnement(int dim_X, int dim_Y, int hauteur_Sol, int epaisseur_bordure, float gravite, float saut, float vitesse, float delai);

		/**
	    * @brief Procédure qui gère la collision des projectiles
	    * @details En cas de collisions avec un personnage ou entre projectiles
	    * modifie la propriété vivant du projectile.
	    */
		void collisionProjectile();

		/**
	    * @brief Procédure qui met à jour les projectiles
	    * @details Mets à jour la position des projectiles et gère leurs
	    * collisions.
	    */
		void updateProjectiles();

		/**
	    * @brief Procédure qui permet le contrôle automatique du joueur 2
	    * @details Par l'utilisation de rand(), permet de faire des actions
	    * de déplacements et d'attaques automatique pour le jouer 2.
	    */
		void comportementAutoJoueur2();

		/**
	    * @brief Procédure de detection de collision entre Personnage
	    */
		bool collision();

		/**
	    * @brief Procédure d'application des collisions entre Personnage
	    * @details Corrige les velocites des personnages en cas de contact entre eux
	    */
		void collisionPersonnage(Personnage & joueur1, Personnage & joueur2);

		/**
	    * @brief Procédure qui met à jour le Jeu.
	    * @details Cette procédure permet de mettre à jour la direction du
	    * regard des Personnage. Elle vérifie si un round est terminé et 
	    * initialise un délai. Elle permet la collision entre les personnages. 
	    */
		void update();

		/**
	    * @brief Procédure qui associe des actions aux fonctions de déplacements
	    * ou attaque de Personnage.
	    * @details Cette procédure associe une action du Personnage à un char. 
	    * Elle est appelé lors de la gestion d'événement clavier.
	    */
		void actionClavier(const char action);

		/**
	    * @brief Procédure qui ré-affecte les valeurs par défaut de Jeu pour
	    * permettre une nouveau round. 
	    */
		void restartRound();

		/**
	    * @brief Procédure qui ré-affecte les valeurs par défaut de Jeu pour
	    * permettre une nouvelle partie. .
	    */
		void restartGame();

		/**
	    * @brief Procédure qui test le bon fonctionnement du module
	    * @details Cette procédure execute 25 000 updates et actionsClavier 
	    * aléatoires et s'assure de leur bon déroulement.
	    */
		void testRegression();
};

#endif