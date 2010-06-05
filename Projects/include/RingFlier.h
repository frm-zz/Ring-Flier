#ifndef __RING_FLIER_H__
#define __RING_FLIER_H__
#include "Ogre.h"
class RingFlierFrameListener;
class Level;
class Ring;
class Ship;
class RingFlier {

private:

	RingFlierFrameListener* frameListener;
	Ogre::Root*               root;
	Ogre::SceneManager*       sceneManager;
	Ogre::RenderWindow*       renderWindow; 
	Ogre::RaySceneQuery*      raySceneQuery;
	Ogre::Ray                 terrainRay;
	Level*					level;
	

public:
	RingFlier();
	~RingFlier();
	Ogre::Camera*       camera;
	Ogre::Root*         getRoot()         { return root; }
	Ogre::SceneManager* getSceneManager() { return sceneManager; }
	Ogre::RenderWindow* getRenderWindow() { return renderWindow; }
	Ogre::Camera*       getCamera()       { return camera; }
	Ring				**e;
	Ship*				ship;
	Ogre::SceneNode *cameraNode;
	Ogre::Vector3 getShipPosition();

	void setSourcePos(int sourceNum, float xpos, float ypos, float zpos);
	void setListenerPos(float xpos, float ypos, float zpos);
	float getTerrainHeightAt(float x, float y);
	void adjustCameraHeightToTerrain();
	void createNextLevel(int Level);
	void createRings(int n);
	void destroyRings(int n);
	void init();
	void scoreEffect();
	void deadEffect();
	void explosion();
	void explosionSound();
	void clockSound();
	void stopClockSound();

private:
	bool setup();
};

#endif
