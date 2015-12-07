/*
 * Bullet.h
 *
 *  Created on: Dec 6, 2015
 *      Author: andres
 */

#ifndef ENTITIES_BULLET_H_
#define ENTITIES_BULLET_H_

#include <Box2D/Box2D.h>
#include "Entity.h"

class Bullet : public Entity{
public:
	Bullet(float x, float y, float scale, string textureKey);
	virtual ~Bullet();
};

#endif /* ENTITIES_BULLET_H_ */
