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

#include "Entities/Entity.h"
#include "Entities/Planet.h"
#include "Entities/Asteroid.h"

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
	vector<Entity*> entities;
	Entity::setContext(&world, &window, &entities);

	float planetX = window.getSize().x/2.f;
	float planetY = window.getSize().y/2.f;
	entities.push_back(new Planet(planetX, planetY, 0.25f, "assets/planets/Planet-8.png"));
	((Planet*)entities[0])->setGravityForce(500.0f);

	entities.push_back(new Asteroid(100.0f, 100.0f, 1.0f, "assets/asteroid.png"));
	entities.push_back(new Asteroid(800.0f, 700.0f, 1.0f, "assets/asteroid.png"));

	//*DELETE*
	b2Vec2 force(215.f, -15.f);
	entities[1]->getBody()->ApplyForce(force, entities[1]->getBody()->GetWorldCenter(), true);
	entities[1]->getBody()->SetAngularVelocity(10.f);

	entities[2]->getBody()->ApplyForce(force, entities[1]->getBody()->GetWorldCenter(), true);
	entities[2]->getBody()->SetAngularVelocity(-15.f);

	bool paused = false;

	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				paused = paused ? false : true;
		}

		if(!paused)
		{
			//Logic
			world.Step(1/60.f, 8, 3);
			((Asteroid*)entities[1])->step();
			((Asteroid*)entities[2])->step();

			//Drawing
			window.clear(Color::Black);
			entities[0]->draw();
			entities[1]->draw();
			entities[2]->draw();
			window.display();
		}
	}

	return 0;
}




