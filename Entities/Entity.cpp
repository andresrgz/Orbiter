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
list<Entity*>* Entity::entities;
map<string, vector<Texture*> > Entity::textures;

Entity::Entity(float x, float y, float scale, string textureKey) {
	this->type = "Entity";
	this->body = NULL;
	this->bodyDef.position = b2Vec2(x/SCALE, y/SCALE);
	this->setScale(scale, scale);

	//Animation variables
	this->frames = 0;
	this->animationRate = 5;
	this->currentTexture = 0;

	//Textures initialization
	if(textures.empty())
		initTextures();

	this->textureKey = textureKey;
	this->setTexture(*(textures[textureKey][currentTexture]));
	this->setOrigin(getTexture()->getSize().x/2, getTexture()->getSize().y/2);
}

Entity::~Entity()
{
	world->DestroyBody(body);
}

void Entity::setContext(b2World* worldPtr, RenderWindow* windowPtr, list<Entity*>* entitiesPtr)
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

void Entity::initTextures()
{
	/*Player Textures*/
	//Standing
	addTexture("S-RIGHT", "assets/player/stand_right.png");
	addTexture("S-LEFT", "assets/player/stand_left.png");

	//Running
	addTextures("R-RIGHT", "assets/player/run_right_", 8);
	addTextures("R-LEFT", "assets/player/run_left_", 8);

	/*Planet Textures*/
	addTexture("Planet1", "assets/new_planet.png");

	/*Asteroid Textures*/
	addTexture("Asteroid1", "assets/asteroid_1.png");
	addTexture("Asteroid2", "assets/asteroid_2.png");
	addTexture("Asteroid3", "assets/asteroid_3.png");
	addTexture("Asteroid4", "assets/asteroid_4.png");

	/*Bullets*/
	addTexture("Bullet", "assets/bullet.png");
}

void Entity::addTexture(string textureKey, string path)
{
	textures[textureKey].push_back(new Texture());
	textures[textureKey][0]->loadFromFile(path);
}

void Entity::addTextures(string textureKey, string path, int count)
{
	ostringstream currentPath;
	for(int i = 1; i <= count; i++)
	{
		textures[textureKey].push_back(new Texture());

		currentPath << path << i << ".png";
		textures[textureKey][i-1]->loadFromFile(currentPath.str());

		currentPath.str("");
		currentPath.clear();
	}
}

void Entity::draw()
{
	frames++;
	if(frames%animationRate == 0)
	{
		currentTexture++;
		frames = 0;
	}

	if(currentTexture >= textures[textureKey].size())
		currentTexture = 0;

	this->setTexture(*(textures[textureKey][currentTexture]));
	this->setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
	this->setRotation(body->GetAngle()*180/b2_pi);
	window->draw(*this);
}
