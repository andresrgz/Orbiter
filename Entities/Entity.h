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
public:
	string type;
	float mass;
	b2World* world;
	b2Body* body;
	RenderWindow* window;
	Texture texture;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	bool drawReady;
	Entity();
	Entity(b2World* world, RenderWindow* window);
	virtual ~Entity();
	b2Body* getBody();
	virtual void configure(float x, float y, float mass, float size, string texturePath) = 0;
	void draw();

};

#endif /* ENTITY_H_ */
