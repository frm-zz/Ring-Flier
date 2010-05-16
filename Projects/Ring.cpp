#include "Ring.h"
#include "RingFlyer.h"
#include "Ogre.h"
#include "EnemyState.h"
const float Ring::CHASE_VELOCITY=0.50f;
const float Ring::ACTIVATION_RADIUS=30.0f;
const float Ring::RELAX_TIME=3;
const float Ring::KILL_RADIUS=500.0f;
Ring::Ring(Ogre::String name, RingFlyer* flyer):flyer(flyer)
{
	position.x=(rand()%5000);
	
	position.z=(rand()%5000);
	//position.y=flyer->getTerrainHeightAt(position.x,position.z)+15.0f;
	position.y=(rand()%500)+flyer->getTerrainHeightAt(position.x,position.z)+100.0f;

	Ogre::SceneNode* sn = flyer->getSceneManager()->getRootSceneNode()->createChildSceneNode("sn"+name);
		Ogre::Entity* ring = flyer->getSceneManager()->createEntity(name,"Torus.mesh");
		//ring->setMaterialName("ring");
		sn->attachObject(ring);
		sn->scale(Ogre::Vector3(015.10f,015.10f,015.10f));
		sn->setPosition(position);
		sn->setVisible(true);
		sn->setOrientation(Ogre::Quaternion(Ogre::Radian(30.0f), Ogre::Vector3::UNIT_Z));
		sn->setDirection(rand()%10,rand()%10,rand()%10,Ogre::Node::TransformSpace::TS_LOCAL,Ogre::Vector3::NEGATIVE_UNIT_Z);
		sphereName=name;
		chaseTime=0.0;
}

Ring::~Ring(void)
{
	delete this;
}
Ogre::Vector3 position;



bool Ring::inRange(const Ogre::Vector3 pos, float r)const{
	if(position.squaredDistance(pos)<=(r*r)){
		return true;
	}
	else{ return false;}
}

void Ring::moveTowards(const Ogre::Vector3 pos, float velocity, float elapsedTime){
	Ogre::Vector3 direction=pos-position;
	Ogre::Vector3 enemyMove;
	enemyMove.x=velocity*elapsedTime*direction.x;
	enemyMove.z=velocity*elapsedTime*direction.z;
	position.x+=enemyMove.x;
	position.z+=enemyMove.z;
	position.y=flyer->getTerrainHeightAt(position.x,position.z)+15.0f;
	Ogre::String nodeName="sn"+sphereName;
	flyer->getSceneManager()->getSceneNode(nodeName)->setPosition(position);
}

bool Ring::update(float elapsedTime){
	if (Ring::inRange(flyer->getSceneManager()->getSceneNode("shipNode")->getPosition(),Ring::ACTIVATION_RADIUS)){
		//Ring::moveTowards(flyer->getCamera()->getPosition(),Ring::CHASE_VELOCITY,elapsedTime);
		//Ring::chaseTime=Ring::RELAX_TIME;
		flyer->getSceneManager()->getEntity(sphereName)->setMaterialName("Active_Sphere");
	}
	else if(chaseTime>0.0){
		//Ring::moveTowards(flyer->getCamera()->getPosition(),Ring::CHASE_VELOCITY,elapsedTime);
		Ring::chaseTime-=elapsedTime;
		//flyer->getSceneManager()->getEntity(sphereName)->setMaterialName("Relaxing_Sphere");
	}
	else{
		//flyer->getSceneManager()->getEntity(sphereName)->setMaterialName("Inactive_Sphere");
	}
	if (Ring::inRange(flyer->getSceneManager()->getSceneNode("shipNode")->getPosition(),Ring::KILL_RADIUS)){
		//return false;
	}
	return true;
}

