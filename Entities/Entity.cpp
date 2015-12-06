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
vector<Entity*>* Entity::entities;

Entity::Entity(float x, float y, float scale, string texturePath) {
	this->type = "Entity";
	this->body = NULL;
	this->bodyDef.position = b2Vec2(x/SCALE, y/SCALE);
	this->setScale(scale, scale);

	//Animation variables
	this->frames = 0;
	this->animationRate = 5;
	this->currentTexture = 0;

	//Texture loading
	this->texture.loadFromFile(texturePath);
	this->setTexture(texture);
	this->setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);
}

Entity::~Entity()
{

}

void Entity::setContext(b2World* worldPtr, RenderWindow* windowPtr, vector<Entity*>* entitiesPtr)
{
	world = worldPtr;
	window = windowPtr;
	entities = entitiesPtr;
}

string Entity::getType()
{
	return type;
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

	cout << "X: " << this->getPosition().x << endl;
	cout << "Y: " << this->getPosition().y << endl;
}

void Entity::startAnimation()
{
	frames++;
	if(frames >= 60)
		frames = 0;

	if(frames%animationRate == 0)
		currentTexture++;

	if(currentTexture >= textures[state].size())
		currentTexture = 0;

	this->setTexture(*(textures[state][currentTexture]));
}
