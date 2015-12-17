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
	this->movementForce = 35.f;
	this->maxSpeed = 12.0f;
	this->jumpForce = 7.f;
	this->facingAngle = 0;
	this->jumpAngle = 0;
	this->referenceAngle = 9.0*b2_pi/180;
	this->gunAngle = referenceAngle;
	this->relativeAngle = 0;

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
	fixtureDef.filter.categoryBits = PLAYER1;
	fixtureDef.filter.maskBits = ASTEROID | PLANET;
	body->CreateFixture(&fixtureDef);

	//Foot sensor
	b2PolygonShape footSensorShape;
	footSensorShape.SetAsBox(sizeX/4, sizeY/4, b2Vec2(0,-3), 0);
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

			if(planetForce.Length() > currentPlanetForce.Length())
				currentPlanet = planet;
		}
	}
}

void Player::setGunAngle(float relativeAngle)
{
	this->gunAngle = relativeAngle + facingAngle;
}

float Player::getGunAngle()
{
	return gunAngle;
}

//Gets the position of the end of the gun in b2World coordinates.
//All angles are in radians.
//All offset values are with respect to the player's center.
b2Vec2 Player::getGunPosition()
{
	//The distance from the tip of the gun to the center of the player.
	float distanceFromPlayer = 45.0f;
	float offsetAngle = facingAngle;
	float x_offset = 1.0f;
	float y_offset = 1.0f;

	if(textureKey == "S-LEFT" || textureKey == "R-LEFT")
	{
		offsetAngle+=gunAngle;
		x_offset*=-1;
		y_offset*=-1;
	}
	else
		offsetAngle-=gunAngle;

	x_offset *= distanceFromPlayer*cos(offsetAngle);
	y_offset *= distanceFromPlayer*sin(offsetAngle);

	x_offset += getPosition().x;
	y_offset += getPosition().y;

	x_offset /= SCALE;
	y_offset /= SCALE;

	return b2Vec2(x_offset, y_offset);
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
	this->jumpAngle = forceX != 0 ? atan(forceY/forceX) : b2_pi/2.f;
	if(jumpAngle < 0)
		jumpAngle*=-1;

	//Calculate the angle at which the player must face
	this->facingAngle = forceY != 0 ? atan(-(forceX/forceY)) : -b2_pi/2.f;
	if(forceY < 0)
		facingAngle+=b2_pi;

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
	movementVec.Set(movementForce*cos(facingAngle), movementForce*sin(facingAngle));
	jumpVec.Set(jumpX, jumpY);
}

void Player::move()
{
	calibrate();

	if(textureKey == "R-LEFT")
		textureKey = "S-LEFT";
	else if(textureKey == "R-RIGHT")
		textureKey = "S-RIGHT";

	if(Keyboard::isKeyPressed(Keyboard::A))
	{
		textureKey = "R-LEFT";
		if(body->GetLinearVelocity().Length() < maxSpeed)
			body->ApplyForce(-movementVec, body->GetWorldCenter(), true);
	}
	else if(Keyboard::isKeyPressed(Keyboard::D) )
	{
		textureKey = "R-RIGHT";
		if(body->GetLinearVelocity().Length() < maxSpeed)
			body->ApplyForce(movementVec, body->GetWorldCenter(), true);
	}

	if(Keyboard::isKeyPressed(Keyboard::W) && numFootContacts >= 1)
		body->ApplyLinearImpulse(jumpVec, body->GetWorldCenter(), true);

	if(Keyboard::isKeyPressed(Keyboard::Space))
		shoot();

	if(Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		relativeAngle += 0.1;
		this->setGunAngle(relativeAngle);
	}
	else if(Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		relativeAngle -= 0.1;
		this->setGunAngle(relativeAngle);
	}
}

void Player::shoot()
{
	Bullet* bullet = new Bullet(this);
	bullet->spawn();
}
