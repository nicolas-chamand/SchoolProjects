/**
@brief Module gérant un vecteur 2D
@details Les opérateurs +,-,=,+= et * par un scalaire sont surchargés
@file Vec2.h
@date 2020/03/14
*/

#ifndef _VEC2_H
#define _VEC2_H

/**
@brief Un Vec2 = (x,y)
*/
class Vec2
{
	public:
	
		float x, y;

		/**
		* @brief Constructeur avec paramètres
		* @details Crée un vecteur 2D avec les valeurs (newY, newY) passé
		* en paramètre.
		* @param float newX : nouvelle valeur en abscisse 
		* @param float newY : nouvelle valeur en ordonné
		*/
		Vec2(float newX, float newY);

		/**
		* @brief Constructeur par défaut
		* @details Crée un vecteur 2D (0, 0).
		*/
		Vec2();

		/**
		* @brief Procédure qui permet le teste des fonctionnalités du module
		* Vec2.
		*/
		void testregression();
};
		/**
		* @brief Fonction qui créer et retourne un Vec2.
		* @details Créer un Vec2 avec les valeurs passées en paramètres
		* et le retourne.
		*/
		Vec2 make_vec2(float x, float y);

		/**
		* @brief Fonction qui permet l'ajout de deux Vec2.
		* @details Un nouveau Vec2 est retourné avec comme valeurs
		* l'addition des composantes des deux vecteurs.
		*/
		Vec2 operator+(const Vec2& a, const Vec2& b);

		/**
		* @brief Fonction qui permet la soustraction de deux Vec2.
		* @details Un nouveau Vec2 est retourné avec comme valeurs
		* la soustraction des composantes des deux vecteurs.
		*/
		Vec2 operator-(const Vec2& a, const Vec2& b);

		/**
		* @brief Fonction qui permet l'utilisation de "+=" entre deux Vec2.
		* @details Affecte dans le Vec2 de gauche les valeurs de l'addition 
		* des composantes des deux vecteurs.
		*/
		Vec2 operator+=(Vec2& a, const Vec2& b);

		/**
		* @brief Fonction qui permet la multiplication d'un Vec2 par un scalaire.
		* @details Un nouveau Vec2 est retourné avec comme valeurs
		* la multiplication du scalaire avec les composantes du Vec2.
		*/
		Vec2 operator*(float a, const Vec2& b);
#endif