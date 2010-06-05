#include "Level.h"
#include "RingFlier.h"
#include "RingFlierFrameListener.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ring.h"
#include "Ship.h"
#include "Ogre.h"
#include "SoundManager.h"
#include <string>

//Sound globals
#define NUM_BUFFERS 205
#define NUM_SOURCES 205
#define NUM_ENVIRONMENTS 1

ALfloat listenerPos[]={500.0,500.0,500.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat	listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};
ALfloat source0Pos[]={ 500.0, 500.0, 500.0};
ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

ALuint	buffer[NUM_BUFFERS];
ALuint	source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];
ALboolean ALtrue;
ALsizei size,freq;
ALenum 	format;
ALvoid 	*data;
int 	ch;
int ambientNum = 201;
int explosionNum = 202;
int clockNum = 203;
bool clockGoing = false;
//end sound globals


RingFlier::RingFlier() : root(new Ogre::Root()), frameListener(NULL), raySceneQuery(NULL) {
}

void RingFlier::setSourcePos(int sourceNum, float xpos, float ypos, float zpos){
	ALfloat tempPos[] = {xpos, ypos, zpos};
	ALfloat tempVel[] = {0.0, 0.0, 0.0};

	std::string filename ="ring" + Ogre::StringConverter().toString(sourceNum%5 +1) + ".wav";
	alutLoadWAVFile((ALbyte*)filename.c_str(),&format,&data,&size,&freq,&ALtrue);
    alBufferData(buffer[sourceNum],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

	alSourcef(source[sourceNum],AL_PITCH,1.0f);
    alSourcef(source[sourceNum],AL_GAIN,0.4f);
	alSourcef(source[sourceNum],AL_ROLLOFF_FACTOR, 20.0f);
	alSourcef(source[sourceNum],AL_MAX_DISTANCE, 5000.0f);
    alSourcefv(source[sourceNum],AL_POSITION,tempPos);
    alSourcefv(source[sourceNum],AL_VELOCITY,tempVel);
    alSourcei(source[sourceNum],AL_BUFFER,buffer[sourceNum]);
    alSourcei(source[sourceNum],AL_LOOPING,AL_TRUE);
}

void RingFlier::setListenerPos(float xpos, float ypos, float zpos){
	ALfloat tempPos[] = {xpos, ypos, zpos};
	ALfloat tempVel[] = {0.0, 0.0, 0.0};
	Ogre::Vector3 tempy, tempz;
	ALfloat tempOrient[] = {0.0, 0.0, 0.0,   0.0, 0.0, 0.0};	
    
	Ogre::Quaternion tempQuat = sceneManager->getSceneNode("shipNode")->getOrientation();
	tempy = tempQuat.yAxis();
	tempz = tempQuat.zAxis();

	tempOrient[0] = tempz.x;
	tempOrient[1] = tempz.y;
	tempOrient[2] = tempz.z;

	tempOrient[3] = 0.0;
	tempOrient[4] = tempy.y;
	tempOrient[5] = 0.0;

	alListenerfv(AL_ORIENTATION,tempOrient);
	alListenerfv(AL_POSITION,tempPos);
    alListenerfv(AL_VELOCITY,tempVel);
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

	// create scene manager
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

//sound init
	alutInit(0, NULL);

    alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);
    
    alGetError(); // clear any error messages
    
    if(alGetError() != AL_NO_ERROR) 
    {
        printf("- Error creating buffers !!\n");
        exit(1);
    }
    else
    {
        printf("init() - No errors yet.");

    }
    
    // Generate buffers, or else no sound will happen!
    alGenBuffers(NUM_BUFFERS, buffer);
    alGetError(); /* clear error */
    alGenSources(NUM_SOURCES, source);

    if(alGetError() != AL_NO_ERROR) 
    {
        printf("- Error creating sources !!\n");
        exit(2);
    }
    else
    {
        printf("init - no errors after alGenSources\n");
    }

	//setup for ambient1
	ALfloat tempPos[] = {0, 0, 0};
	ALfloat tempVel[] = {0.0, 0.0, 0.0};	

	alutLoadWAVFile("ambient1.wav",&format,&data,&size,&freq,&ALtrue);
    alBufferData(buffer[ambientNum],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

	alSourcef(source[ambientNum],AL_PITCH,1.0f);
    alSourcef(source[ambientNum],AL_GAIN,0.2f);
    alSourcefv(source[ambientNum],AL_POSITION,tempPos);
    alSourcefv(source[ambientNum],AL_VELOCITY,tempVel);
    alSourcei(source[ambientNum],AL_BUFFER,buffer[ambientNum]);
    alSourcei(source[ambientNum],AL_LOOPING,AL_TRUE);
	alSourcePlay(source[ambientNum]);
	alDistanceModel(AL_LINEAR_DISTANCE);

//end sound init

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

	return true;
}
void RingFlier::createRings(int n){
	int i;
	e=new Ring*[n];
	for (i=0;i<n;i++){
		e[i]=new Ring(Ogre::StringConverter::toString(i),this);
		//setSourcePos(i, sceneManager->getSceneNode("sn"+ e[i]->ringName)->getPosition().x,sceneManager->getSceneNode("sn"+ e[i]->ringName)->getPosition().y, sceneManager->getSceneNode("sn"+ e[i]->ringName)->getPosition().z);
		setSourcePos(i, e[i]->position.x, e[i]->position.y, e[i]->position.z);
		//std::cout << e[i]->position.x<<" "<< e[i]->position.y<<" "<< e[i]->position.z <<"\n";
		//std::cout << "SLDKFJKLGDJHGS "<< i << "\n";
		alSourcePlay(source[i]);
	}
}
void RingFlier::destroyRings(int n){
	int i;
	for (i=0;i<n;i++){
		sceneManager->getRootSceneNode()->removeAndDestroyChild("sn" + Ogre::StringConverter::toString(i));
		alSourceStop((ALuint) i);
	}
}
void RingFlier::createNextLevel(int x){
	clockGoing = false;
	stopClockSound();

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
	explosionSound();
}

void RingFlier::explosion(){
	Ogre::ParticleSystem* pSysExpl = sceneManager->createParticleSystem("pSysExpl","PEExamples/shipExpl");
	sceneManager->getSceneNode("shipNode")->attachObject(sceneManager->getParticleSystem("pSysExpl"));
	explosionSound();
}

void RingFlier::explosionSound(){
ALfloat tempPos[] = {0, 0, 0};
	ALfloat tempVel[] = {0.0, 0.0, 0.0};
	alutLoadWAVFile("Explosion.wav",&format,&data,&size,&freq,&ALtrue);
    alBufferData(buffer[explosionNum],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);

	alSourcef(source[explosionNum],AL_PITCH,1.0f);
    alSourcef(source[explosionNum],AL_GAIN,1.0f);
    alSourcefv(source[explosionNum],AL_POSITION,tempPos);
    alSourcefv(source[explosionNum],AL_VELOCITY,tempVel);
    alSourcei(source[explosionNum],AL_BUFFER,buffer[explosionNum]);
    alSourcei(source[explosionNum],AL_LOOPING,AL_FALSE);
	alSourcePlay(source[explosionNum]);
	alSourceStop(source[clockNum]);
}

void RingFlier::clockSound(){
	if(!clockGoing){
		ALfloat tempPos[] = {0, 0, 0};
		ALfloat tempVel[] = {0.0, 0.0, 0.0};
		alutLoadWAVFile("clock.wav",&format,&data,&size,&freq,&ALtrue);
		alBufferData(buffer[clockNum],format,data,size,freq);
		alutUnloadWAV(format,data,size,freq);

		alSourcef(source[clockNum],AL_PITCH,1.0f);
		alSourcef(source[clockNum],AL_GAIN,2.0f);
		alSourcefv(source[clockNum],AL_POSITION,tempPos);
		alSourcefv(source[clockNum],AL_VELOCITY,tempVel);
		alSourcei(source[clockNum],AL_BUFFER,buffer[clockNum]);
		alSourcei(source[clockNum],AL_LOOPING,AL_TRUE);
		alSourcePlay(source[clockNum]);
		clockGoing = true;
	}

}
void RingFlier::stopClockSound(){
	alSourceStop(source[clockNum]);
	clockGoing = false;
}

