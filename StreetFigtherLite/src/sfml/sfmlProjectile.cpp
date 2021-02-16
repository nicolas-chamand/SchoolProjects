#include "sfmlProjectile.h"
#include <iostream>
#include <cmath>

void sfmlProjectile::init(Projectile *prjctle)
{
	projectile = prjctle;
  	sf::Image img;
	if(!img.loadFromFile("data/texture_ryu.png"))
    {
    	std::cout << "Trying ../data/texture_ryu.png" << std::endl;
    	img.loadFromFile("../data/texture_ryu.png");
    }
    // recupere et supprime la couleur de fond de l'image
    img.createMaskFromColor(img.getPixel(1,1));
    // charge la texture depuis l'image sans sa couleur de fond
    texture.loadFromImage(img);

  rectSourceSprite.left = 420;
	rectSourceSprite.top = 643;
	rectSourceSprite.width = 36;
	rectSourceSprite.height = 40;

  sprite.setTexture(texture);
	sprite.setTextureRect(rectSourceSprite);
	sprite.setScale(2.0f,2.0f);
}

void sfmlProjectile::afficher(sf::RenderTarget &render)
{
    sf::Vector2f translation;
    if(projectile->regardeDroite)
    {
      sprite.setScale(abs(sprite.getScale().x), sprite.getScale().y);
      translation = sf::Vector2f(-rectSourceSprite.width,-rectSourceSprite.height);
    }
    else
    {
      // symetrie d'axe vertical
      sprite.setScale(-1.0f * abs(sprite.getScale().x), sprite.getScale().y);
      translation = sf::Vector2f(rectSourceSprite.width,-rectSourceSprite.height);
    }
    // translation de la position de la sprite par rapport a la position du psng
    translation.x += projectile->position.x; 
    translation.y += projectile->position.y;
    sprite.setPosition(translation);
    render.draw(sprite);
    clock.restart();
}
	