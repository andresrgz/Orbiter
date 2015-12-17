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

	GameContactListener gameContactListener;
	world.SetContactListener(&gameContactListener);

	//Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets/background.png");
	Sprite background;
	background.setTexture(backgroundTexture);

	//Entities
	list<Entity*> entities;
	Entity::setContext(&world, &window, &entities);
	GameWorld gameWorld(&entities);

	//Planets
	float planetX = window.getSize().x/2.f;
	float planetY = window.getSize().y/2.f;
	Planet* planet = new Planet(planetX, planetY, 0.25f, "Planet1");
	planet->setGravityForce(1000.0f);
	entities.push_back(planet);

	//Player
	Player* player = new Player(planetX, planetY - 100, 1.00f, "S-RIGHT");
	entities.push_back(player);

	//GUI
	GUI gui(&window, player);

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
			//Logic
			world.Step(1/60.f, 8, 3);
			gameWorld.spawnAsteroids();
			gameWorld.clean();
			for(list<Entity*>::iterator i = entities.begin(); i != entities.end(); i++)
			{
				Entity* entity = *i;
				if(entity->getType() == "Planet")
					((Planet*)entity)->step();
				else if(entity->getType() == "Player")
					((Player*)entity)->move();
			}
		}
		//Drawing
		window.clear(Color::Black);
		window.draw(background);
		for(list<Entity*>::iterator i = entities.begin(); i != entities.end(); i++)
			(*i)->draw();
		gui.draw();
		window.display();
	}

	return 0;
}




