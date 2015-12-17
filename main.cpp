/*
 * main.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: andres
 */
#include <iostream>
#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#include "Entities/Entity.h"
#include "Entities/Planet.h"
#include "Entities/Asteroid.h"
#include "Entities/GameContactListener.h"
#include "Entities/Player.h"
#include "GameWorld.h"
#include "Scene.h"
#include "GUI.h"

using namespace std;
using namespace sf;

int main()
{
	//Window settings
	RenderWindow window(VideoMode::getDesktopMode(), "Orbiter");
	window.setFramerateLimit(60);

	//World settings
	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);

	//Entities
	list<Entity*> entities;
	Entity::setContext(&world, &window, &entities);

	GameContactListener gameContactListener(&entities);
	world.SetContactListener(&gameContactListener);

	GameWorld gameWorld(&entities);
	Scene scene(&window, &gameWorld, &entities);
	scene.createScene(0);

	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				gameWorld.pause();
		}
		if(!gameWorld.paused)
		{
			world.Step(1/60.f, 8, 3);
			scene.step();
		}
		window.clear(Color::Black);
		scene.draw();
		window.display();
	}

	return 0;
}




