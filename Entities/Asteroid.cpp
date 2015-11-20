/*
 * Asteroid.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Asteroid.h"

const float SCALE = 30.0;
const float G = 6.67e-11;

Asteroid::Asteroid(b2World* world, RenderWindow* window) : Entity(world, window){
	this->type = "Asteroid";

}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::configure(float x, float y, float mass, string texturePath)
{
	x/=SCALE;
	y/=SCALE;

	//Properties
	this->mass = mass;

	//Texture loading
	texture.loadFromFile(texturePath);

	//Body definitions
	bodyDef.position = b2Vec2(x, y);
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape asteroidShape;
	asteroidShape.m_radius = (texture.getSize().x/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &asteroidShape;
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);

	drawReady = true;
}

void Asteroid::step(vector<Entity*>* entities)
{
	vector<Entity*> e = *entities;
	Planet* planet = (Planet*)e[0];
	b2Body* planetBody = planet->getBody();

	b2Vec2 planetPos = planetBody->GetPosition();
	b2Vec2 asteroidPos = body->GetPosition();

	float distance = pow((planetPos.x - asteroidPos.x), 2) + pow((planetPos.y - asteroidPos.y), 2);
	cout << "DISTANCE: " << sqrt(distance) << endl;

	float deltaX = planetPos.x - asteroidPos.x;
	float deltaY = planetPos.y - asteroidPos.y;
	float angle = atan(deltaY/deltaX);

	float forceMagnitude = (G * (this->mass) * (planet->mass))/distance;
	cout << "FORCE :" << forceMagnitude << endl;

	b2Vec2 gravityForce(forceMagnitude*cos(angle), forceMagnitude*sin(angle));

	body->ApplyForce(gravityForce, body->GetWorldCenter(), true);
}
