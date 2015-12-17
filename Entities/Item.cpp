/*
 * Item.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: andres
 */

#include "Item.h"

const float SCALE = 30.0;

Item::Item(float x, float y) : Entity(x, y, 1.f, "Health"){
	this->type = "Item";

	//Body definitions
	bodyDef.type = b2_dynamicBody;
	body = world->CreateBody(&bodyDef);

	//Shape definitions
	b2CircleShape itemShape;
	itemShape.m_radius = ((getTexture()->getSize().x*this->getScale().x)/2)/SCALE;

	//Fixture definitions
	fixtureDef.shape = &itemShape;
	fixtureDef.filter.categoryBits = ITEM;
	fixtureDef.filter.maskBits = PLAYER1 | ASTEROID | PLANET;
	body->CreateFixture(&fixtureDef);
}

Item::~Item() {
	// TODO Auto-generated destructor stub
}

