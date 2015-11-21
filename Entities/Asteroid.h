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
	Asteroid(float x, float y, float scale, string texturePath);
	virtual ~Asteroid();
	void step(vector<Entity*>* entities);
};

#endif /* ENTITIES_ASTEROID_H_ */
