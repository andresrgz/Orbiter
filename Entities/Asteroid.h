/*
 * Asteroid.h
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#ifndef ENTITIES_ASTEROID_H_
#define ENTITIES_ASTEROID_H_

#include "Entity.h"
#include "Planet.h"
#include <math.h>
#include <vector>

class Asteroid : public Entity{
public:
	Asteroid(b2World* world, RenderWindow* window);
	virtual ~Asteroid();
	void configure(float x, float y, string texturePath);
	void step(vector<Entity*>* entities);
};

#endif /* ENTITIES_ASTEROID_H_ */
