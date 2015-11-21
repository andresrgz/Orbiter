/*
 * Entity.h
 *
 *  Created on: Nov 18, 2015
 *      Author: andres
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include <vector>
#include <math.h>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity : public Sprite{
protected:
	static b2World* world;
	static RenderWindow* window;
	static vector<Entity*>* entities;
public:
	string type;
	Texture texture;
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	Entity(float x, float y, float scale, string texturePath);
	virtual ~Entity();
	static void setContext(b2World* worldPtr, RenderWindow* windowPtr, vector<Entity*>* entitiesPtr);
	string getType();
	b2Body* getBody();
	void draw();
};

#endif /* ENTITY_H_ */
