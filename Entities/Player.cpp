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
	this->maxSpeed = .5f;
	this->jumpForce = 5.f;
	this->currentPlanet = NULL;
	this->numFootContacts = 0;
	this->frames = 0;
	this->state = "S-RIGHT";
	this->animationRate = 5;
	this->currentTexture = 0;

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

	//Foot sensor
	b2PolygonShape footSensorShape;
	footSensorShape.SetAsBox(0.3, 0.3, b2Vec2(0,-2), 0);
	fixtureDef.isSensor = true;
	footSensorFixture = body->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData(this);

	initTextures();
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::initTextures()
{

	//Standing textures
	textures["S-RIGHT"].push_back(new Texture());
	textures["S-RIGHT"][0]->loadFromFile("assets/player/stand_right.png");

	textures["S-LEFT"].push_back(new Texture());
	textures["S-LEFT"][0]->loadFromFile("assets/player/stand_left.png");

	//Running textures
	loadMultiTextures("R-RIGHT", "assets/player/run_right_", 8);
	loadMultiTextures("R-LEFT", "assets/player/run_left_", 8);
}

void Player::loadMultiTextures(string state, string path, int count)
{
	ostringstream currentPath;
	for(int i = 1; i <= count; i++)
	{
		textures[state].push_back(new Texture());
		currentPath << path << i << ".png";

		textures[state][i-1]->loadFromFile(currentPath.str());

		currentPath.str("");
		currentPath.clear();
	}
}

void Player::setCurrentPlanet()
{
	//Gets the first planet in the entities list
	for(unsigned int i = 0; i < entities->size(); i++)
	{
		Entity* entity = entities->at(i);
		if(entity->getType() == "Planet")
		{
			currentPlanet = (Planet*)entity;
			break;
		}
	}

	//Compares distance between all the other planets
	for(unsigned int i = 0; i < entities->size(); i++)
	{
		Entity* entity = entities->at(i);
		if(entity->getType() == "Planet" && (Planet*)entity != currentPlanet)
		{
			Planet* planet = (Planet*)entity;
			if(planet->getCurrentForce(this) > currentPlanet->getCurrentForce(this))
				currentPlanet = planet;
		}
	}
}

/*Calibrates player details such as: Rotation angle, jump vector, and speed vector
depending on the planet.
*/
void Player::calibrate()
{
	//Check on what planet the player is currently.
	setCurrentPlanet();

	//Get player coordinates
	float playerX = this->getPosition().x;
	float playerY = this->getPosition().y;

	//Get current planet coordinates
	float planetX = currentPlanet->getPosition().x;
	float planetY = currentPlanet->getPosition().y;

	//Calculate the difference between the player and the planet's coordinates
	float deltaX = playerX - planetX;
	float deltaY = playerY - planetY;

	//Calculate the angle at which the jump vector must point
	float angle = deltaX != 0 ? atan(deltaY/deltaX) : b2_pi/2.f;
	if(angle < 0)
		angle*=-1;

	//Calculate the angle at which the player must face
	float facingAngle = deltaY != 0 ? atan(-(deltaX/deltaY)) : b2_pi/2.f;
	if(deltaY > 0)
		facingAngle-=b2_pi;

	//Apply
	body->SetTransform(body->GetPosition(), facingAngle);
	speedVec.Set(maxSpeed*cos(facingAngle), maxSpeed*sin(facingAngle));

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


void Player::move()
{
	if(Keyboard::isKeyPressed(Keyboard::A))
	{
		state = "R-LEFT";
		body->ApplyLinearImpulse(-speedVec, body->GetWorldCenter(), true);
	}
	else if(Keyboard::isKeyPressed(Keyboard::D))
	{
		state = "R-RIGHT";
		body->ApplyLinearImpulse(speedVec, body->GetWorldCenter(), true);
	}
	else
	{
		if(state == "R-LEFT")
			state = "S-LEFT";
		else if(state == "R-RIGHT")
			state = "S-RIGHT";
	}
	if(Keyboard::isKeyPressed(Keyboard::Space) && numFootContacts >= 1)
		body->ApplyLinearImpulse(jumpVec, body->GetWorldCenter(), true);

	calibrate();

	frames++;
	if(frames >= 60)
		frames = 0;

	if(frames%animationRate == 0)
		currentTexture++;

	if(currentTexture >= textures[state].size())
		currentTexture = 0;

	this->setTexture(*(textures[state][currentTexture]));
}
