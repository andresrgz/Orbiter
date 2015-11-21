/*
 * Planet.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Planet.h"

const float SCALE = 30.0;

Planet::Planet(float gravityForce){
	this->type = "Planet";
	this->gravityForce = gravityForce;
}

Planet::~Planet(){
	// TODO Auto-generated destructor stub
}

void Planet::configure(float x, float y, string texturePath)
{
	x/=SCALE;
	y/=SCALE;

	//Texture loading
	texture.loadFromFile(texturePath);
	this->setTexture(texture);
	this->setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);

	//Body definitions
	bodyDef.position = b2Vec2(x, y);
	bodyDef.type = b2_staticBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape planetShape;
	planetShape.m_radius = ((texture.getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &planetShape;
	body->CreateFixture(&fixtureDef);

	drawReady = true;
}

float Planet::getGravityForce()
{
	return gravityForce;
}
