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
#include "Player.h"

class Player;

class Bullet : public Entity{
public:
	Player* owner;
	float bulletForce;
	Bullet(Player* owner);
	void setBulletForce(float bulletForce);
	void spawn();
	virtual ~Bullet();
};

#endif /* ENTITIES_BULLET_H_ */
