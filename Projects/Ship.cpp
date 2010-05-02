#include "Ship.h"
#include "TerrainDemo.h"
#include "Ogre.h"

Ship::Ship(TerrainDemo* demo):demo(demo)
{
			node="shipNode";
	shipPosition.x=demo->getCamera()->getPosition().x-20.0f;
		shipPosition.y=demo->getCamera()->getPosition().y;
			shipPosition.z=demo->getCamera()->getPosition().z-30.0f;
	Ogre::SceneNode* shipNode = demo->getSceneManager()->getRootSceneNode()->createChildSceneNode(node);
		Ogre::Entity* shipEnt = demo->getSceneManager()->createEntity("shipEnt","sphere.mesh");
		shipNode->attachObject(shipEnt);
		shipNode->setPosition(shipPosition);
		shipNode->scale(0.05f,0.05f,0.05f);
		shipNode->setVisible(true);
		shipNode->setOrientation(Ogre::Quaternion(Ogre::Radian(30.0f), Ogre::Vector3::UNIT_Z));

}
Ogre::Vector3 shipPosition;
Ship::~Ship(void)
{
}
void Ship::setPosition(Ogre::Vector3 position){
shipPosition=position;
demo->getSceneManager()->getSceneNode(node)->setPosition(shipPosition);
}
Ogre::Vector3 Ship::getPosition(){
	return shipPosition;
}