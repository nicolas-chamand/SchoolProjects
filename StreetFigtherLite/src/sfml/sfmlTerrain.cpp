#include "sfmlTerrain.h"
#include <map>
#include <fstream>
#include <iostream>

void sfmlTerrain::charger(int idTerrain)
{
	getDimensionsTerrain("terrain"+std::to_string(idTerrain));

	//Chargement de la texture du terrain
	if(!texture.loadFromFile("./data/terrain/terrain"+std::to_string(idTerrain)+std::string(".png")))
	{
		std::cout << "Trying ../data/terrain/terrain"+std::to_string(idTerrain)+std::string(".png") << std::endl;
		texture.loadFromFile("../data/terrain/terrain"+std::to_string(idTerrain)+std::string(".png"));
	}

	//Initialisation du rectangle à déplacer
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = dimX;
	rectSourceSprite.height = dimY;

	//Chargement du sprite à afficher dans la fenêtre
	sprite.setTexture(texture);
	sprite.setTextureRect(rectSourceSprite);
	sprite.setScale(2.5f,2.5f); // augmente la taille du terrain
	sprite.setPosition(0,0);
	sprite.move(-((dimX*2.5)-900)/2.0,0.0f); // la camera s'initialise au milieu du terrain
}

void sfmlTerrain::afficher(sf::RenderTarget &render)
{
	if(clock.getElapsedTime().asSeconds() > 0.1f)
	{
		//Si on n'est pas arrivé tout à droite
		if(rectSourceSprite.left != int((texture.getSize().x/dimX - 1)*dimX)) // la position du bord haut-gauche du rectSourceSprite en partant de 0 lorsqu'on est tout à droite 
			rectSourceSprite.left += dimX;
		//Sinon, on descend (ou monte) d'un cran
		else
		{
			rectSourceSprite.left = 0;
			//Si on n'est pas arrivé tout en bas
			if(rectSourceSprite.top != int((texture.getSize().y/dimY - 1)*dimY) ) // la position du bord haut-gauche du rectSourceSprite en partant de 0 lorsqu'on est tout en bas
			  rectSourceSprite.top += dimY;  
			//Sinon on remonte tout en haut
			else
			  rectSourceSprite.top = 0; 
		}
		clock.restart();
	}
	sprite.setTextureRect(rectSourceSprite);
	render.draw(sprite);
}  

void sfmlTerrain::getDimensionsTerrain(const string &nomTerrain)
{
	ifstream fichierLecture("./data/terrain/dimTerrain.txt");
	if (!fichierLecture.is_open())
	{
		std::cout << "Error loading dimTerrain.txt: Trying ../data/terrain/dimTerrain.txt" << std::endl;
		fichierLecture.open("../data/terrain/dimTerrain.txt");
		if(!fichierLecture.is_open())
		{
			std::cout << "Erreur dans l'ouverture en lecture du fichier : dimTerrain.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
 	}
 	string nom;
 	fichierLecture >> nom;
 	while(nom != nomTerrain)
 		fichierLecture >> nom;
 	fichierLecture >> dimX;
 	fichierLecture >> dimY;
 	fichierLecture.close();
}

float sfmlTerrain::cameraScroll(float deplacement)
{
	float r = sprite.getPosition().x + deplacement;
	if(r > 0) // Si on déplace trop à droite le terrain
	{
		sprite.setPosition(0,0);
		return -sprite.getPosition().x;
	}
	else if(r < -(dimX*2.5 - 900)) // Si on déplace trop à gauche le terrain
	{
		sprite.setPosition(-(dimX*2.5 - 900),0);
		return sprite.getPosition().x + (dimX*2.5 - 900);
	}
	else
	{
		sprite.move(deplacement, 0);
		return deplacement;
	}
}