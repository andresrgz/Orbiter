/*
 * Planet.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Planet.h"

const float SCALE = 30.0;

Planet::Planet(b2World* world, RenderWindow* window) : Entity(world, window){
	this->type = "Planet";
}

Planet::~Planet(){
	// TODO Auto-generated destructor stub
}

void Planet::configure(float x, float y, float mass, string texturePath)
{
	x/=SCALE;
	y/=SCALE;

	//Properties
	this->mass = mass;

	//Texture loading
	texture.loadFromFile(texturePath);

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
