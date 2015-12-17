/*
 * GameWorld.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: andres
 */

#include "GameWorld.h"

GameWorld::GameWorld(list<Entity*>* entities) {
	srand(time(NULL));
	this->entities = entities;
	this->gameover = false;
	this->gameStarted = false;
	this->paused = false;
	this->asteroidCount = 0;
	this->maxAsteroids = 0;

	this->screenW = VideoMode::getDesktopMode().width;
	this->screenH = VideoMode::getDesktopMode().height;
}

GameWorld::~GameWorld() {
	// TODO Auto-generated destructor stub
}

void GameWorld::pause()
{
	if(gameStarted && !gameover)
	{
		paused = !paused;
		Entity::paused = !Entity::paused;
	}
}

void GameWorld::spawnAsteroids()
{
	if(asteroidCount < maxAsteroids && !gameover)
	{
		/*Position*/
		float posX, posY;

		//If true posX:[0,screenW] and Y is either 0 or screenH
		//If false posY:[0,screenY] and X is either 0 or screenW
		if(rand()%2)
		{
			posX = rand()%((int)screenW);
			posY = screenH*(rand()%2);
		}
		else
		{
			posY = rand()%((int)screenH);
			posX = screenW*(rand()%2);
		}

		/*Scale size*/
		float scale = (1.f/(rand()%4 + 2.f));

		/*Asteroid image*/
		float asteroidNum = rand()%4 + 1;
		ostringstream textureKey;
		textureKey << "Asteroid" << asteroidNum;

		/*Force*/
		float forceX = pow(-1, rand()%2)*(rand()%100 + 10);
		float forceY = pow(-1, rand()%2)*(rand()%100 + 10);

		//Makes sure that the force is always applied into the screen
		if((posX >= screenW/2.0f && forceX >= 0) || (posX < screenW/2.0f && forceX < 0) )
			forceX*=-1;
		if((posY >= screenH/2.0f && forceY >= 0) || (posY < screenH/2.0f && forceY < 0))
			forceY*=-1;

		b2Vec2 force(forceX, forceY);

		Asteroid* asteroid = new Asteroid(posX, posY, scale, textureKey.str());
		asteroid->getBody()->ApplyForce(force, asteroid->getBody()->GetWorldCenter(), true);

		entities->push_back(asteroid);
		asteroidCount++;
	}
}

void GameWorld::clean()
{
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
	{
		Entity* entity = *i;

		if(entity->getType() == "Asteroid" || entity->getType() == "Bullet")
		{
			float posX = entity->getPosition().x;
			float posY = entity->getPosition().y;

			if(posX < 0)
				posX*=-1;

			if(posY < 0)
				posY*=-1;

			if(posX > screenW + 1000 || posY > screenH + 1000)
				entity->deleteEntity();
		}


		if(entity->getType() == "Player")
		{
			if(((Player*)entity)->hp == 0)
			{
				entity->deleteEntity();
				gameover = true;
			}
		}

		if(entity->deleteFlag)
		{
			if(entity->getType() == "Asteroid")
				asteroidCount--;

			entities->erase(i++);
			delete entity;
		}

	}
}
