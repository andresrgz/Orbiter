/*
 * Player.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: andres
 */

#include "Player.h"

const float SCALE = 30.0;

Player::Player(float x, float y, float scale, string textureKey) : Entity(x, y, scale, textureKey){
	this->type = "Player";

	this->maxSpeed = .5f;
	this->jumpForce = 5.f;

	this->currentPlanet = NULL;
	this->numFootContacts = 0;

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2PolygonShape playerShape;
	float sizeX = (getTexture()->getSize().x/SCALE)/2;
	float sizeY = (getTexture()->getSize().y/SCALE)/2;
	playerShape.SetAsBox(sizeX, sizeY);

	//Fixture definitions
	fixtureDef.shape = &playerShape;
	body->CreateFixture(&fixtureDef);

	//Foot sensor
	b2PolygonShape footSensorShape;
	footSensorShape.SetAsBox(0.3, 0.3, b2Vec2(0,-2), 0);
	fixtureDef.isSensor = true;
	footSensorFixture = body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData(this);
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::setCurrentPlanet()
{
	//Gets the first planet in the entities list
	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
	{
		Entity* entity = *i;
		if(entity->getType() == "Planet")
		{
			currentPlanet = (Planet*)entity;
			break;
		}
	}

	for(list<Entity*>::iterator i = entities->begin(); i != entities->end(); i++)
	{
		Entity* entity = *i;
		if(entity->getType() == "Planet" && (Planet*)entity != currentPlanet)
		{
			Planet* planet = (Planet*)entity;

			b2Vec2 planetForce = planet->getCurrentForce(this);
			b2Vec2 currentPlanetForce = currentPlanet->getCurrentForce(this);

			float planetForceMagnitude = sqrt(planetForce.x*planetForce.x + planetForce.y*planetForce.y);
			float currentPlanetForceMagnitude = sqrt(currentPlanetForce.x*currentPlanetForce.x + currentPlanetForce.y*currentPlanetForce.y);

			if(planetForceMagnitude > currentPlanetForceMagnitude)
				currentPlanet = planet;
		}
	}
}

//Calibrates player details such as: Rotation angle, jump vector, and speed vector depending on the planet.
void Player::calibrate()
{
	//Check on what planet the player is currently.
	setCurrentPlanet();

	//Get current gravity force on player
	b2Vec2 force = currentPlanet->getCurrentForce(this);
	float forceX = force.x;
	float forceY = force.y;

	//Calculate the reference angle at which the jump vector must point
	float jumpAngle = forceX != 0 ? atan(forceY/forceX) : b2_pi/2.f;
	if(jumpAngle < 0)
		jumpAngle*=-1;

	//Calculate the angle at which the player must face
	float facingAngle = forceY != 0 ? atan(-(forceX/forceY)) : b2_pi/2.f;
	if(forceY < 0)
		facingAngle-=b2_pi;

	//Calculate jump force's components
	float jumpX = jumpForce*cos(jumpAngle);
	float jumpY = jumpForce*sin(jumpAngle);

	//Set jump force direction
	if(forceX > 0)
		jumpX*=-1;
	if(forceY > 0)
		jumpY*=-1;

	//Apply
	body->SetTransform(body->GetPosition(), facingAngle);
	speedVec.Set(maxSpeed*cos(facingAngle), maxSpeed*sin(facingAngle));
	jumpVec.Set(jumpX, jumpY);
}


void Player::move()
{
	if(Keyboard::isKeyPressed(Keyboard::A))
	{
		textureKey = "R-LEFT";
		body->ApplyLinearImpulse(-speedVec, body->GetWorldCenter(), true);
	}
	else if(Keyboard::isKeyPressed(Keyboard::D) )
	{
		textureKey = "R-RIGHT";
		body->ApplyLinearImpulse(speedVec, body->GetWorldCenter(), true);
	}
	else
	{
		if(textureKey == "R-LEFT")
			textureKey = "S-LEFT";
		else if(textureKey == "R-RIGHT")
			textureKey = "S-RIGHT";
	}
	if((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::W))  && numFootContacts >= 1)
		body->ApplyLinearImpulse(jumpVec, body->GetWorldCenter(), true);

	calibrate();
}
