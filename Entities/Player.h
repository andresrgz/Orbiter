/*
 * Player.h
 *
 *  Created on: Nov 21, 2015
 *      Author: andres
 */

#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include <map>
#include "Entity.h"
#include "Planet.h"

class Planet;

class Player : public Entity{
public:
	int numFootContacts;
	float maxSpeed, jumpForce;
	b2Vec2 speedVec, jumpVec;
	b2Fixture* footSensorFixture;
	Planet* currentPlanet;
	Player(float x, float y, float scale, string textureKey);
	virtual ~Player();
	void setCurrentPlanet();
	void calibrate();
	void move();
};

#endif /* ENTITIES_PLAYER_H_ */
