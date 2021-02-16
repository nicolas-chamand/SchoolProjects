/**
@brief Module gérant un projectile

@file Projectile.h
@date 2020/04/21
*/

#ifndef _Projectile_H_
#define _Projectile_H_

#include "Vec2.h"

class Projectile
{
	public:
		bool vivant;
		bool regardeDroite;
		Vec2 position;
		float taille;

		/**
	    * @brief Procédure d'initialisation du projectile.
	    * @details Postcondition : La valeur vivant est mise par defaut sur false.
	    */
		void init(unsigned int width);
		
		/**
	    * @brief Procédure qui met a jour la position du hadoken. ("coup spécial")
	    * @details Postcondition : La valeur de positionX est mise à jour.
	    */
		void miseAJourPosition(float vitesse);
};
#endif