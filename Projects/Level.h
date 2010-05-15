//#pragma once

#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Ogre.h"
class RingFlyer;
class Level
{


private:
	Ogre::String currentLevel, skyBox;
	
	
public:
	Level(int x,RingFlyer* flyer);
	~Level(void);


};
#endif;
