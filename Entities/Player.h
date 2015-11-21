/*
 * Player.h
 *
 *  Created on: Nov 21, 2015
 *      Author: andres
 */

#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include <map>
#include "Entity.h"

class Player : public Entity{
public:
	map<string, Texture> textures;
	Player(float x, float y, float scale, string texturePath);
	virtual ~Player();
};

#endif /* ENTITIES_PLAYER_H_ */
