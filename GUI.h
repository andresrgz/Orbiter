/*
 * GUI.h
 *
 *  Created on: Dec 16, 2015
 *      Author: andres
 */

#ifndef GUI_H_
#define GUI_H_

#include <sstream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entities/Player.h"
#include "GameWorld.h"

using namespace sf;

class GUI {
public:
	vector<int> scores;
	float screenW, screenH;
	RenderWindow* window;
	GameWorld* world;
	Player* player;
	Font font, commando;
	Text playerPoints, hp, highscore, gameover;
	GUI(RenderWindow* window, GameWorld* world);
	virtual ~GUI();
	void draw();
	void readScores();
};

#endif /* GUI_H_ */
