#include "Ship.h"
#include "RingFlyer.h"
#include "Ogre.h"

Ship::Ship(RingFlyer* flyer):flyer(flyer)
{
			node="shipNode";
	
	Ogre::SceneNode* shipNode = flyer->getSceneManager()->getRootSceneNode()->createChildSceneNode(node);
		Ogre::Entity* shipEnt = flyer->getSceneManager()->createEntity("shipEnt","razor.mesh");
		shipEnt->setMaterialName("RZR-002");
		
		shipNode->attachObject(shipEnt);
		shipNode->setPosition(Ogre::Vector3(1200.0f,flyer->getTerrainHeightAt(1200,1200)+1000.0f,1200.0f));
		shipNode->scale(0.05f,0.05f,0.05f);
		shipNode->setVisible(true);
		shipNode->showBoundingBox(true);
		//shipNode->setInheritOrientation(false);
		shipNode->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-90)),Ogre::Vector3::UNIT_X));
		
}
Ogre::Vector3 shipPosition;
Ship::~Ship(void)
{
}
void Ship::setPosition(Ogre::Vector3 position){
shipPosition=position;
//flyer->getSceneManager()->getSceneNode(node)->setPosition(shipPosition);
flyer->getSceneManager()->getSceneNode(node)->translate(flyer->getSceneManager()->getSceneNode(node)->getLocalAxes(),position,Ogre::Node::TS_PARENT);
}
void Ship::setOrientation(float pitch,float roll){
	flyer->getSceneManager()->getSceneNode(node)->pitch(Ogre::Radian(pitch));
	flyer->getSceneManager()->getSceneNode(node)->roll(Ogre::Radian(roll));
		//flyer->getSceneManager()->getSceneNode(node)->setDirection(Ogre::Vector3(flyer->getSceneManager()->getSceneNode(node)->getOrientation().zAxis()),Ogre::Node::TS_LOCAL,Ogre::Vector3::NEGATIVE_UNIT_Z);

	//std::cout << pitch <<" "<<roll<<std::endl;
}
Ogre::Vector3 Ship::getPosition(){
	return flyer->getSceneManager()->getSceneNode(node)->getPosition();
}
Ogre::Vector3 Ship::getOrientation(){
	//return flyer->getSceneManager()->getSceneNode(node)->getor
	return Ogre::Vector3::UNIT_Z;
}