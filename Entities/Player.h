/*
 * Player.h
 *
 *  Created on: Nov 21, 2015
 *      Author: andres
 */

#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include <map>
#include <sstream>
#include "Entity.h"
#include "Planet.h"

class Planet;

class Player : public Entity{
public:
	int numFootContacts, frames, animationRate;
	unsigned int currentTexture;
	float maxSpeed, jumpForce;
	string state;
	b2Vec2 speedVec, jumpVec;
	b2Fixture* footSensorFixture;
	map<string, vector<Texture*> > textures;
	Planet* currentPlanet;
	Player(float x, float y, float scale, string texturePath);
	virtual ~Player();
	void initTextures();
	void loadMultiTextures(string state, string path, int count);
	void setCurrentPlanet();
	void calibrate();
	void move();
};

#endif /* ENTITIES_PLAYER_H_ */
