// RingFlyer.h
// @author Eric D. Wills

#ifndef __RING_FLYER_H__
#define __RING_FLYER_H__

#include "Ogre.h"

class RingFlyerFrameListener;
class Level;
class Ring;
class Ship;


class RingFlyer {
	
 private:
	 
  RingFlyerFrameListener* frameListener;
  Ogre::Root*               root;
  Ogre::SceneManager*       sceneManager;
  Ogre::RenderWindow*       renderWindow;
  Ogre::Camera*             camera;
  Ogre::RaySceneQuery*      raySceneQuery;
  Ogre::Ray                 terrainRay;
  Level*					level;
  //Ogre::Overlay*     mPanelOverlay;




 public:
  RingFlyer();

  ~RingFlyer();

  Ogre::Root*         getRoot()         { return root; }
  Ogre::SceneManager* getSceneManager() { return sceneManager; }
  Ogre::RenderWindow* getRenderWindow() { return renderWindow; }
  Ogre::Camera*       getCamera()       { return camera; }
  Ring **e;
    Ship*						ship;
	Ogre::SceneNode *cameraNode;
  float getTerrainHeightAt(float x, float y);

  void adjustCameraHeightToTerrain();

  void createNextLevel(int Level);

  void createRings(int n);

  void destroyRings(int n);

  Ogre::Vector3 getShipPosition();

  void init();

 private:
  bool setup();
};

#endif
