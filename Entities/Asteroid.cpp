/*
 * Asteroid.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Asteroid.h"

const float SCALE = 30.0;

Asteroid::Asteroid(float x, float y, float scale, string textureKey) : Entity(x, y, scale, textureKey){
	this->type = "Asteroid";

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape asteroidShape;
	asteroidShape.m_radius = ((getTexture()->getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &asteroidShape;
	fixtureDef.restitution = 0.2f;
	fixtureDef.filter.categoryBits = ASTEROID;
	fixtureDef.filter.maskBits = PLAYER1 | ASTEROID | PLANET | BULLET;
	body->CreateFixture(&fixtureDef);
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}
