/*
 * GameWorld.h
 *
 *  Created on: Dec 3, 2015
 *      Author: andres
 */

#ifndef ENTITIES_GAMEWORLD_H_
#define ENTITIES_GAMEWORLD_H_

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Asteroid.h"

class GameWorld {
public:
	int asteroidCount, maxAsteroids;
	int screenW, screenH;
	vector<Entity*>* entities;
	GameWorld(vector<Entity*>* entities);
	virtual ~GameWorld();
	void spawnAsteroids();
};

#endif /* ENTITIES_GAMEWORLD_H_ */
