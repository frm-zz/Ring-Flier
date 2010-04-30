// TerrainDemo.cpp
// @author Eric D. Wills

#include "TerrainDemo.h"
#include "TerrainDemoFrameListener.h"
//#include "Level.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



TerrainDemo::TerrainDemo() : root(new Ogre::Root()), frameListener(NULL), raySceneQuery(NULL), currentLevel(NULL) {}

TerrainDemo::~TerrainDemo() {
  if (frameListener != NULL)
    delete frameListener;
  if (raySceneQuery != NULL)
    delete raySceneQuery;

  delete root;
}

float TerrainDemo::getTerrainHeightAt(float x, float z) {
  terrainRay.setOrigin(Ogre::Vector3(x, 1000.0f, z));
  raySceneQuery->setRay(terrainRay);

  Ogre::RaySceneQueryResult&          queryResult = raySceneQuery->execute();
  Ogre::RaySceneQueryResult::iterator qi          = queryResult.begin();
  return (qi != queryResult.end() && qi->worldFragment) ? qi->worldFragment->singleIntersection.y : 0.0f;
}

void TerrainDemo::adjustCameraHeightToTerrain() {
  const Ogre::Vector3& cameraPos = camera->getPosition();
  camera->setPosition(cameraPos.x, getTerrainHeightAt(cameraPos.x, cameraPos.z) + 15.0f, cameraPos.z);
}

void TerrainDemo::init() {
  if (setup())
    root->startRendering();
}

bool TerrainDemo::setup() {
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");

  // iterate through resources.cfg and register resource groups
  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  while (seci.hasMoreElements()) {
    std::string secName = seci.peekNextKey();

    Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
    for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin(); i != settings->end(); ++i)
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(i->second, i->first, secName);
  }

  // create render window if user completes config dialog
  if (root->showConfigDialog())
    renderWindow = root->initialise(true);
  else
    return false;

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  // craete scene manager
  sceneManager = root->createSceneManager("TerrainSceneManager");

  Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
  sceneManager->setFog(Ogre::FOG_LINEAR, fogColor, 0.001f, 500.0f, 1000.0f);

  // create camera
  camera = sceneManager->createCamera("PrimaryCamera");
  camera->setNearClipDistance(1.0f);
  camera->setFarClipDistance(10000.0f);
  camera->setPosition(707.0f, 2500.0f, 528.0f);

  // create viewport
  Ogre::Viewport* vp = renderWindow->addViewport(camera);
  vp->setBackgroundColour(fogColor);
  camera->setAspectRatio(vp->getActualWidth()/(float)vp->getActualHeight());
  camera->setFOVy(Ogre::Radian(65.0f*Ogre::Math::PI/180.0f));

  // set up lighting
  sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

  Ogre::Light* light = sceneManager->createLight("PrimaryLight");
  light->setPosition(20.0f, 80.0f, 50.0f);
  //
  //
  // load terrain
  
  sceneManager->setWorldGeometry("terrain.cfg");
  // set up the ray query for terrain following
  terrainRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
  
  raySceneQuery = sceneManager->createRayQuery(terrainRay);

  frameListener = new TerrainDemoFrameListener(this);
  root->addFrameListener(frameListener);
  //create a scene node and entity. entities all must have names
  //createEntity
  
  int i;
  for(i=0;i<1000;i++){
	  Ogre::SceneNode* sn = sceneManager -> getRootSceneNode()->createChildSceneNode("sn"+Ogre::StringConverter::toString(i));
	  Ogre::Entity* sphere = sceneManager ->createEntity("sphere"+Ogre::StringConverter::toString(i),"sphere.mesh");
	  sn->attachObject(sphere);
	  sn->scale(Ogre::Vector3(10.0f));
	  int r;
	  int r2;
	  r=rand();
	  r2=rand();
	  //srand(time());
	  sn->setPosition(r%1500,getTerrainHeightAt(r%1500,r2%1500)+15.0f,r2%1500);
	  sn->setVisible(true);
  }
  
	 

 
  return true;
}
