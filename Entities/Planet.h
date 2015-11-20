/*
 * Planet.h
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#ifndef ENTITIES_PLANET_H_
#define ENTITIES_PLANET_H_

#include "Entity.h"

class Planet : public Entity{
public:
	Planet(b2World* world, RenderWindow* window);
	virtual ~Planet();
	void configure(float x, float y, float mass, string texturePath);
};

#endif /* ENTITIES_PLANET_H_ */
