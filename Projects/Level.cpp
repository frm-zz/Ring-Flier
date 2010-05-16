#include "Level.h"
#include "RingFlyer.h"
#include "Ogre.h"
Level::Level(int x, RingFlyer* flyer)//:flyer(flyer)
{
	if (x==3){
		//ONLY USED FOR INITIALIZATION
		//flyer->destroyRings(200);
		flyer->getSceneManager()->setWorldGeometry("terrain1.cfg");
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_stormy",100);
		flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flyer->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		flyer->createRings(50);
	}
	else if (x==0){
		
		flyer->destroyRings(200);
		flyer->getSceneManager()->setWorldGeometry("terrain1.cfg");
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_stormy",50);
		flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 300.0f);
		flyer->createRings(50);
	}
	else if (x==1){
		flyer->destroyRings(50);
		flyer->getSceneManager()->setWorldGeometry("terrain2.cfg");
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_evening",50);
		flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(1.0f, 0.0f, 0.5f));
		Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.0f, 0.86f, 0.76f);
		flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);
		flyer->createRings(200);
	}
	else if (x==2){
		flyer->destroyRings(100);
		flyer->getSceneManager()->setWorldGeometry("terrain2.cfg");
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_cloudy_noon",50);
		flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.3f, 0.1f, 0.1f));
		Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.32f, 0.32f);
		flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);
		flyer->createRings(200);
	}
}

Level::~Level(void)
{
	//delete this;
}

Ogre::String currentLevel;
Ogre::String skyBox;



