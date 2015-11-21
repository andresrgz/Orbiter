/*
 * Asteroid.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Asteroid.h"

const float SCALE = 30.0;

Asteroid::Asteroid(b2World* world, RenderWindow* window) : Entity(world, window){
	this->type = "Asteroid";

}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::configure(float x, float y, string texturePath)
{
	x/=SCALE;
	y/=SCALE;

	//Texture loading
	texture.loadFromFile(texturePath);
	this->setTexture(texture);
	this->setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);

	//Body definitions
	bodyDef.position = b2Vec2(x, y);
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape asteroidShape;
	asteroidShape.m_radius = ((texture.getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &asteroidShape;
	fixtureDef.restitution = 0.2f;
	body->CreateFixture(&fixtureDef);

	drawReady = true;
}

void Asteroid::step(vector<Entity*>* entities)
{

	//Get planet details
	vector<Entity*> e = *entities;
	Planet* planet = (Planet*)e[0];
	b2Body* planetBody = planet->getBody();

	//Get planet and asteroid positions
	b2Vec2 planetPos = planetBody->GetPosition();
	b2Vec2 asteroidPos = body->GetPosition();

	//Calculate distance difference
	float deltaX = asteroidPos.x - planetPos.x;
	float deltaY = asteroidPos.y - planetPos.y;

	//Calculate angle
	float angle;
	if(deltaX != 0)
		angle = atan(deltaY/deltaX);
	else
		angle = b2_pi/2.f;

	if(angle < 0)
		angle*=-1;

	//Calculate force magnitude
	float distance = deltaX*deltaX + deltaY*deltaY;
	float forceMagnitude = (planet->getGravityForce())/distance;
	float forceX = forceMagnitude*cos(angle);
	float forceY = forceMagnitude*sin(angle);

	//Calculate force's components' directions
	if(deltaX > 0)
		forceX*=-1;
	if(deltaY > 0)
		forceY*=-1;

	b2Vec2 gravityForce(forceX, forceY);

	body->ApplyForce(gravityForce, body->GetWorldCenter(), true);

	cout << "DELTA X: " << deltaX << " DELTA Y: " << deltaY << endl;
	cout << "DISTANCE: " << sqrt(distance) << endl;
	cout << "ANGLE: " << angle*180/b2_pi<< endl;
	cout << "FORCE MAGNITUDE: " << forceMagnitude << endl;
	cout << "FORCE X: " << forceMagnitude*cos(angle) << endl;
	cout << "FORCE Y: " << forceMagnitude*sin(angle) << endl << endl;
}
