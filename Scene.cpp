/*
 * Scene.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: andres
 */

#include "Scene.h"

Scene::Scene(RenderWindow* window, GameWorld* world, list<Entity*>* entities) {
	this->sceneID = 0;
	this->window = window;
	this->world = world;
	this->lastTime = 0;
	this->entities = entities;
	this->gui = new GUI(window, world);
	this->arrowIndex = 0;

	this->screenW = window->getView().getSize().x;
	this->screenH = window->getView().getSize().y;

	this->slkscr.loadFromFile("assets/slkscr.ttf");
	this->commando.loadFromFile("assets/commando.ttf");

	arrowTexture.loadFromFile("assets/arrow.png");
	arrow.setTexture(arrowTexture);

	logo.setFont(commando);
	logo.setCharacterSize(128);
	logo.setColor(Color::White);
	logo.setString("Orbiter");
	logo.setPosition(100, 100.f);

	start.setFont(slkscr);
	start.setCharacterSize(32);
	start.setColor(Color::White);
	start.setString("Start game");
	start.setPosition(120, screenH/2.0f - 100);

	highscores.setFont(slkscr);
	highscores.setCharacterSize(32);
	highscores.setColor(Color::White);
	highscores.setString("Instructions");
	highscores.setPosition(120, screenH/2.0f - 50);

	quit.setFont(slkscr);
	quit.setCharacterSize(32);
	quit.setColor(Color::White);
	quit.setString("Quit");
	quit.setPosition(120, screenH/2.0f);

	howTo.setFont(slkscr);
	howTo.setCharacterSize(64);
	howTo.setColor(Color::White);
	howTo.setString("How to Play");
	howTo.setPosition(screenW/2.0f - 240, 100);

	String instructionsText = "1. Press Space to shoot\n\n2. Press W to jump\n\n3. Shoot asteroids and survive!";

	instructions.setFont(slkscr);
	instructions.setCharacterSize(32);
	instructions.setColor(Color::White);
	instructions.setString(instructionsText);
	instructions.setPosition(screenW/2.0f - 300, 300);

	levelSelection.setFont(slkscr);
	levelSelection.setCharacterSize(64);
	levelSelection.setColor(Color::White);
	levelSelection.setString("Level Selection");
	levelSelection.setPosition(100, 100.f);

	level1.setFont(slkscr);
	level1.setCharacterSize(32);
	level1.setColor(Color::White);
	level1.setString("Level 1");
	level1.setPosition(120, screenH/2.0f - 100);

	level2.setFont(slkscr);
	level2.setCharacterSize(32);
	level2.setColor(Color::White);
	level2.setString("Level 2");
	level2.setPosition(120, screenH/2.0f - 50);

	level3.setFont(slkscr);
	level3.setCharacterSize(32);
	level3.setColor(Color::White);
	level3.setString("Level 3");
	level3.setPosition(120, screenH/2.0f);
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::createScene(int sceneID)
{
	this->sceneID = sceneID;

	if(sceneID == 0)
	{
		//Background
		backgroundTexture.loadFromFile("assets/menu_background.png");
		background.setTexture(backgroundTexture);

		//Asteroids
		world->maxAsteroids = 8;
	}
	else if(sceneID == 3)
	{
		for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
			(*i)->deleteEntity();

		//Background
		backgroundTexture.loadFromFile("assets/background.png");
		background.setTexture(backgroundTexture);

		//Asteroids
		world->maxAsteroids = 5;

		//Planets
		float planetX = window->getSize().x/2.f;
		float planetY = window->getSize().y/2.f;
		Planet* planet = new Planet(planetX, planetY, 0.25f, "Planet1");
		planet->setGravityForce(1000.0f);
		entities->push_back(planet);

		//Player
		Player* player = new Player(planetX, planetY - 100, 1.00f, "S-RIGHT");
		entities->push_back(player);
	}
	else if(sceneID == 4)
	{
		for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
			(*i)->deleteEntity();

		//Background
		backgroundTexture.loadFromFile("assets/background.png");
		background.setTexture(backgroundTexture);

		//Asteroids
		world->maxAsteroids = 5;

		//Planets
		float planetX = window->getSize().x/2.f;
		float planetY = window->getSize().y/2.f;
		Planet* planet = new Planet(planetX - 200, planetY, 0.25f, "Planet1");
		planet->setGravityForce(1000.0f);
		entities->push_back(planet);

		Planet* planet2 = new Planet(planetX + 200, planetY, 0.25f, "Planet1");
		planet2->setGravityForce(1000.0f);
		entities->push_back(planet2);

		//Player
		Player* player = new Player(planetX, planetY - 100, 1.00f, "S-RIGHT");
		entities->push_back(player);
	}
	else if(sceneID == 5)
	{
		for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
			(*i)->deleteEntity();

		//Background
		backgroundTexture.loadFromFile("assets/background.png");
		background.setTexture(backgroundTexture);

		//Asteroids
		world->maxAsteroids = 8;

		//Planets
		Planet* planet = new Planet(400, 400, 0.25f, "Planet1");
		planet->setGravityForce(1000.0f);
		entities->push_back(planet);

		Planet* planet2 = new Planet(600, 600, 0.20f, "Planet1");
		planet2->setGravityForce(700.0f);
		entities->push_back(planet2);

		Planet* planet3 = new Planet(1000, 300, 0.5f, "Planet1");
		planet3->setGravityForce(1200.0f);
		entities->push_back(planet3);

		//Player
		Player* player = new Player(400, 400, 1.00f, "S-RIGHT");
		entities->push_back(player);
	}
}

void Scene::step()
{
	world->spawnAsteroids();
	world->clean();
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
	{
		Entity* entity = *i;
		if(entity->getType() == "Planet")
			((Planet*)entity)->step();
		else if(entity->getType() == "Player")
			((Player*)entity)->move();
	}
}

void Scene::menuInput()
{
	int arrowX = 70;

	if(clock.getElapsedTime().asMilliseconds() - lastTime >= 150)
	{
		if(Keyboard::isKeyPressed(Keyboard::W))
		{
			if(arrowIndex > 0)
				arrowIndex--;
			lastTime = clock.getElapsedTime().asMilliseconds();
		}
		else if(Keyboard::isKeyPressed(Keyboard::S))
		{
			if(arrowIndex < 2)
				arrowIndex++;
			lastTime = clock.getElapsedTime().asMilliseconds();
		}
	}

	if(sceneID == 0)
	{
		switch(arrowIndex)
		{
		case 0:
			arrow.setPosition(arrowX, start.getPosition().y);
			if(Keyboard::isKeyPressed(Keyboard::Space))
			{
				createScene(1);
				world->gameStarted = true;
				lastTime = clock.getElapsedTime().asMilliseconds();
			}
			break;
		case 1:
			arrow.setPosition(arrowX, highscores.getPosition().y);
			if(Keyboard::isKeyPressed(Keyboard::Space))
				createScene(2);
			break;
		case 2:
			arrow.setPosition(arrowX, quit.getPosition().y);
			if(Keyboard::isKeyPressed(Keyboard::Space))
				window->close();
			break;
		}
	}
	else if(sceneID == 1)
	{
		if(clock.getElapsedTime().asMilliseconds() - lastTime >= 150)
		{
			switch(arrowIndex)
			{
			case 0:
				arrow.setPosition(arrowX, level1.getPosition().y);
				if(Keyboard::isKeyPressed(Keyboard::Space))
				{
					createScene(3);
					world->gameStarted = true;
				}
				break;
			case 1:
				arrow.setPosition(arrowX, level2.getPosition().y);
				if(Keyboard::isKeyPressed(Keyboard::Space))
				{
					createScene(4);
					world->gameStarted = true;
				}
				break;
			case 2:
				arrow.setPosition(arrowX, level3.getPosition().y);
				if(Keyboard::isKeyPressed(Keyboard::Space))
				{
					createScene(5);
					world->gameStarted = true;
				}
				break;
			}
		}
	}
}

void Scene::draw()
{
	window->draw(background);
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
		(*i)->draw();

	if(sceneID == 0)
	{
		menuInput();
		window->draw(arrow);
		window->draw(logo);
		window->draw(start);
		window->draw(highscores);
		window->draw(quit);
	}
	else if(sceneID == 1)
	{
		menuInput();
		window->draw(arrow);
		window->draw(levelSelection);
		window->draw(level1);
		window->draw(level2);
		window->draw(level3);

		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			createScene(0);
			arrowIndex = 0;
		}
	}
	else if(sceneID == 2)
	{
		window->draw(howTo);
		window->draw(instructions);

		if(Keyboard::isKeyPressed(Keyboard::Escape))
			createScene(0);
	}
	else if(sceneID >= 3 && sceneID <= 5)
	{
		gui->draw();
		if(world->gameover)
		{
			if(Keyboard::isKeyPressed(Keyboard::Escape))
			{
				world->gameover = false;
				world->gameStarted = false;
			}

		}
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
				(*i)->deleteEntity();
			createScene(0);
			arrowIndex = 0;
		}
	}
}
