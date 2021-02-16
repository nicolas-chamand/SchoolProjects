#include "Ryu.h"

Ryu::Ryu() : sfmlPersonnage("ryu")
{}

void Ryu::animationEncaisseCoupCorps()
{
  // si la sprite en cours n'est pas une sprite de l'animation
  if(rectSourceSprite.top != 751 || rectSourceSprite.left >= 163)
  {
    // je temporise pour laisser le coup venir jusqu'au joueur
    if(clock.getElapsedTime().asSeconds() > 0.18f)
    {
      // premiere sprite
      rectSourceSprite.top = 751;
      rectSourceSprite.left = 5;
      rectSourceSprite.width = 43;
      rectSourceSprite.height = 87;
    }
  }
  // je vais de sprite en sprite chaque 0.1 sec
  else if(clock.getElapsedTime().asSeconds() > 0.1f)
  {
    if(rectSourceSprite.left == 5)
    {
      rectSourceSprite.width = 48;
      rectSourceSprite.left = 52;
    }
    else if(rectSourceSprite.left == 52)
    {
      rectSourceSprite.width = 50;
      rectSourceSprite.left = 105;
    }
    else if(rectSourceSprite.left == 105)
    {
      rectSourceSprite.width = 43;
      rectSourceSprite.left = 163;
      personnage->animationActionEnCoursTerminee();
    } 
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}
void Ryu::animationEncaisseCoupTete()
{
  // si la sprite en cours n'est pas une sprite de l'animation
  if(rectSourceSprite.top != 751 || rectSourceSprite.left < 216 || rectSourceSprite.left >= 391)
  {
    // je temporise pour laisser le coup venir jusqu'au joueur
    if(clock.getElapsedTime().asSeconds() > 0.18f)
    {
      // premiere sprite
      rectSourceSprite.top = 751;
      rectSourceSprite.left = 216;
      rectSourceSprite.width = 49;
      rectSourceSprite.height = 87;
    }
  }
  // je vais de sprite en sprite chaque 0.1 sec
  else if(clock.getElapsedTime().asSeconds() > 0.1f)
  {
    if(rectSourceSprite.left == 216)
    {
      rectSourceSprite.left = 271;
      rectSourceSprite.width = 52;
    }
    else if(rectSourceSprite.left == 271)
    {
      rectSourceSprite.left = 327;
      rectSourceSprite.width = 59;
    }
    else if(rectSourceSprite.left == 327)
    {
      rectSourceSprite.left = 391;
      rectSourceSprite.width = 43;
      personnage->animationActionEnCoursTerminee();
    }
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}
void Ryu::animationEncaisseCoupAccroupi()
{
  if(rectSourceSprite.top != 751)
  {
    if(clock.getElapsedTime().asSeconds() > 0.18f)
    {
      rectSourceSprite.top = 751;
      rectSourceSprite.left = 450;
      rectSourceSprite.width = 46;
      rectSourceSprite.height = 87;
      clock.restart();
    }
  }
  if(clock.getElapsedTime().asSeconds() > 0.18f)
  {
    personnage->animationActionEnCoursTerminee(true);
    clock.restart();
  }
  sprite.setTextureRect(rectSourceSprite);
}

void Ryu::animationCoupSpecial()
{
  if(clock.getElapsedTime().asSeconds() > 0.12f)
  {
    if(rectSourceSprite.top != 633 || rectSourceSprite.left >= 298)
    {
      rectSourceSprite.left = 4;
      rectSourceSprite.top = 633;
      rectSourceSprite.width = 52;
      rectSourceSprite.height = 87;
    }
    else if(rectSourceSprite.left == 4)
    {
      rectSourceSprite.left = 60;
      rectSourceSprite.width = 66;
    }
    else if(rectSourceSprite.left == 60)
    {
      rectSourceSprite.left = 131;
    }
    else if(rectSourceSprite.left == 131)
    {
      rectSourceSprite.left = 202;
      rectSourceSprite.width = 91;
    }
    else if(rectSourceSprite.left == 202)
    {
      rectSourceSprite.left = 298;
      rectSourceSprite.width = 71;
      personnage->projectile.vivant = true;
      personnage->animationActionEnCoursTerminee();
    }
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}

void Ryu::animationEncaisseCoupSpecial(int hauteurSol)
{
  if((rectSourceSprite.top != 754 && rectSourceSprite.top != 732) 
      || rectSourceSprite.left < 510 || rectSourceSprite.left >= 948)
    {
      rectSourceSprite.left = 510;
      rectSourceSprite.top = 754;
      rectSourceSprite.width = 48;
      rectSourceSprite.height = 85;
      sprite.setTextureRect(rectSourceSprite);
      clock.restart();
    }
  else if(clock.getElapsedTime().asSeconds() > 0.12f)
  {
    if(rectSourceSprite.left == 510 && hauteurSol-personnage->getPosition().y<35)
    {
      rectSourceSprite.left = 568;
      rectSourceSprite.width = 43;
    }
    else if(rectSourceSprite.left == 568)
    {
      rectSourceSprite.left = 774;
      rectSourceSprite.width = 52;
    }
    else if(rectSourceSprite.left == 774)
    {
      rectSourceSprite.left = 831;
      rectSourceSprite.top = 732;
      rectSourceSprite.height = 104;
    }
    else if(rectSourceSprite.left == 831)
    {
      rectSourceSprite.left = 889;
      rectSourceSprite.width = 55;
    }
    else if(rectSourceSprite.left == 889)
    {
      rectSourceSprite.left = 948;
      rectSourceSprite.width = 42;
      personnage->animationActionEnCoursTerminee();
    }
    sprite.setTextureRect(rectSourceSprite);
    clock.restart();
  }
}

void Ryu::animationKO()
{
	if(clock.getElapsedTime().asSeconds() > 0.12f)
	{
		if(rectSourceSprite.top != 780 && rectSourceSprite.left != 1165)
		{
		  rectSourceSprite.left = 1165;
		  rectSourceSprite.top = 780;
		  rectSourceSprite.width = 45;
		  rectSourceSprite.height = 60;
		}
		else if(rectSourceSprite.left == 1165)
		{
		  rectSourceSprite.left = 1218;
		  rectSourceSprite.width = 72;
		}
		else if(rectSourceSprite.left == 1218)
		{
		  rectSourceSprite.left = 1295;
		  rectSourceSprite.width = 74;
		}
		else if(rectSourceSprite.left == 1295)
		{
		  rectSourceSprite.left = 1373;
		  rectSourceSprite.width = 72;
		}
		else if(rectSourceSprite.left == 1373)
		{
		  rectSourceSprite.left = 1450;
		  rectSourceSprite.width = 74;
      rectSourceSprite.height = 57;
		}
		sprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void Ryu::animationWin()
{
	if(clock.getElapsedTime().asSeconds() > 0.12f)
	{
		if(rectSourceSprite.top != 876 && rectSourceSprite.left != 160)
		{
		  rectSourceSprite.left = 160;
		  rectSourceSprite.top = 876;
		  rectSourceSprite.width = 43;
		  rectSourceSprite.height = 88;
		}
		else if(rectSourceSprite.left == 160)
		  rectSourceSprite.left = 207;
		else if(rectSourceSprite.left == 207)
		  rectSourceSprite.left = 254;
		else if(rectSourceSprite.left == 254 || rectSourceSprite.left == 446)
		  rectSourceSprite.left = 303;
		else if(rectSourceSprite.left == 303)
		  rectSourceSprite.left = 350;
		else if(rectSourceSprite.left == 350)
		  rectSourceSprite.left = 399;
		else if(rectSourceSprite.left == 399)
		  rectSourceSprite.left = 446;

		sprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void Ryu::afficher(sf::RenderTarget &render, int positionSol)
{
  update();
	render.draw(sprite);
	//AFFICHAGE DES HITBOX THEORIQUES POUR LE DEVELOPPEMENT ET DEBUG
	/*
	sf::RectangleShape hitbox(sf::Vector2f(personnage->tailleX*2, personnage->tailleY));
	hitbox.setFillColor(sf::Color(255,255,255,128));
	hitbox.setOutlineThickness(2);
	hitbox.setOutlineColor(sf::Color(255, 0, 0));
	hitbox.setPosition(personnage->getPosition().x-personnage->tailleX,personnage->getPosition().y-personnage->tailleY);
	render.draw(hitbox);
  */
	if(personnage->currentAction == 1) // COUP DE POING DEBOUT
		animationCoupPoingDebout();
	else if(personnage->currentAction == 2) // COUP DE PIED DEBOUT
		animationCoupPiedDebout();
	else if(personnage->currentAction == 3) // PARADE DEBOUT
		animationParadeDebout();
	else if(personnage->currentAction == 4) // COUP SPECIAL
		animationCoupSpecial();
	else if(personnage->currentAction == 10) // ACCROUPI
		animationAccroupi();
	else if(personnage->currentAction == 11) // COUP DE POING ACCROUPI
		animationCoupPoingAccroupi();
	else if(personnage->currentAction == 12) // COUP PIED ACCROUPI
		animationCoupPiedAccroupi();
	else if(personnage->currentAction == 13) // PARADE ACCROUPI
		animationParadeAccroupi();
	else if(personnage->currentAction == 20) // SAUT
		animationSaut(positionSol);
	else if(personnage->currentAction == 90) // COUP AU CORPS
		animationEncaisseCoupCorps();          
	else if(personnage->currentAction == 91) // COUP A LA TETE
		animationEncaisseCoupTete();
	else if(personnage->currentAction == 92) // COUP ACCROUPI
		animationEncaisseCoupAccroupi();
	else if(personnage->currentAction == 93) // ENCAISSE COUP SPECIAL
		animationEncaisseCoupSpecial(positionSol);
	else if(personnage->currentAction == 99) // K.O
		animationKO();
	else if(personnage->currentAction == 100) // Win
		animationWin();
	else if(personnage->deplacement) // DEPLACEMENT
		animationDeplacement();
	else // IMMOBILE
		animationDeboutInactif();
}