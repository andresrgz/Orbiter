/*
 * GUI.h
 *
 *  Created on: Dec 16, 2015
 *      Author: andres
 */

#ifndef GUI_H_
#define GUI_H_

#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entities/Player.h"

using namespace sf;

class GUI {
public:
	float screenW, screenH;
	RenderWindow* window;
	Player* player;
	Font font, commando;
	Text playerPoints, hp, highscore, gameover;
	GUI(RenderWindow* window, Player* player);
	virtual ~GUI();
	void draw();
};

#endif /* GUI_H_ */
