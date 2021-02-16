#include "sfmlMenu.h"
#include <iostream>
#include <fstream>
#include <string>


sfmlMenu::sfmlMenu()
{
	//Chargement de la texture du menu principale
	if(!texture.loadFromFile("./data/homeStart.png"))
	{
		std::cout << "Trying ../data/homeStart.png" << std::endl;
		texture.loadFromFile("../data/homeStart.png");
	}

	// Initialisation pour la sprite Home
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = 600;
	rectSourceSprite.height = 338;

	spriteHome.setTexture(texture);
	spriteHome.setTextureRect(rectSourceSprite);
	spriteHome.setScale(1.63f, 1.63f);
	spriteHome.move(-40.0, 0);
}

int sfmlMenu::getIdTerrain() const
{
	return idTerrain;
}

void sfmlMenu::animationSelect()
{
	sf::Color color = spriteFlag.getColor();
	if(clock.getElapsedTime().asSeconds() > 0.08f)
	{
		if(color.a == 0)
		{
			sf::Color newColor(color.r, color.g, color.b, 255);
			spriteFlag.setColor(newColor);
		}
		else
		{
			sf::Color newColor(color.r, color.g, color.b, color.a-5);
			spriteFlag.setColor(newColor);
		}
	}
}

void sfmlMenu::deplacementHaut()
{
	if(idTerrain >= 6 && idTerrain <= 9)
	{
		idTerrain-=5;
	}
	else if(idTerrain >= 11 && idTerrain <= 16)
	{
		idTerrain-=6;
	}
	updateFlag();
}
void sfmlMenu::deplacementBas()
{
	if(idTerrain >= 1 && idTerrain <= 4)
	{
		idTerrain+=5;
	}
	else if(idTerrain >= 5 && idTerrain <= 10)
	{
		idTerrain+=6;
	}
	updateFlag();
}
void sfmlMenu::deplacementDroite()
{
	if(idTerrain != 4 && idTerrain != 10 && idTerrain != 16)
	{
		idTerrain++;
	}
	updateFlag();
}
void sfmlMenu::deplacementGauche()
{
	if(idTerrain != 1 && idTerrain != 5 && idTerrain != 11)
	{
		idTerrain--;
	}
	updateFlag();
}

void sfmlMenu::initStageSelect()
{
	// Initialisation du idTerrain
	idTerrain = 1;

	//Chargement de la texture du menu
	sf::Image img;
	if(!img.loadFromFile("./data/stageSelect.png"))
	{
		std::cout << "Trying ../data/stageSelect.png" << std::endl;
		img.loadFromFile("../data/stageSelect.png");
	}
    // recupere et supprime la couleur de fond de l'image
    img.createMaskFromColor(img.getPixel(1,1));

    texture.loadFromImage(img);

	//Initialisation du rectangle de la spriteBackground
	rectSourceSprite.left = 9;
	rectSourceSprite.top = 550;
	rectSourceSprite.width = 256;
	rectSourceSprite.height = 193;

	//Chargement du sprite à afficher dans la fenêtre
	spriteBackground.setTexture(texture);
	spriteBackground.setTextureRect(rectSourceSprite);
	spriteBackground.setScale(2.85f, 2.85f);
	spriteBackground.setPosition(0,0);
	spriteBackground.move(-((256*2.85)-900)/2.0,0.0f); // on place la sprite au milieu

	//Initialisation du rectangle de fond 
	backgroundColor.setSize(sf::Vector2f(900.f, 550.f));
	backgroundColor.setFillColor(sf::Color(0,0,112));

	//Initialisation du rectangle de la spriteFlag
	rectSourceSprite.left = 277;
	rectSourceSprite.top = 487;
	rectSourceSprite.width = 22;
	rectSourceSprite.height = 20;

	//Chargement du sprite à afficher dans la fenêtre
	spriteFlag.setTexture(texture);
	spriteFlag.setTextureRect(rectSourceSprite);
	spriteFlag.setScale(2.85f, 2.85f);
	spriteFlag.setPosition(0,0);
	spriteFlag.move(-((256*2.85)-900)/2.0,0.0f); // on place la sprite au bord du background
	spriteFlag.move(52*2.85,100*2.85); // on place la sprite au dessus du drapeau
}

void sfmlMenu::updateFlag()
{
	std::ifstream fichierLecture("./data/flagsPos.txt");
	if(!fichierLecture.is_open())
	{
		std::cout << "Error loading flagsPos.txt: Trying ../data/flagsPos.txt" << std::endl;
		fichierLecture.open("../data/flagsPos.txt");
		if(!fichierLecture.is_open())
		{
			std::cout << "Erreur dans l'ouverture en lecture du fichier : dimTerrain.txt" << std::endl;
			exit(EXIT_FAILURE);
		}
 	}

 	std::string enTete;
 	fichierLecture >> enTete >> enTete >> enTete >> enTete >> enTete;

 	int id;
 	int left, width, PosX, PosY;

 	do
 	{
 		fichierLecture >> id >> left >> width >> PosX >> PosY;
 	}
 	while(id != idTerrain);
 	
 	rectSourceSprite.left = left;
	rectSourceSprite.width = width;
	// Terrain désactiver
	if(id == 8)
	{
		rectSourceSprite.top = 457;
		rectSourceSprite.height = 24; 
	}
	else
	{
		rectSourceSprite.top = 487;
		rectSourceSprite.height = 20;
	}

	spriteFlag.setTextureRect(rectSourceSprite);
	spriteFlag.setPosition(sf::Vector2f(-((256*2.85)-900)/2.0 + 2.85*PosX, PosY*2.85));

 	fichierLecture.close();
}

void sfmlMenu::animationStart()
{
	if(clock.getElapsedTime().asSeconds() > 0.03f)
	{
		//Si on n'est pas arrivé tout à droite
		if(rectSourceSprite.left != (19-1)*600) /* la position du bord 
			haut-gauche du rectSourceSprite lorsqu'on est tout à droite */
		{
			rectSourceSprite.left += 600;
		}
		//Sinon, on revient au début
		else
			rectSourceSprite.left = 0;

		clock.restart();
	}
	spriteHome.setTextureRect(rectSourceSprite);
}

void sfmlMenu::initHomeSelect()
{
	//Chargement de la texture du menu principale
	if(!texture.loadFromFile("./data/modeSelectBackground.png"))
	{
		std::cout << "Trying ../data/modeSelectBackground.png" << std::endl;
		texture.loadFromFile("../data/modeSelectBackground.png");
	}

	// Initialisation pour la sprite Home
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = 600;
	rectSourceSprite.height = 338;

	spriteHome.setTexture(texture);
	spriteHome.setTextureRect(rectSourceSprite);

	sf::Image img;
	if(!img.loadFromFile("./data/modeSelect.png"))
	{
		std::cout << "Trying ../data/modeSelect.png" << std::endl;
		img.loadFromFile("../data/modeSelect.png");
	}
    // recupere et supprime la couleur de fond de l'image
    img.createMaskFromColor(img.getPixel(1,1));

    textureSelect.loadFromImage(img);
	// Initialisation pour la sprite Home
	sf::IntRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 1850;
	rect.height = 1080;

	spriteMode.setTexture(textureSelect);
	spriteMode.setTextureRect(rect);
	spriteMode.setScale(0.51f, 0.51f);
}

void sfmlMenu::animationSuperBattle()
{
	sf::IntRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 1850;
	rect.height = 1080;
	spriteMode.setTextureRect(rect);
}

void sfmlMenu::animationVersusBattle()
{
	sf::IntRect rect;
	rect.left = 1850;
	rect.top = 0;
	rect.width = 1850;
	rect.height = 1080;
	spriteMode.setTextureRect(rect);
}

void sfmlMenu::update(sf::RenderTarget &render)
{
	render.draw(backgroundColor);
	render.draw(spriteBackground);
	animationSelect();
	render.draw(spriteFlag);
}

void sfmlMenu::initRestartSelect()
{
	//Chargement de la texture du menu restart
	if(!texture.loadFromFile("./data/restartSelect.png"))
	{
		std::cout << "Trying ../data/restartSelect.png" << std::endl;
		texture.loadFromFile("../data/restartSelect.png");
	}

	// Initialisation pour la sprite Home
	rectSourceSprite.left = 0;
	rectSourceSprite.top = 0;
	rectSourceSprite.width = 1920;
	rectSourceSprite.height = 1080;

	spriteBackground.setTexture(texture);
	spriteBackground.setTextureRect(rectSourceSprite);
	spriteBackground.setScale(0.51f, 0.51f);
	spriteBackground.setPosition(0,0);
	spriteBackground.move(-50,0);
}

void sfmlMenu::animationRestartSelect()
{
	sf::IntRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 1920;
	rect.height = 1080;
	spriteBackground.setTextureRect(rect);
}
void sfmlMenu::animationHomeSelect()
{
	sf::IntRect rect;
	rect.left = 1920;
	rect.top = 0;
	rect.width = 1920;
	rect.height = 1080;
	spriteBackground.setTextureRect(rect);
}
void sfmlMenu::dessineBackground(sf::RenderTarget &render)
{
	render.draw(spriteHome);
}
void sfmlMenu::dessineHome(sf::RenderTarget &render)
{
	render.draw(spriteHome);
}
void sfmlMenu::dessineMode(sf::RenderTarget &render)
{
	render.draw(spriteMode);
}