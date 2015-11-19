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

using namespace std;
using namespace sf;

const float SCALE = 30.0;

int main()
{
	//Window settings
	RenderWindow window(VideoMode(800,600), "Orbiter");
	window.setFramerateLimit(60);

	//World settings
	b2Vec2 gravity(0.0f,9.8f);
	b2World world(gravity);

	Planet planet(&world, &window);
	planet.configure(window.getSize().x/2.f, window.getSize().y/2.f, 10.f, 100.f, "assets/planets/Planet-8.png");
	planet.setScale(0.35f, 0.35f);

	Asteroid asteroid(&world, &window);
	asteroid.configure(350.f, 0.f, 10.f, 10.f, "assets/asteroid.png");

	while(window.isOpen())
	{
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
		}

		world.Step(1/60.f, 8, 3);

		window.clear(Color::Black);
		planet.draw();
		asteroid.draw();
		window.display();
	}

	return 0;
}




