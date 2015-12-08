/*
 * Bullet.cpp
 *
 *  Created on: Dec 6, 2015
 *      Author: andres
 */

#include "Bullet.h"

const float SCALE = 30.0;

Bullet::Bullet(Player* owner) : Entity(0.f, 0.f, 1.0f, "Bullet") {
	this->type = "Bullet";
	this->bulletForce = 100.0f;
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

void Bullet::spawn()
{
	if(owner->textureKey == "S-LEFT" || owner->textureKey == "R-LEFT")
		bulletForce*=-1;

	b2Vec2 force(bulletForce*cos(owner->facingAngle), bulletForce*sin(owner->facingAngle));
	body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);
	body->SetTransform(owner->getGunPosition(), owner->facingAngle);

	entities->push_back(this);
}
