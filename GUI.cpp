/*
 * GUI.cpp
 *
 *  Created on: Dec 16, 2015
 *      Author: andres
 */

#include "GUI.h"

GUI::GUI(RenderWindow* window, GameWorld* world) {
	this->window = window;
	this->world = world;
	this->player = player;
	this->font.loadFromFile("assets/slkscr.ttf");
	this->commando.loadFromFile("assets/commando.ttf");

	this->screenW = window->getView().getSize().x;
	this->screenH = window->getView().getSize().y;

	playerPoints.setFont(font);
	playerPoints.setCharacterSize(24);
	playerPoints.setColor(Color::White);
	playerPoints.setPosition(40, 80);

	hp.setFont(font);
	hp.setCharacterSize(24);
	hp.setColor(Color::White);
	hp.setPosition(40, 110);

	highscore.setFont(commando);
	highscore.setCharacterSize(24);
	highscore.setColor(Color::White);
	highscore.setString("New Highscore");
	highscore.setPosition(screenW/2.0f - 180, screenH/2.0f - 60);

	gameover.setFont(commando);
	gameover.setCharacterSize(82);
	gameover.setColor(Color::White);
	gameover.setString("Game Over");
	gameover.setPosition(screenW/2.0f - 180, screenH/2.0f - 60);
}

GUI::~GUI() {

}

void GUI::draw()
{
	for(list<Entity*>::iterator i = world->entities->begin(); i != world->entities->end(); i++)
	{
		Entity* entity = *i;
		if(entity->getType() == "Player")
		{
			player = (Player*)entity;
			break;
		}
	}

	if(!world->gameover)
	{
		int points = player->points;
		ostringstream pointsString;
		pointsString << "Points: " << points;

		int hp_value = player->hp;
		ostringstream hpString;

		ostringstream hpBars;
		for(int i = 0; i < hp_value; i++)
			hpBars << "|";
		hpString << "HP: " << hpBars.str();

		playerPoints.setString(pointsString.str());
		hp.setString(hpString.str());

		window->draw(playerPoints);
		window->draw(hp);
	}
	else
	{
		window->draw(gameover);
	}
}

