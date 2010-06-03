//#pragma once
#ifndef __SHIP_H__
#define __SHIP_H__
#include "Ogre.h"
class RingFlier;
class Ship
{
private:
	Ogre::Vector3 shipPosition;
	RingFlier* flier;
	Ogre::String nodeName;
public:
	Ship(RingFlier* flier);
	~Ship(void);
	Ogre::Vector3 getPosition();
	void setOrientation(float pitch, float roll);
	void setPosition(Ogre::Vector3 position);

};
#endif;