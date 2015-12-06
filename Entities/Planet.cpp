/*
 * Planet.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Planet.h"

const float SCALE = 30.0;

Planet::Planet(float x, float y, float scale, string textureKey) : Entity(x, y, scale, textureKey){
	this->type = "Planet";
	this->gravityForce = 0;

	//Body definitions
	this->bodyDef.type = b2_staticBody;
	this->body = world->CreateBody(&bodyDef);

	//Shape definitions
	this->planetShape.m_radius = ((getTexture()->getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	this->fixtureDef.shape = &planetShape;
	this->body->CreateFixture(&fixtureDef);
}

Planet::~Planet(){
	// TODO Auto-generated destructor stub
}

void Planet::setGravityForce(float gravityForce)
{
	this->gravityForce = gravityForce;
}

b2Vec2 Planet::getCurrentForce(Entity* entity)
{
	//Get planet and this entity's position
	b2Vec2 planetPos = body->GetPosition();
	b2Vec2 entityPos = entity->getBody()->GetPosition();

	//Calculate distance difference
	float deltaX = entityPos.x - planetPos.x;
	float deltaY = entityPos.y - planetPos.y;
	float distanceSquared = deltaX*deltaX + deltaY*deltaY;

	//Calculate the reference angle at which gravity must be applied
	float angle = deltaX != 0 ? atan(deltaY/deltaX) : b2_pi/2.f;
	if(angle < 0)
		angle*=-1;

	//Calculate force magnitude and its components
	float forceMagnitude = gravityForce/distanceSquared;
	float forceX = forceMagnitude*cos(angle);
	float forceY = forceMagnitude*sin(angle);

	//Check and set force direction
	if(deltaX > 0)
		forceX*=-1;
	if(deltaY > 0)
		forceY*=-1;

	return b2Vec2(forceX, forceY);
}

//This function allows the planet to attract all other entities.
void Planet::step()
{
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
	{
		Entity* entity = *i;
		if(entity->getType() != this->type)
			entity->getBody()->ApplyForce(getCurrentForce(entity), entity->getBody()->GetWorldCenter(), true);
	}
}


