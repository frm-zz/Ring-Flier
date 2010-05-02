#include "Enemy.h"
#include "TerrainDemo.h"
#include "Ogre.h"
#include "EnemyState.h"
const float Enemy::CHASE_VELOCITY=0.50f;
const float Enemy::ACTIVATION_RADIUS=10.0f;
const float Enemy::RELAX_TIME=3;
const float Enemy::KILL_RADIUS=10.0f;
Enemy::Enemy(Ogre::String name, TerrainDemo* demo):demo(demo)
{
	position.x=(rand()%5000);
	
	position.z=(rand()%5000);
	//position.y=demo->getTerrainHeightAt(position.x,position.z)+15.0f;
	position.y=(rand()%500)+demo->getTerrainHeightAt(position.x,position.z);

	Ogre::SceneNode* sn = demo->getSceneManager()->getRootSceneNode()->createChildSceneNode("sn"+name);
		Ogre::Entity* enemy = demo->getSceneManager()->createEntity(name,"sphere.mesh");
		enemy->setMaterialName("Inactive_Sphere");
		sn->attachObject(enemy);
		sn->scale(Ogre::Vector3(0.10f,0.10f,0.10f));
		sn->setPosition(position);
		sn->setVisible(true);
		sn->setOrientation(Ogre::Quaternion(Ogre::Radian(30.0f), Ogre::Vector3::UNIT_Z));
		sphereName=name;
		chaseTime=0.0;
}

Enemy::~Enemy(void)
{
}
Ogre::Vector3 position;



bool Enemy::inRange(const Ogre::Vector3 pos, float r)const{
	if(position.squaredDistance(pos)<=(r*r)){
		return true;
	}
	else{ return false;}
}

void Enemy::moveTowards(const Ogre::Vector3 pos, float velocity, float elapsedTime){
	Ogre::Vector3 direction=pos-position;
	Ogre::Vector3 enemyMove;
	enemyMove.x=velocity*elapsedTime*direction.x;
	enemyMove.z=velocity*elapsedTime*direction.z;
	position.x+=enemyMove.x;
	position.z+=enemyMove.z;
	position.y=demo->getTerrainHeightAt(position.x,position.z)+15.0f;
	Ogre::String nodeName="sn"+sphereName;
	demo->getSceneManager()->getSceneNode(nodeName)->setPosition(position);
}

bool Enemy::update(float elapsedTime){
	if (Enemy::inRange(demo->getCamera()->getPosition(),Enemy::ACTIVATION_RADIUS)){
		//Enemy::moveTowards(demo->getCamera()->getPosition(),Enemy::CHASE_VELOCITY,elapsedTime);
		//Enemy::chaseTime=Enemy::RELAX_TIME;
		demo->getSceneManager()->getEntity(sphereName)->setMaterialName("Active_Sphere");
	}
	else if(chaseTime>0.0){
		//Enemy::moveTowards(demo->getCamera()->getPosition(),Enemy::CHASE_VELOCITY,elapsedTime);
		Enemy::chaseTime-=elapsedTime;
		//demo->getSceneManager()->getEntity(sphereName)->setMaterialName("Relaxing_Sphere");
	}
	else{
		//demo->getSceneManager()->getEntity(sphereName)->setMaterialName("Inactive_Sphere");
	}
	if (Enemy::inRange(demo->getCamera()->getPosition(),Enemy::KILL_RADIUS)){
		//return false;
	}
	return true;
}

