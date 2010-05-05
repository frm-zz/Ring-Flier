// TerrainDemo.h
// @author Eric D. Wills

#ifndef __TERRAIN_DEMO_H__
#define __TERRAIN_DEMO_H__

#include "Ogre.h"

class TerrainDemoFrameListener;
class Level;
class Enemy;
class Ship;


class TerrainDemo {
	
 private:
	 
  TerrainDemoFrameListener* frameListener;
  Ogre::Root*               root;
  Ogre::SceneManager*       sceneManager;
  Ogre::RenderWindow*       renderWindow;
  Ogre::Camera*             camera;
  Ogre::RaySceneQuery*      raySceneQuery;
  Ogre::Ray                 terrainRay;
  Level*					level;





 public:
  TerrainDemo();

  ~TerrainDemo();

  Ogre::Root*         getRoot()         { return root; }
  Ogre::SceneManager* getSceneManager() { return sceneManager; }
  Ogre::RenderWindow* getRenderWindow() { return renderWindow; }
  Ogre::Camera*       getCamera()       { return camera; }
  Enemy **e;
    Ship*						ship;
	Ogre::SceneNode *cameraNode;
  float getTerrainHeightAt(float x, float y);

  void adjustCameraHeightToTerrain();

  void createNextLevel(int Level);

  void createEnemies(int n);

  void destroyEnemies(int n);

  Ogre::Vector3 getShipPosition();

  void init();

 private:
  bool setup();
};

#endif
