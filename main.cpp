/*
 * main.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: andres
 */
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#include "Entities/GameWorld.h"
#include "Entities/Entity.h"
#include "Entities/Planet.h"
#include "Entities/Asteroid.h"
#include "Entities/Player.h"
#include "Entities/PlanetContactListener.h"

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

	PlanetContactListener planetContactListener;
	world.SetContactListener(&planetContactListener);

	//Background
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets/background.png");
	Sprite background;
	background.setTexture(backgroundTexture);

	//Menu


	//Entities
	vector<Entity*> entities;
	Entity::setContext(&world, &window, &entities);
	GameWorld gameWorld(&entities);

	//Planets
	float planetX = window.getSize().x/2.f;
	float planetY = window.getSize().y/2.f;
	entities.push_back(new Planet(planetX, planetY, 0.25f, "assets/new_planet.png"));
	((Planet*)entities[0])->setGravityForce(1000.0f);

	//Player
	entities.push_back(new Player(planetX, planetY - 100, 1.0f, "assets/player/stand_right.png"));

	bool paused = false;
	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				paused = !paused;
		}
		if(!paused)
		{
			//Logic
			world.Step(1/60.f, 8, 3);
			gameWorld.spawnAsteroids();
			for(unsigned int i = 0; i < entities.size(); i++)
			{
				if(entities[i]->getType() == "Planet")
					((Planet*)entities[i])->step();
				else if(entities[i]->getType() == "Player")
					((Player*)entities[i])->move();
			}
		}
		//Drawing
		window.clear(Color::Black);
		window.draw(background);
		for(unsigned int i = 0; i < entities.size(); i++)
			entities[i]->draw();
		window.display();
	}

	return 0;
}




