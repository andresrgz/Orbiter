/*
 * Asteroid.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Asteroid.h"

const float SCALE = 30.0;

Asteroid::Asteroid(b2World* world, RenderWindow* window) : Entity(world, window){
	this->type = "Asteroid";

}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::configure(float x, float y, float mass, float size, string texturePath)
{
	x/=SCALE;
	y/=SCALE;
	size/=SCALE;

	//Properties
	this->mass = mass;

	//Texture loading
	texture.loadFromFile(texturePath);

	//Body definitions
	bodyDef.position = b2Vec2(x, y);
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape planetShape;
	planetShape.m_radius = (texture.getSize().x/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &planetShape;
	body->CreateFixture(&fixtureDef);

	drawReady = true;
}

