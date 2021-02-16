/**
@brief Module gérant un Personnage

@file Personnage.h
@date 2020/03/14
*/

#ifndef _PERSONNAGE_H_
#define _PERSONNAGE_H_

#include <ctime>
#include "Vec2.h"
#include "Projectile.h"

class Personnage
{
	private:
		Vec2 position;
		Vec2 vel;

	public:
		int vie;
		float tailleX, tailleY, taillePoing, taillePied;
		Projectile projectile;
		bool regardeDroite;
		bool accroupi;
		bool parade;
		bool deplacement;
		clock_t timerAction;
		unsigned char currentAction;
		
		/**
	    * @brief Constructeur par défaut
	    * @details Initialise le Personnage : sa vie à 100 et intilisate le 
	    * timer timerAction.
	    */
		Personnage();

		/**
	    * @brief initialisation des parametres du personnage qui dependent de
	    * l'environnement.
	    */
		void init(unsigned int width, unsigned int height, unsigned int fistSize, 
				  unsigned int footSize, Vec2 positionDefault);

	  	/**
	    * @brief Procédure qui deplace le Personnage vers la droite
	    * @details On ajoute un vecteur vitesse horizontal à vel pour déplacer 
	    * le Personnage vers la droite.
	    */
		void deplacementDroite(float deplacement);

		/**
	    * @brief Procédure qui deplace le Personnage vers la gauche
	    * @details On ajoute un vecteur vitesse horizontal à vel pour déplacer
	    * le Personnage vers la droite.
	    */
		void deplacementGauche(float deplacement);

		/**
	    * @brief Procedure qui fait sauter le Personnage
	    * @details On ajoute un vecteur vitesse vertical à vel pour déplacer le
	    * Personnage vers le haut.
	    */
	    void sauter(float v_saut);

	    /**
	    * @brief Procédure qui accroupi le personnage
	    */
	    void accroupir();

	    /**
	    * @brief Procédure qui accroupi le personnage
	    */
	    void accroupirPersistant();

		/**
	    * @brief Procédure qui met à jour la position du Personnage en temps réel.
	    * @details Cette procédure est appellé à chaque tour de boucle pour 
	    * mettre à jour la position du personnage avec application de la 
	    * gravité et prise en compte des limites du terrain : hauteur du sol et
	    * extrémité gauche et droite du terrain. 
	    */
	    void update(float v_gravitation, float hauteurSol, float dimX, float offset);

	    /**
	    * @brief Accesseur position
	    * details Cette fonction retourne la position du Personnage de type 
	    * Vec2.
	    */
		Vec2 getPosition() const;

		/**
	    * @brief Mutateur position
	    * @details Cette procédure modifie la position du personnage par la 
	    * position, de type Vec2, passé en paramètre.
	    * @param Vec2 newPosition : vecteur 2D
	    */
		void setPosition(Vec2 newPosition);

		/**
	    * @brief Accesseur vel
	    * details Cette fonction retourne la velocite du Personnage (vel) qui
	    * est de type Vec2.
	    */
		Vec2 getVel() const;

		/**
	    * @brief Mutateur vel
	    * @details Cette procédure modifie la vélocité du personnage (vel) par
	    * la vélocité, de type Vec2, passé en paramètre.
	    * @param Vec2 newVel : vecteur 2D
	    */
		void setVel(Vec2 newVel);

		/**
		* @brief Procédure qui met à jour la vie si le coup de poing est valide.
		* @details Cette procédure vérifie si le Personnage courant et celui 
		* passé en paramètre sont assez proches et si il n'y a pas parade lors
		* du coup poing. Alors, la vie du Personnage passé en paramètre est 
		* mise à jour.
		* @param Personnage psng : référence sur le Personnage qui reçoit le
		* coup de poing.
		*/
	    void coupPoing(Personnage & psng);

	    /**
		* @brief Procédure qui met à jour la vie si le coup de pied est valide.
		* @details Cette procédure vérifie si le Personnage courant et celui 
		* passé en paramètre sont assez proches et si il n'y a pas parade lors
		* du coup pied. Alors, la vie du Personnage passé en paramètre est mise
		* à jour.
		* @param Personnage psng : référence sur le Personnage qui reçoit le
		* coup de pied.
		*/
	    void coupPied(Personnage & psng);

	    /**
	    * @brief Procédure qui permet de lancer le coup special.
	    * @details Le Projectile associé au Personnage est activé,
	    * sa propriété vivant est modifié.
	    */
	    void hadoken();

		/**
	    * @brief Retire montantsDegats pv au personnage
	    */
	  	void encaisseDegats(int montantDegats);

	  	/**
	    * @brief testRegression des fonctionalités du module Personnage
	    */
	  	void testregression();
		
		/**
	    * @brief Procédure qui active la parade du joueur
	    * @details Si le joueur est immobile, il ne recevra aucun degats sur la
	    * frame a venir
	    */
	    void blocking();

	    /**
	    * @brief Procédure qui active/desactive la parade du joueur 
	    * @details Si le joueur est immobile, il ne recevra aucun degats 
	    * jusqu'a ce que blockingPersistant est rappelé.
	    */
	    void blockingPersistant();

	    /**
	    * @brief Procédure qui reinitialise l'action en cours.
	    * @details Appeller en fin d'animation pour réinitialiser les variables
	    * currentAction, parade et accroupi. Pour mettre fin a une action en
	    * gardant le joueur accroupi appeller la fonction avec keepAccroupi sur
	    * true.
	    */
	    void animationActionEnCoursTerminee(bool keepAccroupi = false);
};
#endif