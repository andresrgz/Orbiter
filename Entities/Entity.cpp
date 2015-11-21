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

Entity::Entity(float x, float y, float scale, string texturePath) {
	this->type = "Entity";
	this->body = NULL;
	this->bodyDef.position = b2Vec2(x/SCALE, y/SCALE);
	this->setScale(scale, scale);

	//Texture loading
	texture.loadFromFile(texturePath);
	this->setTexture(texture);
	this->setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);
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
	this->setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	this->setRotation(body->GetAngle()*180/b2_pi);
	window->draw(*this);
}
