/*
 * Entity.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: andres
 */

#include "Entity.h"

const float SCALE = 30.0;

Entity::Entity(b2World* world, RenderWindow* window) {
	this->type = "Entity";
	this->world = world;
	this->window = window;
	this->body = NULL;
	this->drawReady = false;
}

Entity::~Entity()
{

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
