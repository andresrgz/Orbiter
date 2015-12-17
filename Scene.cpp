/*
 * Scene.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: andres
 */

#include "Scene.h"

Scene::Scene(RenderWindow* window, GameWorld* world, list<Entity*>* entities) {
	this->sceneID = 0;
	this->window = window;
	this->world = world;
	this->entities = entities;
	this->gui = new GUI(window, world);
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::createScene(int sceneID)
{
	this->sceneID = sceneID;
	entities->clear();

	if(sceneID == 0)
	{
		//Background
		backgroundTexture.loadFromFile("assets/menu_background.png");
		background.setTexture(backgroundTexture);

		//Asteroids
		world->maxAsteroids = 8;
	}
	else if(sceneID == 1)
	{
		//Background
		backgroundTexture.loadFromFile("assets/background.png");
		background.setTexture(backgroundTexture);

		//Asteroids
		world->maxAsteroids = 100;

		//Planets
		float planetX = window->getSize().x/2.f;
		float planetY = window->getSize().y/2.f;
		Planet* planet = new Planet(planetX, planetY, 0.25f, "Planet1");
		planet->setGravityForce(1000.0f);
		entities->push_back(planet);

		//Player
		Player* player = new Player(planetX, planetY - 100, 1.00f, "S-RIGHT");
		entities->push_back(player);
	}
}

void Scene::step()
{
	world->spawnAsteroids();
	world->clean();
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
	{
		Entity* entity = *i;
		if(entity->getType() == "Planet")
			((Planet*)entity)->step();
		else if(entity->getType() == "Player")
			((Player*)entity)->move();
	}
}

void Scene::draw()
{
	window->draw(background);
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
		(*i)->draw();

	if(sceneID >= 1 && sceneID <= 3)
		gui->draw();
}
