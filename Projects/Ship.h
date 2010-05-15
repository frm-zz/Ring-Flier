//#pragma once
#ifndef __SHIP_H__
#define __SHIP_H__
#include "Ogre.h"
class RingFlyer;

class Ship
{
private:
	Ogre::Vector3 shipPosition;
	RingFlyer* flyer;
	Ogre::String node;
public:
	Ship(RingFlyer* flyer);
	~Ship(void);
	void setPosition(Ogre::Vector3 position);
	Ogre::Vector3 getPosition();
	void setOrientation(float pitch, float roll);
	Ogre::Vector3 getOrientation();

};
#endif;