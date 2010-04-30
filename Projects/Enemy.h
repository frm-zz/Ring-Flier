//#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Ogre.h"
class TerrainDemo;
class EnemyState;
class Enemy
{
private:
	static const float ACTIVATION_RADIUS;
	static const float CHASE_VELOCITY;
	static const float RELAX_TIME;
	static const float KILL_RADIUS;
	float chaseTime;
	Ogre::Vector3 position;
	TerrainDemo*         demo;
	bool inRange(const Ogre::Vector3 pos, float r) const;
	void moveTowards(const Ogre::Vector3 pos, float velocity, float elapsedTime);
	Ogre::String sphereName;
	//void setCurrentState(EnemyState* state);
	//EnemyState* state;
	//bool frameStarted(const Ogre::FrameEvent& event);
	//bool frameEnded(const Ogre::FrameEvent& event);

public:
	Enemy(Ogre::String name, TerrainDemo* demo);
	~Enemy(void);

	bool update(float elapsedTime);
	

};
#endif;