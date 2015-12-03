/*
 * PlanetContactLister.h
 *
 *  Created on: Dec 2, 2015
 *      Author: andres
 */

#ifndef ENTITIES_PLANETCONTACTLISTENER_H_
#define ENTITIES_PLANETCONTACTLISTENER_H_

#include <Box2D/Box2D.h>
#include "Player.h"

class PlanetContactListener: public b2ContactListener {
public:
	PlanetContactListener();
	virtual ~PlanetContactListener();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif /* ENTITIES_PLANETCONTACTLISTENER_H_ */
