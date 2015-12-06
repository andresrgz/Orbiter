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
#include <list>
#include <math.h>
#include <sstream>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity : public Sprite{
private:
	static void initTextures();
	static void addTexture(string textureKey, string path);
	static void addTextures(string textureKey, string path, int count);
protected:
	static b2World* world;
	static RenderWindow* window;
	static list<Entity*>* entities;
	static map<string, vector<Texture*> > textures;
public:
	string type;
	string textureKey;
	unsigned int animationRate, frames, currentTexture;
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	Entity(float x, float y, float scale, string textureKey);
	virtual ~Entity();
	static void setContext(b2World* worldPtr, RenderWindow* windowPtr, list<Entity*>* entitiesPtr);
	string getType();
	b2Body* getBody();
	void draw();
};

#endif /* ENTITY_H_ */
