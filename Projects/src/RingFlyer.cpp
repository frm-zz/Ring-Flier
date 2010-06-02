// RingFlyer.cpp


#include "../Level.h"
#include "RingFlyer.h"
#include "RingFlyerFrameListener.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Ring.h"
#include "../Ship.h"
#include "Ogre.h"
//#include "OgreParticleEmitter.h"
//#include <OgreTextAreaOverlayElement.h>
//#include <OgreFontManager.h>


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

	cameraNode= sceneManager->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-700.0f));
	cameraNode->setAutoTracking(true,sceneManager->getSceneNode("shipNode"));
	cameraNode->attachObject(camera);
	//Ogre::Entity* test = sceneManager->createEntity("test","sphere.mesh");
	//cameraNode->attachObject(test);
	//cameraNode->scale(Ogre::Vector3(0.1f));
	//cameraNode->setVisible(true);
	//cameraNode->setFixedYawAxis(true);
	//cameraNode->setInheritOrientation(true);
	
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
		Ogre::ParticleSystem* pSysEngine = sceneManager->createParticleSystem("pSysEngine","Examples/JetEngine1");
		sceneManager->getSceneNode("shipNode")->createChildSceneNode("engineNode",Ogre::Vector3(-8.0f,0.0f,-10.0f));
	
	sceneManager->getSceneNode("engineNode")->attachObject(pSysEngine);
		Ogre::ParticleSystem* pSysScore = sceneManager->createParticleSystem("pSysScore","PEExamples/ringTest");
sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysScore"));
	sceneManager->getParticleSystem("pSysScore")->getEmitter(0)->setEnabled(false);
	//Ogre::ParticleSystem* pSysShimmer = sceneManager->createParticleSystem("ringShimmer","PEExamples/ringShimmer");
	//sceneManager->getSceneNode("testNode2")->attachObject(sceneManager->getParticleSystem("ringShimmer"));

	//pSys->addEmitter("Point");
	//sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(sceneManager->createParticleSystem("Fountain", "Examples/PurpleFountain"));
	
	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode1",Ogre::Vector3(2500.0f,500.0f,0.0f));

		sceneManager->getRootSceneNode()->createChildSceneNode("wallNode2",Ogre::Vector3(2500.0f,500.0f,5000.0f));

		sceneManager->getRootSceneNode()->createChildSceneNode("wallNode3",Ogre::Vector3(0.0f,500.0f,2500.0f));

		sceneManager->getRootSceneNode()->createChildSceneNode("wallNode4",Ogre::Vector3(5000.0f,500.0f,2500.0f));
	
sceneManager->getRootSceneNode()->createChildSceneNode("rainNode",Ogre::Vector3(2500.0f,2000.0f,2500.0f));
	return true;
}
void RingFlyer::createRings(int n){
	int i;
	e=new Ring*[n];
	//std::cout << "e=new Ring*[n]; "<< std::endl;
	for (i=0;i<n;i++){
		//std::cout << "trying to make a ring "<< std::endl;
		e[i]=new Ring(Ogre::StringConverter::toString(i),this);
		//std::cout << "made a ring "<< std::endl;
	}
}
void RingFlyer::destroyRings(int n){
	int i;
	//std::cout << "inside destroyRings"<< std::endl;
	for (i=0;i<n;i++){
		sceneManager->getRootSceneNode()->removeAndDestroyChild("sn" + Ogre::StringConverter::toString(i));

	//	delete sceneManager->getParticleSystem(Ogre::StringConverter::toString(i)+"p");
		//delete e[i];
		//e[i]->~Ring();
	}
	std::cout << "inside destroyRings"<< std::endl;
}


void RingFlyer::createNextLevel(int x){
	//std::cout << "here1!!!!"<< std::endl;
	//delete level;
	//std::cout << "here2!!!!"<< std::endl;
	//level->~Level();
	//std::cout << "here!!!!"<< std::endl;
	//sceneManager->clearScene();

	//sceneManager->getSceneNode("shipNode")->
	sceneManager->destroyAllEntities();
	sceneManager->destroyAllParticleSystems();
		//Ship* ship= new Ship(this);
	//destroyRings(50);
	//std::cout << "after destroyAllEnts"<< std::endl;
	//cameraNode= sceneManager->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-380.0f));
	//cameraNode->setAutoTracking(true,sceneManager->getSceneNode("shipNode"));
	//cameraNode->attachObject(camera);
	Level* level = new Level(x,this);
	//std::cout << "here3!!!!"<< std::endl;
	//camera->setPosition(707.0f, getTerrainHeightAt(707.0f,528.0f), 528.0f);
	//std::cout << "setCameraPos"<< std::endl;

	sceneManager->getRootSceneNode()->removeAndDestroyChild("shipNode");
	
	delete ship;
	//std::cout << "deleted ship"<< std::endl;
	Ship* ship= new Ship(this);
	//std::cout << "made a new ship"<< std::endl;
	cameraNode= sceneManager->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-700.0f));
	//std::cout << "make a camera node"<< std::endl;
	cameraNode->setAutoTracking(true,sceneManager->getSceneNode("shipNode"));
	//std::cout << "autotrack"<< std::endl;
	cameraNode->attachObject(camera);
	//std::cout << "attached"<< std::endl;

	/*delete frameListener;
	frameListener = new RingFlyerFrameListener(this,ship); //this was a quick fix...could not delete and then just make a setShip() or something

	root->addFrameListener(frameListener);*/
	frameListener->setShip(ship);
		Ogre::ParticleSystem* pSysEngine = sceneManager->createParticleSystem("pSysEngine","Examples/JetEngine1");
		sceneManager->getSceneNode("shipNode")->createChildSceneNode("engineNode",Ogre::Vector3(-8.0f,0.0f,-10.0f));
	//	sceneManager->getRootSceneNode()->createChildSceneNode("testNode2",Ogre::Vector3(2500.0f,600.0f,2500.0f));
	sceneManager->getSceneNode("engineNode")->attachObject(pSysEngine);
		Ogre::ParticleSystem* pSysScore = sceneManager->createParticleSystem("pSysScore","PEExamples/ringTest");
sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysScore"));
	sceneManager->getParticleSystem("pSysScore")->getEmitter(0)->setEnabled(false);
	
	//	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode1",Ogre::Vector3(2500.0f,500.0f,0.0f));
		Ogre::ParticleSystem* pSysWall1 = sceneManager->createParticleSystem("pSysWall1","PEExamples/wall1");
sceneManager->getSceneNode("wallNode1")->attachObject(sceneManager->getParticleSystem("pSysWall1"));
	//	sceneManager->getRootSceneNode()->createChildSceneNode("wallNode2",Ogre::Vector3(2500.0f,500.0f,5000.0f));
		Ogre::ParticleSystem* pSysWall2 = sceneManager->createParticleSystem("pSysWall2","PEExamples/wall1");
sceneManager->getSceneNode("wallNode2")->attachObject(sceneManager->getParticleSystem("pSysWall2"));
		//sceneManager->getRootSceneNode()->createChildSceneNode("wallNode3",Ogre::Vector3(0.0f,500.0f,2500.0f));
		Ogre::ParticleSystem* pSysWall3 = sceneManager->createParticleSystem("pSysWall3","PEExamples/wall2");
sceneManager->getSceneNode("wallNode3")->attachObject(sceneManager->getParticleSystem("pSysWall3"));
		//sceneManager->getRootSceneNode()->createChildSceneNode("wallNode4",Ogre::Vector3(5000.0f,500.0f,2500.0f));
		Ogre::ParticleSystem* pSysWall4 = sceneManager->createParticleSystem("pSysWall4","PEExamples/wall2");
sceneManager->getSceneNode("wallNode4")->attachObject(sceneManager->getParticleSystem("pSysWall4"));
}
Ogre::Vector3 RingFlyer::getShipPosition(){
	return RingFlyer::ship->getPosition();
}
void RingFlyer::scoreEffect(){


	sceneManager->getParticleSystem("pSysScore")->getEmitter(0)->setEnabled(true);
	

}
void RingFlyer::deadEffect(){

	Ogre::ParticleSystem* pSysDead1 = sceneManager->createParticleSystem("pSysDead1","PEExamples/shipFlame");
	Ogre::ParticleSystem* pSysDead2 = sceneManager->createParticleSystem("pSysDead2","Examples/Smoke");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysDead1"));
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysDead2"));
}
void RingFlyer::explosion(){
Ogre::ParticleSystem* pSysExpl = sceneManager->createParticleSystem("pSysExpl","PEExamples/shipExpl");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysExpl"));
}
