/*
 * Asteroid.h
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#ifndef ENTITIES_ASTEROID_H_
#define ENTITIES_ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity{
public:
	Asteroid(b2World* world, RenderWindow* window);
	virtual ~Asteroid();
	void configure(float x, float y, float mass, float size, string texturePath);
};

#endif /* ENTITIES_ASTEROID_H_ */
