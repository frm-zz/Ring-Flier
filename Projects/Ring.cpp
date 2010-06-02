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
	check=true;
	//std::cout << "inside new ring"<< std::endl;
	position.x=(rand()%5000);
	
	position.z=(rand()%5000);
	//position.y=flyer->getTerrainHeightAt(position.x,position.z)+15.0f;
	position.y=(rand()%500)+flyer->getTerrainHeightAt(position.x,position.z)+100.0f;
	//std::cout << "set ring pos" << name << std::endl;

	//Ogre::SceneNode* hello = flyer->getSceneManager()->getRootSceneNode();
	//->createChildSceneNode("hello"+name);
		//std::cout << "got root"<< hello << std::endl;
	Ogre::SceneNode* sn = flyer->getSceneManager()->getRootSceneNode()->createChildSceneNode("sn"+name);
	//std::cout << "created sceneNode"<< std::endl;
		Ogre::Entity* ring = flyer->getSceneManager()->createEntity(name,"Torus.mesh");
		//std::cout << "set ring name"<< std::endl;
		//ring->setMaterialName("ring");
		sn->attachObject(ring);
		sn->scale(Ogre::Vector3(015.10f,015.10f,015.10f));
		sn->setPosition(position);
		sn->setVisible(true);
		sn->setOrientation(Ogre::Quaternion(Ogre::Radian(30.0f), Ogre::Vector3::UNIT_Z));
		sn->setDirection(rand()%10,rand()%10,rand()%10,Ogre::Node::TransformSpace::TS_LOCAL,Ogre::Vector3::NEGATIVE_UNIT_Z);
		sphereName=name;
		chaseTime=0.0;
		Ogre::ParticleSystem* pSysRing = flyer->getSceneManager()->createParticleSystem(sphereName+'p',"PEExamples/ringShimmer");
		flyer->getSceneManager()->getSceneNode("sn"+sphereName)->attachObject(pSysRing);
		
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

int Ring::update(float elapsedTime){
	if (this->check){
	if (Ring::inRange(flyer->getSceneManager()->getSceneNode("shipNode")->getPosition(),Ring::ACTIVATION_RADIUS)){

		flyer->getSceneManager()->getEntity(sphereName)->setMaterialName("Active_Sphere");
		this->check=false;

		flyer->scoreEffect();
		flyer->getSceneManager()->getParticleSystem(sphereName+'p')->getEmitter(0)->setEnabled(false);
		return 1;
		
	}

	
	return 0;
}
	return 0;
}

