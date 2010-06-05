#include "Ring.h"
#include "RingFlier.h"
#include "Ogre.h"

const float Ring::ACTIVATION_RADIUS=30.0f;
Ring::Ring(Ogre::String name, RingFlier* flier):flier(flier)
{
	check=true;
	ringName=name;
	position.x=(rand()%5000);
	position.z=(rand()%5000);
	position.y=(rand()%700)+flier->getTerrainHeightAt(position.x,position.z)+100.0f;

	Ogre::SceneNode* sn = flier->getSceneManager()->getRootSceneNode()->createChildSceneNode("sn"+name);
	Ogre::Entity* ring = flier->getSceneManager()->createEntity(name,"Torus.mesh");
	sn->attachObject(ring);
	sn->scale(Ogre::Vector3(015.10f,015.10f,015.10f));
	sn->setPosition(position);
	sn->setVisible(true);
	sn->setOrientation(Ogre::Quaternion(Ogre::Radian(30.0f), Ogre::Vector3::UNIT_Z));
	sn->setDirection(rand()%10,rand()%10,rand()%10,Ogre::Node::TransformSpace::TS_LOCAL,Ogre::Vector3::NEGATIVE_UNIT_Z);
	Ogre::ParticleSystem* pSysRing = flier->getSceneManager()->createParticleSystem(ringName+'p',"PEExamples/ringShimmer");
	flier->getSceneManager()->getSceneNode("sn"+ringName)->attachObject(pSysRing);
}

Ring::~Ring(void)
{
}

bool Ring::inRange(const Ogre::Vector3 pos, float r)const{
	if(position.squaredDistance(pos)<=(r*r)){
		return true;
	}
	else{ return false;}
}

int Ring::update(float elapsedTime){
	if (this->check){
		if (Ring::inRange(flier->getSceneManager()->getSceneNode("shipNode")->getPosition(),Ring::ACTIVATION_RADIUS)){
			flier->getSceneManager()->getEntity(ringName)->setMaterialName("Active_Sphere");
			this->check=false;
			flier->scoreEffect();
			flier->getSceneManager()->getParticleSystem(ringName+'p')->getEmitter(0)->setEnabled(false);
			return 1;
		}
		return 0;
	}
	return 0;
}


