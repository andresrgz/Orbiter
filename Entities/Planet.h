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
	float gravityForce;
	Planet(float gravityForce);
	virtual ~Planet();
	void configure(float x, float y, string texturePath);
	float getGravityForce();
};

#endif /* ENTITIES_PLANET_H_ */
