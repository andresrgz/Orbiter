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

class Asteroid : public Entity{
public:
	Asteroid(float x, float y, float scale, string texturePath);
	virtual ~Asteroid();
};

#endif /* ENTITIES_ASTEROID_H_ */
