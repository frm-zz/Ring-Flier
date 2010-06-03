#include "Ship.h"
#include "RingFlier.h"
#include "Ogre.h"
Ogre::Vector3 shipPosition;
Ship::Ship(RingFlier* flier):flier(flier)
{
	nodeName="shipNode";

	Ogre::SceneNode* shipNode = flier->getSceneManager()->getRootSceneNode()->createChildSceneNode(nodeName);
	Ogre::Entity* shipEnt = flier->getSceneManager()->createEntity("shipEnt","razor.mesh");
	shipEnt->setMaterialName("RZR-002");

	shipNode->attachObject(shipEnt);
	shipNode->setPosition(Ogre::Vector3(1200.0f,flier->getTerrainHeightAt(1200,1200)+1000.0f,1200.0f));
	shipNode->scale(0.05f,0.05f,0.05f);
	shipNode->setVisible(true);
}

Ship::~Ship(void)
{
}

void Ship::setPosition(Ogre::Vector3 position){
	shipPosition=position;
	flier->getSceneManager()->getSceneNode(nodeName)->translate(flier->getSceneManager()->getSceneNode(nodeName)->getLocalAxes(),position,Ogre::Node::TS_PARENT);
}

void Ship::setOrientation(float pitch,float roll){
	flier->getSceneManager()->getSceneNode(nodeName)->pitch(Ogre::Radian(pitch));
	flier->getSceneManager()->getSceneNode(nodeName)->roll(Ogre::Radian(roll));
}

Ogre::Vector3 Ship::getPosition(){
	return flier->getSceneManager()->getSceneNode(nodeName)->getPosition();
}
