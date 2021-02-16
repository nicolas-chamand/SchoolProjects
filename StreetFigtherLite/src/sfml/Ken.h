#ifndef _KEN_H
#define _KEN_H

#include "sfmlPersonnage.h"

class Ken : public sfmlPersonnage
{
	private:

	/**
    * @brief Animation du personnage qui encaisse un coup dans le corps.
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée.
    */
	void animationEncaisseCoupCorps();

	/**
    * @brief Animation du personnage qui encaisse un coup au visage.
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée.
    */
	void animationEncaisseCoupTete();

	/**
    * @brief Animation du personnage qui encaisse un coup accroupi.
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée sur accroupi.
    */
	void animationEncaisseCoupAccroupi();

	/**
    * @brief Animation du personnage qui lance un projectile
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée et le projectile devient vivant.
    */
	void animationCoupSpecial();

	/**
    * @brief Animation du personnage qui encaisse un coup qui le projete au sol.
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée.
    */
	void animationEncaisseCoupSpecial(int hauteurSol);
		
	/**
    * @brief Animation du personnage KO.
    */
	void animationKO();
		
	/**
    * @brief Animation du personnage victorieux.
    */
	void animationWin();
	
	public:
  	
  	Ken();
  	
	/**
    * @brief Procédure d'affichage et animation du personnage dans le render.
	* @details Postcondition : lorsqu'une animation prend fin, l'action en cours du personnage et ses variables associées sont reinitialisés.
	*/
  	void afficher(sf::RenderTarget &render, int positionSol);
};
#endif