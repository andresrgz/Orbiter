/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: andres
 */

#include "Bullet.h"

const float SCALE = 30.0;

Bullet::Bullet(Player* owner) : Entity(0.f, 0.f, 1.f, "Bullet") {
	this->type = "Bullet";
	this->bulletForce = 100.0f;
	this->offsetAngle = 0;
	this->angleFromPlayer = 11.0*b2_pi/180;
	this->distanceFromPlayer = 45.0f;
	this->owner = owner;

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2PolygonShape bulletShape;
	float sizeX = (getTexture()->getSize().x/SCALE)/2;
	float sizeY = (getTexture()->getSize().y/SCALE)/2;
	bulletShape.SetAsBox(sizeX, sizeY);

	//Fixture definitions
	fixtureDef.shape = &bulletShape;
	body->CreateFixture(&fixtureDef);
}

Bullet::~Bullet() {

}

void Bullet::setBulletForce(float bulletForce)
{
	this->bulletForce = bulletForce;
}

void Bullet::setDistanceFromPlayer(float distanceFromPlayer)
{
	this->distanceFromPlayer = distanceFromPlayer;
}

void Bullet::spawn()
{
	//Initialize offset coordinates in which the bullet will be positioned
	float x_offset = 1.0f;
	float y_offset = 1.0f;
	offsetAngle = owner->getGunAngle();

	//If the player is facing left, the offset coordinates and the force gets flipped.
	if(owner->textureKey == "S-LEFT" || owner->textureKey == "R-LEFT")
	{
		bulletForce*=-1;
		x_offset*=-1;
		y_offset*=-1;
	}

	//Calculate the offset in each axis depending on the facing angle of the player.
	x_offset *= distanceFromPlayer*cos(offsetAngle);
	y_offset *= distanceFromPlayer*sin(offsetAngle);

	b2Vec2 position((owner->getPosition().x + x_offset)/SCALE, (owner->getPosition().y + y_offset)/SCALE);
	body->SetTransform(position, owner->facingAngle);

	b2Vec2 force(bulletForce*cos(owner->facingAngle), bulletForce*sin(owner->facingAngle));
	body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);

	entities->push_back(this);
}
