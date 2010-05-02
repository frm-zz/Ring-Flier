//#pragma once
#ifndef __SHIP_H__
#define __SHIP_H__
#include "Ogre.h"
class TerrainDemo;

class Ship
{
private:
	Ogre::Vector3 shipPosition;
	TerrainDemo* demo;
	Ogre::String node;
public:
	Ship(TerrainDemo* demo);
	~Ship(void);
	void setPosition(Ogre::Vector3 position);
	Ogre::Vector3 getPosition();

};
#endif;