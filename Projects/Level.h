//#pragma once

#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "Ogre.h"
class TerrainDemo;
class Level
{


private:
	Ogre::String currentLevel, skyBox;
	
	
public:
	Level(int x,TerrainDemo* demo);
	~Level(void);


};
#endif;
