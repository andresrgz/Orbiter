/*
 * Entity.h
 *
 *  Created on: Nov 18, 2015
 *      Author: andres
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity : public Sprite{
protected:
	static b2World* world;
	static RenderWindow* window;
public:
	string type;
	Texture texture;
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	bool drawReady;
	Entity();
	virtual ~Entity();
	static void init(b2World* worldPtr, RenderWindow* windowPtr);
	b2Body* getBody();
	virtual void configure(float x, float y, string texturePath) = 0;
	void draw();
};

#endif /* ENTITY_H_ */
