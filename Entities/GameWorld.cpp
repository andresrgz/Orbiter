/*
 * GameWorld.cpp
 *
 *  Created on: Dec 3, 2015
 *      Author: andres
 */

#include "GameWorld.h"

GameWorld::GameWorld(vector<Entity*>* entities) {
	srand(time(NULL));
	this->entities = entities;
	this->asteroidCount = 0;
	this->maxAsteroids = 5;

	this->screenW = VideoMode::getDesktopMode().width;
	this->screenH = VideoMode::getDesktopMode().height;
}

GameWorld::~GameWorld() {
	// TODO Auto-generated destructor stub
}

void GameWorld::spawnAsteroids()
{
	if(asteroidCount < maxAsteroids)
	{
		/*Position*/
		float posX, posY;

		//If true posX:[0,screenW] and Y is either 0 or screenH
		//If false posY:[0,screenY] and X is either 0 or screenW
		if(rand()%2)
		{
			posX = rand()%screenW;
			posY = screenH*(rand()%2);
		}
		else
		{
			posY = rand()%screenH;
			posX = screenW*(rand()%2);
		}

		/*Scale size*/
		float scale = (1.f/(rand()%4 + 2.f));

		/*Asteroid image*/
		float asteroidNum = rand()%4 + 1;
		ostringstream path;
		path << "assets/asteroid_" << asteroidNum << ".png";

		/*Force*/
		float forceX = pow(-1, rand()%2)*(rand()%500 + 300);
		float forceY = pow(-1, rand()%2)*(rand()%500 + 300);

		//Makes sure that the force is always applied inside the screen
		if((posX >= (float)screenW/2.0f && forceX >= 0) || (posX < (float)screenW/2.0f && forceX < 0) )
			forceX*=-1;
		if((posY >= (float)screenW/2.0f && forceY >= 0) || (posY < (float)screenW/2.0f && forceY < 0))
			forceY*=-1;

		b2Vec2 force(forceX, forceY);

		Asteroid* asteroid = new Asteroid(posX, posY, scale, path.str());
		asteroid->getBody()->ApplyForce(force, asteroid->getBody()->GetWorldCenter(), true);

		entities->push_back(asteroid);
		asteroidCount++;
	}
}
