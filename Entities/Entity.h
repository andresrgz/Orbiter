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

enum _entityCategory{
	PLAYER1 = 0x0001,
	PLANET = 0x0002,
	ASTEROID = 0x0004,
	BULLET = 0x0008,
};

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
	static bool paused;
	string type;
	string textureKey;
	unsigned int animationRate, frames, currentTexture;
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	bool deleteFlag;
	Entity(float x, float y, float scale, string textureKey);
	virtual ~Entity();
	void deleteEntity();
	static void setContext(b2World* worldPtr, RenderWindow* windowPtr, list<Entity*>* entitiesPtr);
	string getType();
	b2Body* getBody();
	void draw();
};

#endif /* ENTITY_H_ */
