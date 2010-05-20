//#pragma once
#ifndef __RING_H__
#define __RING_H__
#include "Ogre.h"
class RingFlyer;
class EnemyState;
class Ring
{
private:
	static const float ACTIVATION_RADIUS;
	static const float CHASE_VELOCITY;
	static const float RELAX_TIME;
	static const float KILL_RADIUS;
	bool check;
	float chaseTime;
	Ogre::Vector3 position;
	RingFlyer*         flyer;
	bool inRange(const Ogre::Vector3 pos, float r) const;
	void moveTowards(const Ogre::Vector3 pos, float velocity, float elapsedTime);
	Ogre::String sphereName;
	//void setCurrentState(EnemyState* state);
	//EnemyState* state;
	//bool frameStarted(const Ogre::FrameEvent& event);
	//bool frameEnded(const Ogre::FrameEvent& event);

public:
	Ring(Ogre::String name, RingFlyer* flyer);
	~Ring(void);

	int update(float elapsedTime);
	

};
#endif;