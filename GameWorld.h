/*
 * GameWorld.h
 *
 *  Created on: Dec 3, 2015
 *      Author: andres
 */

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include "Entities/Entity.h"
#include "Entities/Asteroid.h"

class GameWorld {
public:
	int asteroidCount, maxAsteroids;
	float screenW, screenH;
	vector<Entity*>* entities;
	GameWorld(vector<Entity*>* entities);
	virtual ~GameWorld();
	void spawnAsteroids();
	void clean();
};

#endif /* GAMEWORLD_H_ */
