#include "Ship.h"
#include "TerrainDemo.h"
#include "Ogre.h"

Ship::Ship(TerrainDemo* demo):demo(demo)
{
			node="shipNode";
	shipPosition.x=demo->getCamera()->getPosition().x;
		shipPosition.y=demo->getCamera()->getPosition().y;
			shipPosition.z=demo->getCamera()->getPosition().z-30.0f;
	Ogre::SceneNode* shipNode = demo->getSceneManager()->getRootSceneNode()->createChildSceneNode(node);
		Ogre::Entity* shipEnt = demo->getSceneManager()->createEntity("shipEnt","razor.mesh");
		shipEnt->setMaterialName("RZR-002");
		
		shipNode->attachObject(shipEnt);
		shipNode->setPosition(Ogre::Vector3(1200.0f,600.0f,1200.0f));
		shipNode->scale(0.05f,0.05f,0.05f);
		shipNode->setVisible(true);
		
		//shipNode->setInheritOrientation(false);
		//shipNode->setOrientation(demo->getCamera()->getOrientation());
		
}
Ogre::Vector3 shipPosition;
Ship::~Ship(void)
{
}
void Ship::setPosition(Ogre::Vector3 position){
shipPosition=position;
//demo->getSceneManager()->getSceneNode(node)->setPosition(shipPosition);
demo->getSceneManager()->getSceneNode(node)->translate(demo->getSceneManager()->getSceneNode(node)->getLocalAxes(),position,Ogre::Node::TS_PARENT);
}
void Ship::setOrientation(float pitch,float roll){
	demo->getSceneManager()->getSceneNode(node)->pitch(Ogre::Radian(pitch));
	demo->getSceneManager()->getSceneNode(node)->roll(Ogre::Radian(roll));
		//demo->getSceneManager()->getSceneNode(node)->setDirection(Ogre::Vector3(demo->getSceneManager()->getSceneNode(node)->getOrientation().zAxis()),Ogre::Node::TS_LOCAL,Ogre::Vector3::NEGATIVE_UNIT_Z);

	//std::cout << pitch <<" "<<roll<<std::endl;
}
Ogre::Vector3 Ship::getPosition(){
	return demo->getSceneManager()->getSceneNode(node)->getPosition();
}
Ogre::Vector3 Ship::getOrientation(){
	//return demo->getSceneManager()->getSceneNode(node)->getor
	return Ogre::Vector3::UNIT_Z;
}