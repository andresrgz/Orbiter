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

class Player : public Entity{
public:
	float facingAngle;
	float speed, jumpForce;
	b2Vec2 speedVec, jumpVec;
	map<string, Texture> textures;
	Player(float x, float y, float scale, string texturePath);
	virtual ~Player();
	void setFacingAngle(float facingAngle);
	void setJumpVector(float deltaX, float deltaY, float angle);
	float getFacingAngle();
	void move();
};

#endif /* ENTITIES_PLAYER_H_ */
