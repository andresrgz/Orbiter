/*
 * main.cpp
 *
 *  Created on: Nov 10, 2015
 *      Author: andres
 */
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Entities/Entity.h"
#include "Entities/Planet.h"
#include "Entities/Asteroid.h"
#include <vector>

using namespace std;
using namespace sf;

const float SCALE = 30.0;

int main()
{
	//Window settings
	RenderWindow window(VideoMode(800,600), "Orbiter");
	window.setFramerateLimit(60);

	//World settings
	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);

	vector<Entity*> entities;

	entities.push_back(new Planet(&world, &window));
	entities[0]->setScale(0.15f, 0.15f);
	entities[0]->configure(window.getSize().x/2.f, window.getSize().y/2.f, 10000000000.f, "assets/planets/Planet-8.png");

	entities.push_back(new Asteroid(&world, &window));
	entities[1]->configure(0.f, 0.f, 100.f, "assets/asteroid.png");

	b2Vec2 force(0.25f, 0.f);
	entities[1]->getBody()->ApplyForce(force, entities[1]->getBody()->GetWorldCenter(), false);

	bool paused = false;

	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
			{
				paused = paused ? false : true;
			}
		}

		if(!paused)
		{
			world.Step(1/60.f, 8, 3);
			((Asteroid*)entities[1])->step(&entities);
			entities[1]->getBody()->ApplyForce(force, entities[1]->getBody()->GetWorldCenter(), false);

			window.clear(Color::Black);
			entities[0]->draw();
			entities[1]->draw();
			window.display();
		}
	}

	return 0;
}




