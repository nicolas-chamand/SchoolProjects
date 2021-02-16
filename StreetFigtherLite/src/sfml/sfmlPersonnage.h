#ifndef _SFMLPERSONNAGE_H
#define _SFMLPERSONNAGE_H

#include "SFML/Graphics.hpp"
#include "Personnage.h"
#include <string>

class sfmlPersonnage
{
  protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect rectSourceSprite;
    sf::Clock clock;
    Personnage *personnage;

    /**
    * @brief Animation du personnage debout inactif.
    */
    void animationDeboutInactif();
    
    /**
    * @brief Animation du personnage en deplacement.
    */
    void animationDeplacement();

    /**
    * @brief Animation du personnage en saut.
    * @details Postcondition: Lorsque l'animation est terminée, l'action du personnage est reinitialisée.
    */
    void animationSaut(int hauteurSol);
    
    /**
    * @brief Animation du personnage en saut.
    * @details Postcondition: Lorsque l'animation est terminée, l'action du personnage est reinitialisée : en particulier le booleen accroupi du Personnage animé ne vaut plus true.
    */
    void animationAccroupi();
    
    /**
    * @brief Animation d'un coup de poing debout.
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée.
    */
    void animationCoupPoingDebout();
    
    /**
    * @brief Animation d'un coup de poing accroupi.
    * @details Postcondition: Lorsque l'animation est terminée, l'action du personnage est reinitialisée : en particulier le booleen accroupi du Personnage animé ne vaut plus true.
    */
    void animationCoupPoingAccroupi();

    /**
    * @brief Animation d'un coup de pied debout.
    * @details Postcondition: Lorsque l'animation prend fin, l'action du personnage est reinitialisée.
    */
    void animationCoupPiedDebout();

    /**
    * @brief Animation d'un coup de pied accroupi.
    * @details Postcondition: Lorsque l'animation est terminée, l'action du personnage est reinitialisée : en particulier le booleen accroupi du Personnage animé ne vaut plus true.
    */
    void animationCoupPiedAccroupi();

    /**
    * @brief Animation de parade debout.
    * @details Postcondition: Lorsque l'animation est terminée, l'action du personnage est reinitialisée : en particulier le booleen accroupi du Personnage animé ne vaut plus true.
    */
    void animationParadeDebout();

    /**
    * @brief Animation d'un coup de poing accroupi.
    * @details Postcondition: Lorsque l'animation est terminée, l'action du personnage est reinitialisée : en particulier les booleens accroupi et parade du Personnage animé ne valent plus true.
    */
    void animationParadeAccroupi();

  public:
    
    /**
    * @brief Constructeur
    * @details Charge la texture, initialise la sprite et le rectangle source associé.
    */
    sfmlPersonnage(const std::string &nomPersonnage);
    
    /**
    * @brief Procédure d'initialisation du pointeur sur le personnage qui sera animé par le module.
    */
    void init(Personnage *psng);

    /**
    * @brief Mise à jour de la position de la sprite par rapport à la position du personnage.
    * @details Prend en compte le regard du personnage pour appliquer une symetrie horizontale si necessaire.
    */
    void update();
};
#endif