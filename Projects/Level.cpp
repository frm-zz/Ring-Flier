#include "Level.h"
#include "TerrainDemo.h"
#include "Ogre.h"
Level::Level(int x, TerrainDemo* demo)//:demo(demo)
{
	if (x==3){
		//ONLY USED FOR INITIALIZATION
		//demo->destroyEnemies(200);
		demo->getSceneManager()->setWorldGeometry("terrain1.cfg");
		demo->getSceneManager()->setSkyBox(true,"SkyBox_stormy",100);
		demo->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = demo->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		demo->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 200.0f, 300.0f);
		demo->createEnemies(50);
	}
	else if (x==0){
		
		demo->destroyEnemies(200);
		demo->getSceneManager()->setWorldGeometry("terrain1.cfg");
		demo->getSceneManager()->setSkyBox(true,"SkyBox_stormy",50);
		demo->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = demo->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		demo->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 300.0f);
		demo->createEnemies(50);
	}
	else if (x==1){
		demo->destroyEnemies(50);
		demo->getSceneManager()->setWorldGeometry("terrain2.cfg");
		demo->getSceneManager()->setSkyBox(true,"SkyBox_evening",50);
		demo->getSceneManager()->setAmbientLight(Ogre::ColourValue(1.0f, 0.0f, 0.5f));
		Ogre::Light* light = demo->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.0f, 0.86f, 0.76f);
		demo->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);
		demo->createEnemies(200);
	}
	else if (x==2){
		demo->destroyEnemies(100);
		demo->getSceneManager()->setWorldGeometry("terrain2.cfg");
		demo->getSceneManager()->setSkyBox(true,"SkyBox_cloudy_noon",50);
		demo->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.3f, 0.1f, 0.1f));
		Ogre::Light* light = demo->getSceneManager()->createLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.32f, 0.32f);
		demo->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);
		demo->createEnemies(200);
	}
}

Level::~Level(void)
{
}

Ogre::String currentLevel;
Ogre::String skyBox;



