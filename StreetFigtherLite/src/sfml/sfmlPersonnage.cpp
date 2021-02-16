#include "sfmlPersonnage.h"
#include <cmath>
#include <iostream>
#include <string>

sfmlPersonnage::sfmlPersonnage(const std::string &nomPersonnage) : rectSourceSprite(6,14,43,87) 
{
  	personnage = NULL;
  	sf::Image img;
    // charge d'abord le .png dans une image
    if(nomPersonnage == "ryu")
    {
      if(!img.loadFromFile("data/texture_ryu.png"))
      {
        std::cout << "Trying ../data/texture_ryu.png" << std::endl;
          img.loadFromFile("../data/texture_ryu.png");
      }
    }
    else
    {
      if(!img.loadFromFile("data/texture_ken.png"))
      {
        std::cout << "Trying ../data/texture_ken.png" << std::endl;
          img.loadFromFile("../data/texture_ken.png");
      }
    }
    // recupere et supprime la couleur de fond de l'image
    img.createMaskFromColor(img.getPixel(1,1));
    // charge la texture depuis l'image sans sa couleur de fond
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    sprite.setTextureRect(rectSourceSprite);
    // augmente la taille du personnage
    sprite.scale(sprite.getScale()*3.0f);
}

// met a jour la position de la sprite en fonction de la pos du psng et de son regard
void sfmlPersonnage::update()
{
    sf::Vector2f translation;
    if(!personnage->regardeDroite)
    {
      // symetrie d'axe vertical
      sprite.setScale(-1.0f * abs(sprite.getScale().x), sprite.getScale().y);
      translation = sf::Vector2f(60.0f,-rectSourceSprite.height*3.0);
    }
    else
    {
      sprite.setScale(abs(sprite.getScale().x), sprite.getScale().y);
      translation = sf::Vector2f(-60.0f,-rectSourceSprite.height*3.0);
    }
    // translation de la position de la sprite par rapport a la position du psng
    translation.x += personnage->getPosition().x; 
    translation.y += personnage->getPosition().y;
    sprite.setPosition(translation); 
 }

void sfmlPersonnage::init(Personnage *psng)
{
  personnage = psng;
  update();
}

void sfmlPersonnage::animationSaut(int hauteurSol)
{
  // je vais de sprite en sprite chaque 0.08 sec
  if(clock.getElapsedTime().asSeconds() > 0.08f)
  {
    // si la sprite en cours n'est pas une sprite de saut
    if(rectSourceSprite.left < 501 || rectSourceSprite.left >= 697)
    {
      // premiere sprite de saut
      rectSourceSprite.left = 501;
      rectSourceSprite.top = 9;
      rectSourceSprite.width = 43;
      rectSourceSprite.height = 77;
    }
    else
    {
      // si la sprite en cours est la premiere sprite de saut
      if(rectSourceSprite.left == 501)
      {
        // re-ajustements
        rectSourceSprite.top = 14;
        rectSourceSprite.height = 87;
      }
      if(rectSourceSprite.left == 501 || rectSourceSprite.left == 538)
        rectSourceSprite.left += 37; // passage a la sprite suivante
      else if(rectSourceSprite.left == 575 && hauteurSol-personnage->getPosition().y<200)
        rectSourceSprite.left = 613;
      else if(rectSourceSprite.left == 613 && hauteurSol-personnage->getPosition().y<35)
      {
        rectSourceSprite.left = 697;
        personnage->animationActionEnCoursTerminee();
      }
    }
    clock.restart();
    sprite.setTextureRect(rectSourceSprite);
  }
}

void sfmlPersonnage::animationAccroupi()
{
  // si la sprite en cours n'est pas la sprite d'accroupissement
  if(rectSourceSprite.left != 1160 || rectSourceSprite.top != 14)
  {
    // sprite d'accroupissement
    rectSourceSprite.left = 1160;
    rectSourceSprite.top = 14;
    rectSourceSprite.width = 43;
    rectSourceSprite.height = 87;
  }
  // animation terminée, reset des variables associées
  personnage->animationActionEnCoursTerminee();

  sprite.setTextureRect(rectSourceSprite);
}

void sfmlPersonnage::animationCoupPoingDebout()
{
  if(clock.getElapsedTime().asSeconds() > 0.1f) // je vais de sprite en sprite chaque 0.1 sec
  {
    // si la sprite en cours n'est pas la 1re sprite de coup de poing
    if(rectSourceSprite.top != 130 || rectSourceSprite.left >= 117)
    {
      // premiere sprite de coup de poing
      rectSourceSprite.top = 130;
      rectSourceSprite.left = 3;
      rectSourceSprite.width = 43;
      rectSourceSprite.height = 87;
    }
    else if(rectSourceSprite.left == 3)
    {
      rectSourceSprite.left += 49;
      rectSourceSprite.width += 15;
    }
    else if(rectSourceSprite.left == 52)
    {
      rectSourceSprite.left += 65;
      rectSourceSprite.width -= 15;
      // animation terminee = fin de l'action
      personnage->animationActionEnCoursTerminee();
    }
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}

void sfmlPersonnage::animationCoupPoingAccroupi()
{
  // je vais de sprite en sprite chaque 0.1 sec
  if(clock.getElapsedTime().asSeconds() > 0.1f)
  {
    // si la sprite en cours n'est pas une sprite de coup de poing accroupi
    if(rectSourceSprite.top != 389 || rectSourceSprite.left >= 127)
    {
      // premiere sprite de l'animation
      rectSourceSprite.top = 389;
      rectSourceSprite.left = 9;
      rectSourceSprite.width = 46;
      rectSourceSprite.height = 87;
    }
    else if(rectSourceSprite.left == 9)
    {
      // deuxieme sprite de l'animation
      rectSourceSprite.left += 52;
      rectSourceSprite.width = 62;
    }
    else if(rectSourceSprite.left == 61)
    {
      // troisieme et derniere sprite de l'animation
      rectSourceSprite.left += 66;
      rectSourceSprite.width = 46;
      // animation terminée, reset des variables associées
      personnage->animationActionEnCoursTerminee();
    }
    clock.restart();
    sprite.setTextureRect(rectSourceSprite);
  }
}

void sfmlPersonnage::animationCoupPiedDebout()
{
  // je vais de sprite en sprite chaque 0.1 sec
  if(clock.getElapsedTime().asSeconds() > 0.1f)
  {
    // si la sprite en cours n'est pas une sprite de coup de pied
    if(rectSourceSprite.top != 260 || rectSourceSprite.left >= 133)
    {
      // premiere sprite
      rectSourceSprite.top = 260;
      rectSourceSprite.left = 8;
      rectSourceSprite.width = 50;
      rectSourceSprite.height = 87;
    }
    else if(rectSourceSprite.left == 8)
    {
      rectSourceSprite.left += 57;
      rectSourceSprite.width = 67;
    }
    else if(rectSourceSprite.left == 65)
    {
      rectSourceSprite.left += 72;
      rectSourceSprite.width = 50;
      personnage->animationActionEnCoursTerminee();
    }
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}

void sfmlPersonnage::animationCoupPiedAccroupi()
{
  // je vais de sprite en sprite chaque 0.1 sec
  if(clock.getElapsedTime().asSeconds() > 0.12f)
  {
    // si la sprite en cours n'est pas la 1re sprite de coup pied accroupi
     if(rectSourceSprite.top != 389 || rectSourceSprite.left < 846 || rectSourceSprite.left >= 993)
      {
        // position de la 1ere sprite de coup pied accroupi
        rectSourceSprite.top = 389; 
        rectSourceSprite.left = 846;
        rectSourceSprite.width = 49;
        rectSourceSprite.height = 87;
      }
      else if(rectSourceSprite.left == 846)
      {
        rectSourceSprite.left += 54;
        rectSourceSprite.width = 89;
      }
      else if(rectSourceSprite.left == 900)
      {
        rectSourceSprite.left += 93;
        rectSourceSprite.width = 49;
        personnage->animationActionEnCoursTerminee();
      }
    clock.restart();
    sprite.setTextureRect(rectSourceSprite);
  }  
}

void sfmlPersonnage::animationParadeAccroupi()
{
  // si la sprite en cours n'est pas la sprite de parade accroupi
  if(rectSourceSprite.left != 1260 || rectSourceSprite.top != 14)
  {
    // sprite de parade accroupi
    rectSourceSprite.left = 1260;
    rectSourceSprite.top = 14;
    rectSourceSprite.width = 43;
    rectSourceSprite.height = 87;
  }
  // animation terminée, reset des variables associées
  personnage->animationActionEnCoursTerminee();

  sprite.setTextureRect(rectSourceSprite);
}

void sfmlPersonnage::animationParadeDebout()
{
  // si la sprite en cours n'est pas la sprite de parade debout
  if(rectSourceSprite.left != 1211 || rectSourceSprite.top != 14)
  {
    // sprite de parade debout
    rectSourceSprite.left = 1211;
    rectSourceSprite.top = 14;
    rectSourceSprite.width = 43;
    rectSourceSprite.height = 87;
  }
  // animation terminée, reset des variables associées
  personnage->animationActionEnCoursTerminee();

  sprite.setTextureRect(rectSourceSprite);
}

void sfmlPersonnage::animationDeplacement()
{
  // je vais de sprite en sprite chaque 0.1 sec
  if(clock.getElapsedTime().asSeconds() > 0.1f)
  {
    // si la sprite en cours n'est pas une sprite de l'animation deplacement
    if(rectSourceSprite.left >= 399 || rectSourceSprite.left < 199 || rectSourceSprite.top != 14)
    {
      //premiere sprite de l'animation
      rectSourceSprite.left = 252;
      rectSourceSprite.top = 14;
      rectSourceSprite.width = 43;
      rectSourceSprite.height = 87;
    }
    else
      rectSourceSprite.left += 49;
    // correction des decalages hasardeux entre les sprites
    // valeurs trouvees pas tatonement pour que l'enchainement soit fluide
    if(rectSourceSprite.left == 350 || rectSourceSprite.left == 400)
      rectSourceSprite.left++;

    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}

void sfmlPersonnage::animationDeboutInactif()
{
  // je vais de sprite en sprite toutes les 0.08 sec
  if(clock.getElapsedTime().asSeconds() > 0.1f)
  {
    // si la sprite en cours n'est pas une sprite d'immobilité
    if(rectSourceSprite.left >= 152 || rectSourceSprite.top != 14)
    {
      rectSourceSprite.left = 6;
      rectSourceSprite.top = 14;
      rectSourceSprite.width = 43;
      rectSourceSprite.height = 87;
    } 
    else
      rectSourceSprite.left += 49;
    // correction d'un leger decalage des psng dans la texture
    // les sprites sont espaces de 49 pixels, sauf entre la 2 et la 3 (50px de difference)
    if(rectSourceSprite.left == 104)
          rectSourceSprite.left++;
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}