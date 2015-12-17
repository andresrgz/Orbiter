/*
 * BulletContactListener.h
 *
 *  Created on: Dec 16, 2015
 *      Author: andres
 */

#ifndef ENTITIES_GAMECONTACTLISTENER_H_
#define ENTITIES_GAMECONTACTLISTENER_H_

#include "Entity.h"
#include "Asteroid.h"
#include "Bullet.h"

class GameContactListener : public b2ContactListener{
public:
	GameContactListener();
	virtual ~GameContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif /* ENTITIES_GAMECONTACTLISTENER_H_ */
