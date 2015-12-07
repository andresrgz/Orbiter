/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: andres
 */

#include "Bullet.h"

const float SCALE = 30.0;

Bullet::Bullet(float x, float y, float scale, string textureKey) : Entity(x, y, scale, textureKey) {
	this->type = "Bullet";

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2PolygonShape bulletShape;
	float sizeX = (getTexture()->getSize().x/SCALE)/2;
	float sizeY = (getTexture()->getSize().y/SCALE)/2;
	bulletShape.SetAsBox(sizeX, sizeY);

	//Fixture definitions
	fixtureDef.shape = &bulletShape;
	body->CreateFixture(&fixtureDef);
}

Bullet::~Bullet() {

}

