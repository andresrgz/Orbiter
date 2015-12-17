/*
 * Player.h
 *
 *  Created on: Nov 21, 2015
 *      Author: andres
 */

#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "Entity.h"
#include "Planet.h"
#include "Bullet.h"

class Planet;

class Player : public Entity{
public:
	bool jumpEnabled, gunEnabled;
	float movementForce, maxSpeed, jumpForce;
	float facingAngle, jumpAngle, gunAngle, referenceAngle, relativeAngle;
	b2Vec2 movementVec, jumpVec;
	Planet* currentPlanet;
	Player(float x, float y, float scale, string textureKey);
	virtual ~Player();
	void setCurrentPlanet();
	void setGunAngle(float relativeAngle);
	float getGunAngle();
	b2Vec2 getGunPosition();
	void calibrate();
	void move();
	void shoot();
};

#endif /* ENTITIES_PLAYER_H_ */
