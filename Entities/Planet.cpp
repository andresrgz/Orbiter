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

//This function allows the planet to attract all other entities.
void Planet::step()
{
	for(unsigned int i = 0; i < entities->size(); i++)
	{
		Entity* entity = entities->at(i);
		if(entity->getType() != "Planet")
		{
			//Get planet's and this entity's positions
			b2Vec2 planetPos = body->GetPosition();
			b2Vec2 entityPos = entity->getBody()->GetPosition();

			//Calculate distance difference
			float deltaX = entityPos.x - planetPos.x;
			float deltaY = entityPos.y - planetPos.y;

			//Calculate angle
			float angle = deltaX != 0 ? atan(deltaY/deltaX) : b2_pi/2.f;
			if(angle < 0)
				angle*=-1;

			//Calculate force magnitude
			float distance = deltaX*deltaX + deltaY*deltaY;
			float forceMagnitude = (getGravityForce())/distance;
			float forceX = forceMagnitude*cos(angle);
			float forceY = forceMagnitude*sin(angle);

			//Check and set force direction
			if(deltaX > 0)
				forceX*=-1;
			if(deltaY > 0)
				forceY*=-1;

			//Apply force
			b2Vec2 gravityForce(forceX, forceY);
			entity->getBody()->ApplyForce(gravityForce, entity->getBody()->GetWorldCenter(), true);
		}
	}
}
