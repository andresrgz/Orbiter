/*
 * PlanetContactLister.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: andres
 */

#include "PlanetContactListener.h"

PlanetContactListener::PlanetContactListener() {
	// TODO Auto-generated constructor stub

}

PlanetContactListener::~PlanetContactListener() {
	// TODO Auto-generated destructor stub
}

void PlanetContactListener::BeginContact(b2Contact* contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetUserData();
	if(bodyUserData)
	{
		static_cast<Player*>(bodyUserData)->numFootContacts++;
	}

	bodyUserData = contact->GetFixtureA()->GetUserData();
	if(bodyUserData)
	{
		static_cast<Player*>(bodyUserData)->numFootContacts++;
	}
}

void PlanetContactListener::EndContact(b2Contact* contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetUserData();
	if(bodyUserData)
	{
		static_cast<Player*>(bodyUserData)->numFootContacts--;
	}

	bodyUserData = contact->GetFixtureA()->GetUserData();
	if(bodyUserData)
	{
		static_cast<Player*>(bodyUserData)->numFootContacts--;
	}
}
