/*
 * Scene.h
 *
 *  Created on: Dec 17, 2015
 *      Author: andres
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/Planet.h"
#include "GameWorld.h"
#include "GUI.h"

class Scene {
public:
	int sceneID;
	GUI* gui;
	RenderWindow* window;
	GameWorld* world;
	list<Entity*>* entities;
	Texture backgroundTexture;
	Sprite background;
	Scene(RenderWindow* window, GameWorld* world, list<Entity*>* entities);
	virtual ~Scene();
	void createScene(int sceneID);
	void step();
	void draw();
};

#endif /* SCENE_H_ */
