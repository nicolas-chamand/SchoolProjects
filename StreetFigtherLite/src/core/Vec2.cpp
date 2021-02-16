#include "Vec2.h"
#include <cstdlib>
#include <time.h>
#include <cassert>
#include <iostream>

Vec2::Vec2() 
{
	x = 0;
	y = 0;
}

Vec2::Vec2(float newX, float newY)
{
	x = newX;
	y = newY;
}

/**
@brief Fonction: renvoie un Vec2 de coordonees (x,y)
*/
Vec2 make_vec2(float x, float y)
{
	Vec2 v;
	v.x = x;
	v.y = y;
	return v;
}

Vec2 operator+(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

Vec2 operator+=(Vec2& a, const Vec2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vec2 operator*(float a, const Vec2& b)
{
	Vec2 r;
	r.x = a * b.x;
	r.y = a * b.y;
	return r;
}

void Vec2::testregression()
{
	Vec2 v1;
	assert(v1.x == 0);
	assert(v1.y == 0); 

	srand(time(NULL));
	for(int i=0; i<10000; i++)
	{
		float x1Rand = rand()/100000.0;
		float y1Rand = rand()/100000.0;

		// Vérifie le fonctionnement du constructeur
		Vec2 v1(x1Rand, y1Rand);
		assert(v1.x == x1Rand);
		assert(v1.y == y1Rand);

		// Vérifie le fonctionnement de make_vec2
		v1 = make_vec2(x1Rand, y1Rand);
		assert(v1.x == x1Rand);
		assert(v1.y == y1Rand);

		float x2Rand = rand()/100000.0;
		float y2Rand = rand()/100000.0;

		// Vérifie le fonctionnement des opérateurs
		Vec2 v2(x2Rand, y2Rand);
		Vec2 v3;

		// Opérateur +
		v3 = v1+v2;
		assert(v3.x == x1Rand+x2Rand);
		assert(v3.y == y1Rand+y2Rand);

		// Opérateur +=
		v3 += v1;
		assert(v3.x == (x1Rand+x2Rand)+x1Rand);
		assert(v3.y == (y1Rand+y2Rand)+y1Rand);

		// Opérateur -
		v3 = v1-v2;
		assert(v3.x == x1Rand-x2Rand);
		assert(v3.y == y1Rand-y2Rand);

		// Opérateur * (avec float)
		float f = rand()/100000.0;
		v3 = f*v1;
		assert(v3.x == f*x1Rand);
		assert(v3.y == f*y1Rand);
	}

	std::cout << "Tous les tests du module Vec2 ont réussit" << std::endl;
}