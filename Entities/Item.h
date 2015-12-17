/*
 * Item.h
 *
 *  Created on: Dec 17, 2015
 *      Author: andres
 */

#ifndef ENTITIES_ITEM_H_
#define ENTITIES_ITEM_H_

#include "Entity.h"

class Item : public Entity{
public:
	Item(float x, float y);
	virtual ~Item();
};

#endif /* ENTITIES_ITEM_H_ */
