/*
 * Player.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: andres
 */

#include "Player.h"

const float SCALE = 30.0;

Player::Player(float x, float y, float scale, string texturePath) : Entity(x, y, scale, texturePath){
	this->type = "Player";
	this->facingAngle = 0.0f;
	this->speed = 0.25f;
	this->jumpForce = 1.00f;

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2PolygonShape playerShape;
	float sizeX = (texture.getSize().x/SCALE)/2;
	float sizeY = (texture.getSize().y/SCALE)/2;
	playerShape.SetAsBox(sizeX, sizeY);

	//Fixture definitions
	fixtureDef.shape = &playerShape;
	body->CreateFixture(&fixtureDef);
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

//Angle is set in radians.
//The speed's components change with the facing angle.
void Player::setFacingAngle(float facingAngle)
{
	this->facingAngle = facingAngle;
	body->SetTransform(body->GetPosition(), facingAngle);
	speedVec.Set(speed*cos(facingAngle), speed*sin(facingAngle));
}

//The jump vector depends on the angle of the force of gravity.
void Player::setJumpVector(float deltaX, float deltaY, float angle)
{
	//Calculate jump force's components
	float jumpX = jumpForce*cos(angle);
	float jumpY = jumpForce*sin(angle);

	//Set jump force direction
	if(deltaX < 0)
		jumpX*=-1;
	if(deltaY < 0)
		jumpY*=-1;

	jumpVec.Set(jumpX, jumpY);
}

//Returns angle in radians.
float Player::getFacingAngle()
{
	return facingAngle;
}

void Player::move()
{
	if(Keyboard::isKeyPressed(Keyboard::A))
		body->ApplyLinearImpulse(-speedVec, body->GetWorldCenter(), true);
	if(Keyboard::isKeyPressed(Keyboard::D))
		body->ApplyLinearImpulse(speedVec, body->GetWorldCenter(), true);
	if(Keyboard::isKeyPressed(Keyboard::Space))
		body->ApplyLinearImpulse(jumpVec, body->GetWorldCenter(), true);
}
