#include "Personnage.h"
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <cassert>
#include <iostream>


Personnage::Personnage()
{
  position = make_vec2(0.0,0.0);
  vel = make_vec2(0.0,0.0);
  vie = 100;
  tailleX = 0;
  tailleY = 0;
  regardeDroite = true;
  parade = false;
  accroupi = false;
  deplacement = false;
  timerAction = clock();
  currentAction = 0;
}

void Personnage::init(unsigned int width, unsigned int height, unsigned int fistSize, unsigned int footSize, Vec2 positionDefault)
{
  tailleX = width;
  tailleY = height;
  taillePoing = fistSize;
  taillePied = footSize;
  position = positionDefault;
}

void Personnage::setPosition(Vec2 newPosition)
{
	position = newPosition;
}

Vec2 Personnage::getVel() const
{
	return vel;
}

void Personnage::setVel(Vec2 newVel)
{
	vel = newVel;
}

void Personnage::deplacementDroite(float deplacement)
{
  if(currentAction == 0 || currentAction == 10 || currentAction == 20)
    vel += make_vec2(deplacement,0);
}

void Personnage::deplacementGauche(float deplacement)
{
  if(currentAction == 0 || currentAction == 10 || currentAction == 20)
    vel += make_vec2(-deplacement,0);
}

void Personnage::sauter(float valeur_saut)
{
	if(currentAction == 0) // si le personnage n'a aucune action en cours
  {
		vel.y = valeur_saut;
    currentAction = 20; // action en cours devient 'saut'
  }
}

void Personnage::accroupir()
{
  // si le personnage n'a aucune action en cours et qu'il est immobile
  if(currentAction == 0 && vel.x == 0)
  {    
    currentAction = 10; // l'action en cours devient 'accroupi'
    accroupi = true;
  }
}

void Personnage::hadoken()
{
  if(projectile.vivant == false && currentAction == 0)
  {
    currentAction = 4;
    if(regardeDroite)
      projectile.position = make_vec2(position.x + tailleX + taillePoing, position.y - 0.7 * tailleY);
    else
      projectile.position = make_vec2(position.x - (tailleX + taillePoing), position.y - 0.7 * tailleY);
    projectile.regardeDroite = regardeDroite;
  }
}

void Personnage::accroupirPersistant()
{
  // si le personnage n'a aucune action en cours et qu'il est immobile
  if(vel.x == 0)
  {
    if(!accroupi)
    {
      if(currentAction == 0)
      {
        accroupi = true;
        currentAction = 10; // l'action en cours devient 'accroupi'
      }
      if(currentAction == 3)
      {
        accroupi = true;
        currentAction = 13; // l'action en cours devient 'accroupi parade'
      }
    }    
    else
    {
      if(currentAction == 10)
      {
        currentAction = 0; // l'action en cours devient 'debout'
        accroupi = false;
      }
      if(currentAction == 13)
      {
        currentAction = 3; // l'action en cours devient 'debout parade'
        accroupi = false;
      }
    }
  }
}

void Personnage::blocking()
{
  // si le personnage est immobile et au sol
  if(vel.x == 0)
  {
    // si le personnage est debout
    if(currentAction == 0)
    {
      currentAction = 3; // animation de parade debout
      parade = true; // active la parade : le joueur ne recevra aucun degats sur la frame a venir
    }
    // si le personnage est accroupi
    if(currentAction == 10)
    {
      currentAction = 13; // animation de parade accroupi
      parade = true; // active la parade : le joueur ne recevra aucun degats sur la frame a venir
    }
  }
}

void Personnage::blockingPersistant()
{
  // si le personnage est immobile et au sol
  if(vel.x == 0)
  {
    if(!parade) // Si le personnage n'est pas en parade
    {
      // si le personnage est debout
      if(currentAction == 0)
      {
        currentAction = 3; // animation de parade debout
        parade = true; // active la parade : le joueur ne recevra aucun degats sur la frame a venir
      }
      // si le personnage est accroupi
      if(currentAction == 10)
      {
        currentAction = 13; // animation de parade accroupi
        parade = true; // active la parade : le joueur ne recevra aucun degats sur la frame a venir
      }
    }
    else // Si le personnage est en parade
    {
      parade = false;

      // si le personnage est debout
      if(currentAction == 3)
        currentAction = 0; // animation de parade debout

      // si le personnage est accroupi
      if(currentAction == 13)
        currentAction = 10; // animation de parade accroupi
    } 
  }
}

void Personnage::update(float v_gravitation, float hauteurSol, float dimX, float offset)
{
  // maj de la position
  position += vel;
  vel.x = 0;

  // si le psng chute en arriere
  if(currentAction == 93)
  {
    if(regardeDroite)
      position.x -= 1;
    else
      position.x += 1;
  }

  // application de la gravite
  vel.y += v_gravitation; 

  if(getPosition().x <= 2.0f+offset)
      position.x = 2+offset;
  else if(getPosition().x >= dimX-3.0f-offset)
      position.x = dimX-3.0f-offset;

  // maintiens le joueur au dessus du sol
  if(position.y >= hauteurSol) 
  {
  	vel.y = 0;
    position.y = hauteurSol;
  }
}

Vec2 Personnage::getPosition() const
{
	return position;
}

void Personnage::coupPoing(Personnage & psng)
{
  if(currentAction == 10) // si le psng est accroupi immobile
  {
    currentAction = 11; // coup de poing accroupi
    // portee (X,Y) du coup de poing accroupi
    if(abs(getPosition().x - psng.getPosition().x)<psng.tailleX+taillePoing)
      if(abs(getPosition().y - psng.getPosition().y)<(tailleY/3.0))
      {
          if(psng.accroupi && !psng.parade)
            psng.currentAction = 92;
          else if(psng.currentAction == 20)
            psng.currentAction = 93;
          else
            psng.currentAction = 90;
          psng.encaisseDegats(5);
      }
  } 
  else if(currentAction == 0) // si le personnage est debout immobile
  {
    currentAction = 1; // coup de poing debout
    // portee (X,Y) du coup de poing debout
    if(abs(getPosition().x - psng.getPosition().x)<psng.tailleX+taillePoing)
      if(abs(getPosition().y - psng.getPosition().y)<(tailleY/3.0))
        if(psng.parade==false && psng.accroupi==false)
        {
          if(psng.currentAction == 20)
            psng.currentAction = 93;
          else
            psng.currentAction = 91;
          psng.encaisseDegats(5);
        }
  }
} 

void Personnage::coupPied(Personnage & psng)
{
  if(currentAction == 10) // si le psng est accoupi immobile
  {
    currentAction = 12; // coup de pied accroupi
    // portee (x,y) du coup de pied accroupi
    if(abs(getPosition().x - psng.getPosition().x)<psng.tailleX+(taillePied*1.6))
      if(abs(getPosition().y - psng.getPosition().y)<(tailleY/3.0))
        if(!(psng.parade==true && psng.accroupi == true))
        {
          psng.currentAction = 93;
          psng.encaisseDegats(5);
        }
  }
  else if(currentAction == 0) // si le psng est debout immobile
  {
    currentAction = 2; // coup de pied debout
    // portee (x,y) du coup de pied debout
    if(abs(getPosition().x - psng.getPosition().x)<psng.tailleX+taillePied)
      if(abs(getPosition().y - psng.getPosition().y)<(tailleY/3.0))
        if(!psng.parade && !psng.accroupi)
        {
          if(psng.currentAction == 20)
            psng.currentAction = 93;
          else
            psng.currentAction = 91;
          psng.encaisseDegats(10);
        }
  }
}

void Personnage::animationActionEnCoursTerminee(bool keepAccroupi)
{
  accroupi = keepAccroupi;
  parade = false;
  if(accroupi)
    currentAction = 10;
  else
    currentAction = 0;
}


void Personnage::encaisseDegats(int montantDegats)
{
  vie -= montantDegats;
  if(vie <= 0)
    vie = 0;
}

void Personnage::testregression()
{
  srand(time(NULL));
  for(int i=0; i<1000; i++)
  {
    // Vérifie le fonctionnement du constructeur
    Personnage p1;
    assert(p1.getPosition().x == 0);
    assert(p1.getPosition().y == 0);
    assert(p1.getVel().x == 0);
    assert(p1.getVel().y == 0);
    assert(p1.vie == 100);
    assert(p1.tailleX == 0);
    assert(p1.tailleY == 0);
    assert(p1.regardeDroite == true);
    assert(p1.parade == false);
    assert(p1.currentAction == 0);

    // Vérifie le fonctionnement de setPosition/setVel
    float x1Rand = rand()/100000.0;
    float y1Rand = rand()/100000.0;

    float x2Rand = rand()/100000.0;
    float y2Rand = rand()/100000.0;

    p1.setPosition(make_vec2(x1Rand, y1Rand));
    p1.setVel(make_vec2(x2Rand, y2Rand));

    assert(p1.getPosition().x == x1Rand);
    assert(p1.getPosition().y == y1Rand);
    assert(p1.getVel().x == x2Rand);
    assert(p1.getVel().y == y2Rand);

    // Vérifie le fonctionnement de deplacementDroite/Gauche
    float x3Rand = rand()/100000.0;
    float x4Rand = rand()/100000.0;

    p1.deplacementDroite(x3Rand);
    assert(p1.getVel().x == x2Rand+x3Rand);
    assert(p1.getVel().y == y2Rand);

    p1.deplacementGauche(x4Rand);
    assert(p1.getVel().x == x2Rand+x3Rand-x4Rand);
    assert(p1.getVel().y == y2Rand);

    // Vérifie le fonctionnement de sauter
    float y3Rand = rand()/100000.0;
    p1.sauter(y3Rand);
    assert(p1.getVel().x == x2Rand+x3Rand-x4Rand);
    assert(p1.getVel().y == y3Rand);

    // Vérifie le fonctionnement de update

  }

  std::cout << "Tous les tests du module Personnage ont réussit" << std::endl;
}