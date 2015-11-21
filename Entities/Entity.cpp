/*
 * Entity.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: andres
 */

#include "Entity.h"

const float SCALE = 30.0;

b2World* Entity::world;
RenderWindow* Entity::window;

Entity::Entity() {
	this->type = "Entity";
	this->body = NULL;
	this->drawReady = false;
}

Entity::~Entity()
{

}

void Entity::init(b2World* worldPtr, RenderWindow* windowPtr)
{
	world = worldPtr;
	window = windowPtr;
}

b2Body* Entity::getBody()
{
	return body;
}

void Entity::draw()
{
	if(drawReady){
		this->setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
		this->setRotation(body->GetAngle()*180/b2_pi);
		window->draw(*this);
	}
	else
	{
		cout << type << " has not yet been configured." << endl;
	}
}
