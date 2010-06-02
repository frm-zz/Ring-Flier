#include "Level.h"
#include "RingFlyer.h"
#include "Ogre.h"
Level::Level(int x, RingFlyer* flyer)//:flyer(flyer)
{
	if (x==3){
		//std::cout << "inside x==3 "<< std::endl;
		//ONLY USED FOR INITIALIZATION
		//flyer->destroyRings(200);
		flyer->getSceneManager()->setWorldGeometry("terrainspace.cfg");
		//std::cout << "setWorldGeom "<< std::endl;
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_purplenebula",100);
		//std::cout << "setSkyBox "<< std::endl;
		flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight"); //do we need these?
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flyer->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		//std::cout << "outside x==3 "<< std::endl;
		flyer->createRings(50);
		
		/*flyer->cameraNode= flyer->getSceneManager()->getSceneNode("shipNode")->createChildSceneNode("cameraNode",Ogre::Vector3(0.0,0.0,-380.0f));
		flyer->cameraNode->setAutoTracking(true,flyer->getSceneManager()->getSceneNode("shipNode"));
		flyer->cameraNode->attachObject(flyer->camera);*/
		
	}
	else if (x==0){
		
		flyer->destroyRings(200);
		flyer->getSceneManager()->setWorldGeometry("terrainspace.cfg");
		
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_purplenebula",50);
		flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	//	Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight");
		Ogre::Light* light = flyer->getSceneManager()->getLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
	//	Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flyer->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		//flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 300.0f);
		flyer->createRings(50);
		

	}
	else if (x==1){
		flyer->destroyRings(50);
		flyer->getSceneManager()->setWorldGeometry("terrain2.cfg");
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_evening",50);
		//flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(1.0f, 0.0f, 0.5f));
		//Ogre::Light* light = flyer->getSceneManager()->createLight("PrimaryLight");
		Ogre::Light* light = flyer->getSceneManager()->getLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		//Ogre::ColourValue fogColor(0.0f, 0.86f, 0.76f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flyer->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		//flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);
		flyer->createRings(100);
		////Rain
		
		Ogre::ParticleSystem* pSysRain = flyer->getSceneManager()->createParticleSystem("pSysRain","Examples/Rain");
flyer->getSceneManager()->getSceneNode("rainNode")->attachObject(flyer->getSceneManager()->getParticleSystem("pSysRain"));
	}
	else if (x==2){
		flyer->destroyRings(100);
		flyer->getSceneManager()->setWorldGeometry("terrain3.cfg");
		flyer->getSceneManager()->setSkyBox(true,"SkyBox_cloudy_noon",50);
		//flyer->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.3f, 0.1f, 0.1f));
		Ogre::Light* light = flyer->getSceneManager()->getLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		//Ogre::ColourValue fogColor(0.93f, 0.32f, 0.32f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		//flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, fogColor, 0.2, 100.0f, 200.0f);
		flyer->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		flyer->createRings(200);
	}
}

Level::~Level(void)
{
	//delete this;
}

Ogre::String currentLevel;
Ogre::String skyBox;



