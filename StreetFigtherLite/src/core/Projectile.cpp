#include "Projectile.h"

void Projectile::init(unsigned int width)
{
	taille = width;
	vivant = false;
}

void Projectile::miseAJourPosition(float vitesse)
{
	if(vivant)
	{
		if(regardeDroite)
			position += make_vec2(vitesse, 0);
		else
			position += make_vec2(-vitesse, 0);
	}
}