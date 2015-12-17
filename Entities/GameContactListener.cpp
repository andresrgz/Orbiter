/*
 * BulletContactListener.cpp
 *
 *  Created on: Dec 16, 2015
 *      Author: andres
 */

#include "GameContactListener.h"

GameContactListener::GameContactListener() {
	// TODO Auto-generated constructor stub

}

GameContactListener::~GameContactListener() {
	// TODO Auto-generated destructor stub
}

void GameContactListener::BeginContact(b2Contact* contact)
{
	Entity* entityA = (Entity*)contact->GetFixtureA()->GetUserData();
	Entity* entityB = (Entity*)contact->GetFixtureB()->GetUserData();

	//Contact between asteroid and bullet
	if(entityA->getType() == "Asteroid" && entityB->getType() == "Bullet")
	{
		entityA->deleteEntity();
		entityB->deleteEntity();
	}
	else if(entityB->getType() == "Asteroid" && entityA->getType() == "Bullet")
	{
		entityA->deleteEntity();
		entityB->deleteEntity();
	}

	//Contact between player and planet
	if(entityA->getType() == "Player" && entityB->getType() == "Planet")
	{
		((Player*)entityA)->jumpEnabled = true;
	}
	else if(entityB->getType() == "Player" && entityA->getType() == "Planet")
	{
		((Player*)entityB)->jumpEnabled = true;
	}
}

void GameContactListener::EndContact(b2Contact* contact)
{
	Entity* entityA = (Entity*)contact->GetFixtureA()->GetUserData();
	Entity* entityB = (Entity*)contact->GetFixtureB()->GetUserData();

	//Contact between player and planet
	if(entityA->getType() == "Player" && entityB->getType() == "Planet")
	{
		((Player*)entityA)->jumpEnabled = false;
	}
	else if(entityB->getType() == "Player" && entityA->getType() == "Planet")
	{
		((Player*)entityB)->jumpEnabled = false;
	}
}

