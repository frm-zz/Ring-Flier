// RingFlier.cpp


#include "../Level.h"
#include "RingFlier.h"
#include "RingFlierFrameListener.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Ring.h"
#include "../Ship.h"
#include "Ogre.h"
#include "SoundManager.h"

RingFlier::RingFlier() : root(new Ogre::Root()), frameListener(NULL), raySceneQuery(NULL) {
}

RingFlier::~RingFlier() {
	if (frameListener != NULL)
		delete frameListener;
	if (raySceneQuery != NULL)
		delete raySceneQuery;
	sceneManager->clearScene();
	delete root;
}

float RingFlier::getTerrainHeightAt(float x, float z) {
	terrainRay.setOrigin(Ogre::Vector3(x, 1000.0f, z));
	raySceneQuery->setRay(terrainRay);
	Ogre::RaySceneQueryResult& queryResult = raySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator qi  = queryResult.begin();
	return (qi != queryResult.end() && qi->worldFragment) ? qi->worldFragment->singleIntersection.y : 0.0f;
}



void RingFlier::adjustCameraHeightToTerrain() {
	const Ogre::Vector3& cameraPos = camera->getPosition();
	camera->setPosition(cameraPos.x, getTerrainHeightAt(cameraPos.x, cameraPos.z) + 15.0f, cameraPos.z);
}

void RingFlier::init() {
	if (setup())
		root->startRendering();
}

bool RingFlier::setup() {
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
	//Camera has no initial position, it gets placed when the ship is placed

	// create viewport
	Ogre::Viewport* vp = renderWindow->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0.3f,0.5f,0.5f));
	camera->setAspectRatio(vp->getActualWidth()/(float)vp->getActualHeight());
	camera->setFOVy(Ogre::Radian(65.0f*Ogre::Math::PI/180.0f));

	terrainRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);
	raySceneQuery = sceneManager->createRayQuery(terrainRay);
	
	Ship* ship= new Ship(this);

	cameraNode= sceneManager->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-700.0f));
	cameraNode->setAutoTracking(true,sceneManager->getSceneNode("shipNode"));
	cameraNode->attachObject(camera);

	frameListener = new RingFlierFrameListener(this,ship);
	root->addFrameListener(frameListener);

	Level* level = new Level(3,this);
	
	//////Ship Engine particle
	Ogre::ParticleSystem* pSysEngine = sceneManager->createParticleSystem("pSysEngine","Examples/JetEngine1");
	sceneManager->getSceneNode("shipNode")->createChildSceneNode("engineNode",Ogre::Vector3(-8.0f,0.0f,-10.0f));
	sceneManager->getSceneNode("engineNode")->attachObject(pSysEngine);
	
	/////Particle for going through a ring and increasing score
	Ogre::ParticleSystem* pSysScore = sceneManager->createParticleSystem("pSysScore","PEExamples/ringTest");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysScore"));
	sceneManager->getParticleSystem("pSysScore")->getEmitter(0)->setEnabled(false);

	//////Nodes placed at the boundaries of the level, used to make the wall effects
	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode1",Ogre::Vector3(2500.0f,500.0f,0.0f));
	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode2",Ogre::Vector3(2500.0f,500.0f,5000.0f));
	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode3",Ogre::Vector3(0.0f,500.0f,2500.0f));
	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode4",Ogre::Vector3(5000.0f,500.0f,2500.0f));
	//////Node created at the top of the level for making rain
	sceneManager->getRootSceneNode()->createChildSceneNode("rainNode",Ogre::Vector3(2500.0f,2000.0f,2500.0f));

	/*SoundManager* soundMgr;
	soundMgr = SoundManager::createManager();

	std::cout << soundMgr->listAvailableDevices();

	soundMgr->init();
	soundMgr->setAudioPath( (char*) ".\\" );

	// Just for testing
	unsigned int audioId=0;
	soundMgr->loadAudio( "Explosion.wav", &audioId,true);
	soundMgr->setSoundPosition(audioId,Ogre::Vector3(2500,500,2500));
	soundMgr->setListenerPosition(camera->getPosition(),Ogre::Vector3(0.0,0.0,0.0),Ogre::Quaternion::IDENTITY);
	soundMgr->playAudio( audioId,false );
	*/

	return true;
}
void RingFlier::createRings(int n){
	int i;
	e=new Ring*[n];
	for (i=0;i<n;i++){
		e[i]=new Ring(Ogre::StringConverter::toString(i),this);
	}
}
void RingFlier::destroyRings(int n){
	int i;
	for (i=0;i<n;i++){
		sceneManager->getRootSceneNode()->removeAndDestroyChild("sn" + Ogre::StringConverter::toString(i));
	}
}


void RingFlier::createNextLevel(int x){

	sceneManager->destroyAllEntities();
	sceneManager->destroyAllParticleSystems();

	Level* level = new Level(x,this);

	sceneManager->getRootSceneNode()->removeAndDestroyChild("shipNode");

	delete ship;

	Ship* ship= new Ship(this);

	cameraNode= sceneManager->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-700.0f));
	cameraNode->setAutoTracking(true,sceneManager->getSceneNode("shipNode"));
	cameraNode->attachObject(camera);

	frameListener->setShip(ship);
	///////create engine effect again
	Ogre::ParticleSystem* pSysEngine = sceneManager->createParticleSystem("pSysEngine","Examples/JetEngine1");
	sceneManager->getSceneNode("shipNode")->createChildSceneNode("engineNode",Ogre::Vector3(-8.0f,0.0f,-10.0f));
	sceneManager->getSceneNode("engineNode")->attachObject(pSysEngine);
	Ogre::ParticleSystem* pSysScore = sceneManager->createParticleSystem("pSysScore","PEExamples/ringTest");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysScore"));
	sceneManager->getParticleSystem("pSysScore")->getEmitter(0)->setEnabled(false);
}

Ogre::Vector3 RingFlier::getShipPosition(){
	return RingFlier::ship->getPosition();
}

void RingFlier::scoreEffect(){
	sceneManager->getParticleSystem("pSysScore")->getEmitter(0)->setEnabled(true);
}

void RingFlier::deadEffect(){
	Ogre::ParticleSystem* pSysDead1 = sceneManager->createParticleSystem("pSysDead1","PEExamples/shipFlame");
	Ogre::ParticleSystem* pSysDead2 = sceneManager->createParticleSystem("pSysDead2","Examples/Smoke");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysDead1"));
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysDead2"));
}

void RingFlier::explosion(){
	Ogre::ParticleSystem* pSysExpl = sceneManager->createParticleSystem("pSysExpl","PEExamples/shipExpl");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysExpl"));
}
