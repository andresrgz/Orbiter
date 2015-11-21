/*
 * Planet.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Planet.h"

const float SCALE = 30.0;

Planet::Planet(float x, float y, float scale, string texturePath) : Entity(x, y, scale, texturePath){
	this->type = "Planet";
	this->gravityForce = 0;

	//Body definitions
	bodyDef.type = b2_staticBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape planetShape;
	planetShape.m_radius = ((texture.getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &planetShape;
	body->CreateFixture(&fixtureDef);
}

Planet::~Planet(){
	// TODO Auto-generated destructor stub
}

void Planet::setGravityForce(float gravityForce)
{
	this->gravityForce = gravityForce;
}

float Planet::getGravityForce()
{
	return gravityForce;
}
