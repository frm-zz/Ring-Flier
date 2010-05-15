// RingFlyer.cpp
// @author Eric D. Wills

#include "../Level.h"
#include "RingFlyer.h"
#include "RingFlyerFrameListener.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Ring.h"
#include "../Ship.h"



RingFlyer::RingFlyer() : root(new Ogre::Root()), frameListener(NULL), raySceneQuery(NULL) {
	//Ship* ship = new Ship(this);
	//cameraNode= sceneManager->getRootSceneNode()->createChildSceneNode("cameraNode");

}

RingFlyer::~RingFlyer() {
	if (frameListener != NULL)
		delete frameListener;
	if (raySceneQuery != NULL)
		delete raySceneQuery;

	delete root;
}

float RingFlyer::getTerrainHeightAt(float x, float z) {
	terrainRay.setOrigin(Ogre::Vector3(x, 1000.0f, z));
	raySceneQuery->setRay(terrainRay);

	Ogre::RaySceneQueryResult& queryResult = raySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator qi  = queryResult.begin();
	return (qi != queryResult.end() && qi->worldFragment) ? qi->worldFragment->singleIntersection.y : 0.0f;
}



void RingFlyer::adjustCameraHeightToTerrain() {
	const Ogre::Vector3& cameraPos = camera->getPosition();
	camera->setPosition(cameraPos.x, getTerrainHeightAt(cameraPos.x, cameraPos.z) + 15.0f, cameraPos.z);
}

void RingFlyer::init() {
	if (setup())

		root->startRendering();
}

bool RingFlyer::setup() {
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
	sceneManager->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);

	// create camera
	printf("creating camera");
	std::cout << "camera";
	camera = sceneManager->createCamera("PrimaryCamera");
	camera->setNearClipDistance(1.0f);
	camera->setFarClipDistance(10000.0f);
	//camera->setPosition(707.0f, 300.0f,528.0f);

	// create viewport
	Ogre::Viewport* vp = renderWindow->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0.3f,0.5f,0.5f));
	camera->setAspectRatio(vp->getActualWidth()/(float)vp->getActualHeight());
	camera->setFOVy(Ogre::Radian(65.0f*Ogre::Math::PI/180.0f));

	terrainRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

	raySceneQuery = sceneManager->createRayQuery(terrainRay);
	Ship* ship= new Ship(this);

	cameraNode= sceneManager->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-380.0f));
	cameraNode->setAutoTracking(true,sceneManager->getSceneNode("shipNode"));
	//Ogre::Entity* test = sceneManager->createEntity("test","sphere.mesh");
	//cameraNode->attachObject(test);
	//cameraNode->scale(Ogre::Vector3(0.1f));
	//cameraNode->setVisible(true);
	//cameraNode->setFixedYawAxis(true);
	//cameraNode->setInheritOrientation(true);
	cameraNode->attachObject(camera);
	//cameraNode->setPosition(camera->getPosition());

	//camera->setAutoTracking(true,sceneManager->getSceneNode("shipNode"),Ogre::Vector3(0.0f,0.0f,0.0f));

	//Ogre::Vector3 hat=ship->getPosition();
	//std::cout <<camera->getPosition() <<std::endl;
	//std::cout << hat << std::endl;
	//ship->setPosition(Ogre::Vector3(hat.x+0.0f,hat.y+0.0f,hat.z-50.0f));
	//std::cout << ship->getPosition() << std::endl;
	frameListener = new RingFlyerFrameListener(this,ship);

	root->addFrameListener(frameListener);
	Level* level = new Level(3,this);


	return true;
}
void RingFlyer::createRings(int n){
	int i;
	e=new Ring*[n];
	for (i=0;i<n;i++){
		e[i]=new Ring(Ogre::StringConverter::toString(i),this);
	}
}
void RingFlyer::destroyRings(int n){
	int i;
	for (i=0;i<n;i++){
		e[i]->~Ring();
	}
}


void RingFlyer::createNextLevel(int x){
	level->~Level();
	sceneManager->clearScene();

	sceneManager->destroyAllEntities();
	Level* level = new Level(x,this);

	camera->setPosition(707.0f, getTerrainHeightAt(707.0f,528.0f), 528.0f);

}
Ogre::Vector3 RingFlyer::getShipPosition(){
	return RingFlyer::ship->getPosition();
}