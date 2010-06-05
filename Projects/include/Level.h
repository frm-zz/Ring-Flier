#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Ogre.h"
class RingFlier;
class Level
{
private:
	Ogre::String currentLevel, skyBox;

public:
	Level(int x,RingFlier* flier);
	~Level(void);
};
#endif;
