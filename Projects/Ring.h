//#pragma once
#ifndef __RING_H__
#define __RING_H__
#include "Ogre.h"
class RingFlier;
class EnemyState;
class Ring
{
private:
	static const float ACTIVATION_RADIUS;
	bool check;
	bool inRange(const Ogre::Vector3 pos, float r) const;
	Ogre::String ringName;
	Ogre::Vector3 position;
	RingFlier*  flier;
public:
	Ring(Ogre::String name, RingFlier* flier);
	~Ring(void);

	int update(float elapsedTime);


};
#endif;