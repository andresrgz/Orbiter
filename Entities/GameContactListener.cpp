/*
 * BulletContactListener.cpp
 *
 *  Created on: Dec 16, 2015
 *      Author: andres
 */

#include "GameContactListener.h"

GameContactListener::GameContactListener(list<Entity*>* entities) {
	this->entities = entities;
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
		Bullet* bullet = (Bullet*)entityB;
		bullet->owner->points += 10;

		entityA->deleteEntity();
		entityB->deleteEntity();
	}
	else if(entityB->getType() == "Asteroid" && entityA->getType() == "Bullet")
	{
		Bullet* bullet = (Bullet*)entityA;
		bullet->owner->points += 10;

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

	//Contact between player and asteroid
	if(entityA->getType() == "Player" && entityB->getType() == "Asteroid")
	{
		((Player*)entityA)->applyDamage(((Asteroid*)entityB)->damage);
		entityB->deleteEntity();
	}
	else if(entityB->getType() == "Player" && entityA->getType() == "Asteroid")
	{
		((Player*)entityB)->applyDamage(((Asteroid*)entityA)->damage);
		entityA->deleteEntity();
	}

	//Contact between planet and asteroid
	if(entityA->getType() == "Asteroid" && entityB->getType() == "Planet")
	{
		entityA->deleteEntity();
	}
	else if(entityB->getType() == "Asteroid" && entityA->getType() == "Planet")
	{
		entityB->deleteEntity();
	}

	//Contact between bullet and planet
	if(entityA->getType() == "Bullet" && entityB->getType() == "Planet")
	{
		entityA->deleteEntity();
	}
	else if(entityB->getType() == "Bullet" && entityA->getType() == "Planet")
	{
		entityB->deleteEntity();
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

