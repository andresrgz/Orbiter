/*
 * Asteroid.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: andres
 */

#include "Asteroid.h"

const float SCALE = 30.0;

Asteroid::Asteroid(float x, float y, float scale, string texturePath) : Entity(x, y, scale, texturePath){
	this->type = "Asteroid";

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape asteroidShape;
	asteroidShape.m_radius = ((texture.getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &asteroidShape;
	fixtureDef.restitution = 0.2f;
	body->CreateFixture(&fixtureDef);
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
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
	float angle = deltaX != 0 ? atan(deltaY/deltaX) : b2_pi/2.f;
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
