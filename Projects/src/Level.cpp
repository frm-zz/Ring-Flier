#include "Level.h"
#include "RingFlier.h"
#include "Ogre.h"
Level::Level(int x, RingFlier* flier)//:flier(flier)
{
	Ogre::String currentLevel;
	Ogre::String skyBox;
	if (x==3){
		////////ONLY USED FOR INITIALIZATION
		flier->getSceneManager()->setWorldGeometry("terrainspace.cfg");
		flier->getSceneManager()->setSkyBox(true,"SkyBox_purplenebula",100);
		flier->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = flier->getSceneManager()->createLight("PrimaryLight"); //do we need these?
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flier->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		flier->createRings(50);
	}
	else if (x==0){
		flier->destroyRings(200);
		flier->getSceneManager()->setWorldGeometry("terrainspace.cfg");
		flier->getSceneManager()->setSkyBox(true,"SkyBox_purplenebula",50);
		flier->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
		Ogre::Light* light = flier->getSceneManager()->getLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flier->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		flier->createRings(50);
	}

	else if (x==1){
		flier->destroyRings(50);
		flier->getSceneManager()->setWorldGeometry("terrain2.cfg");
		flier->getSceneManager()->setSkyBox(true,"SkyBox_evening",50);
		Ogre::Light* light = flier->getSceneManager()->getLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flier->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		flier->createRings(100);

		////Rain
		Ogre::ParticleSystem* pSysRain = flier->getSceneManager()->createParticleSystem("pSysRain","Examples/Rain");
		flier->getSceneManager()->getSceneNode("rainNode")->attachObject(flier->getSceneManager()->getParticleSystem("pSysRain"));
		pSysRain->fastForward(3);
		pSysRain->setDefaultNonVisibleUpdateTimeout(3);

		//////////////Make Level Walls////////////////////
		Ogre::ParticleSystem* pSysWall1 = flier->getSceneManager()->createParticleSystem("pSysWall1","PEExamples/wall1");
		flier->getSceneManager()->getSceneNode("wallNode1")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall1"));

		Ogre::ParticleSystem* pSysWall2 = flier->getSceneManager()->createParticleSystem("pSysWall2","PEExamples/wall1");
		flier->getSceneManager()->getSceneNode("wallNode2")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall2"));

		Ogre::ParticleSystem* pSysWall3 = flier->getSceneManager()->createParticleSystem("pSysWall3","PEExamples/wall2");
		flier->getSceneManager()->getSceneNode("wallNode3")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall3"));

		Ogre::ParticleSystem* pSysWall4 = flier->getSceneManager()->createParticleSystem("pSysWall4","PEExamples/wall2");
		flier->getSceneManager()->getSceneNode("wallNode4")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall4"));

	}
	else if (x==2){
		flier->destroyRings(100);
		flier->getSceneManager()->setWorldGeometry("terrain3.cfg");
		flier->getSceneManager()->setSkyBox(true,"SkyBox_cloudy_noon",50);
		Ogre::Light* light = flier->getSceneManager()->getLight("PrimaryLight");
		light->setPosition(20.0f, 80.0f, 50.0f);
		Ogre::ColourValue fogColor(0.93f, 0.86f, 0.76f);
		flier->getSceneManager()->setFog(Ogre::FOG_EXP, fogColor, 0.00001f, 20.0f, 300.0f);
		flier->createRings(200);

		//////////////Make Level Walls////////////////////
		Ogre::ParticleSystem* pSysWall1 = flier->getSceneManager()->createParticleSystem("pSysWall1","PEExamples/wall1");
		flier->getSceneManager()->getSceneNode("wallNode1")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall1"));

		Ogre::ParticleSystem* pSysWall2 = flier->getSceneManager()->createParticleSystem("pSysWall2","PEExamples/wall1");
		flier->getSceneManager()->getSceneNode("wallNode2")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall2"));

		Ogre::ParticleSystem* pSysWall3 = flier->getSceneManager()->createParticleSystem("pSysWall3","PEExamples/wall2");
		flier->getSceneManager()->getSceneNode("wallNode3")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall3"));

		Ogre::ParticleSystem* pSysWall4 = flier->getSceneManager()->createParticleSystem("pSysWall4","PEExamples/wall2");
		flier->getSceneManager()->getSceneNode("wallNode4")->attachObject(flier->getSceneManager()->getParticleSystem("pSysWall4"));
	}
}

Level::~Level(void)
{
}
