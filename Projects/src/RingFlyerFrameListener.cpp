// RingFlyerFrameListener.cpp


#include "RingFlyerFrameListener.h"
#include "RingFlyer.h"
#include "../Ring.h"
#include "../Ship.h"

const float RingFlyerFrameListener::ROTATION_INCREMENT    = 1.5f;
const float RingFlyerFrameListener::TRANSLATION_INCREMENT = 30.0f;
float RingFlyerFrameListener::FORWARD_VELOCITY = 120.0f;
const float gravity = -9.8f;
float jumpVelocity = 0.0f;
float roll=0.0f;
Ogre::Vector3 frameShipPosition;
int l =0;
float timeLeft=100.0f;
int score=0;
//int enNum=50;

RingFlyerFrameListener::RingFlyerFrameListener(RingFlyer* flyer,Ship* ship) :
flyer(flyer), renderWindow(flyer->getRenderWindow()), camera(flyer->getCamera()), cameraTranslate(Ogre::Vector3::ZERO), cameraPitchIncrement(0.0f), cameraYawIncrement(0.0f), forwardKeyDown(false),
backKeyDown(false), leftKeyDown(false), rightKeyDown(false), shutdownKeyPressed(false), shiftKeyDown(false), spaceKeyPressed(false),
levelKeyPressed(false),incSpeedKeyDown(false),decSpeedKeyDown(false),maxSpeedKeyDown(false),dead(false),enNum(50),frameShipPosition(Ogre::Vector3::ZERO),ship(ship){
	size_t windowHandle;
	renderWindow->getCustomAttribute("WINDOW", &windowHandle);

	inputManager = OIS::InputManager::createInputSystem(windowHandle);

	mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
	mouse->setEventCallback(this);
	mouse->capture();

	keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	keyboard->setEventCallback(this);
	keyboard->capture();
	showTimeOverlay(true);
	showScoreOverlay(true);
	updateScore(score);
}

RingFlyerFrameListener::~RingFlyerFrameListener() {
	inputManager->destroyInputObject(mouse);
	inputManager->destroyInputObject(keyboard);
	OIS::InputManager::destroyInputSystem(inputManager);
}
void RingFlyerFrameListener::setShip(Ship* ship){
	this->ship = ship;
}

bool RingFlyerFrameListener::frameStarted(const Ogre::FrameEvent& event) {
	if (shutdownKeyPressed || renderWindow->isClosed())
		return false;

	mouse->capture();
	keyboard->capture();
	float t2;


	float dt = event.timeSinceLastFrame;
	if (dead){
		//t2=0.0f;
		//flyer->getSceneManager()->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.93f, 0.0f, 0.0f),0.001f,5.0f,100.0f);
		

		//updateTime(t2);
	}

	if (!dead){
		timeLeft-=dt;
		t2=timeLeft*100.0f;
		int t=t2;
		t2=t/100.0f;
		updateTime(t2);
	}
	if(timeLeft<=0.0f){

		dead=true;

	}
	

	//flyer->ship->setPostion(flyer->ship->getPostion().x+20.0f*dt,flyer->ship->getPostion().y,flyer->ship->getPostion().z);
	/*
	if (cameraPitchIncrement != 0.0f) {
	cameraPitch -= ROTATION_INCREMENT*dt*cameraPitchIncrement;
	//std::cout << cameraPitch << " \n";

	if (cameraPitch < -Ogre::Math::PI/2)
	cameraPitch= -Ogre::Math::PI/2;

	else if (cameraPitch > Ogre::Math::PI/2)
	cameraPitch= Ogre::Math::PI/2;


	cameraPitchIncrement = 0.0f;

	}
	if (cameraYawIncrement != 0.0f) {
	cameraYaw -= ROTATION_INCREMENT*dt*cameraYawIncrement;

	cameraYawIncrement = 0.0f;
	}
	*/
	// camera->pitch(Ogre::Radian(cameraPitch*dt/100.0f));
	// camera->yaw(Ogre::Radian(cameraYaw*dt/100.0f));
	//camera->setOrientation(Ogre::Quaternion(Ogre::Radian(cameraYaw), Ogre::Vector3::UNIT_Y)*
	//                  Ogre::Quaternion(Ogre::Radian(cameraPitch), Ogre::Vector3::UNIT_X));

	if (!dead){
		if (forwardKeyDown){
			//cameraTranslate.z = -TRANSLATION_INCREMENT*dt;
			cameraPitch+=ROTATION_INCREMENT*dt;
			//camera->pitch(Ogre::Radian(cameraPitch));
			//ship->setOrientation(cameraPitch,roll);
		}
		//else{
		//	cameraPitch=0.0f;
		//}

		else if (backKeyDown){
			// cameraTranslate.z = TRANSLATION_INCREMENT*dt;
			cameraPitch-=ROTATION_INCREMENT*dt;
			//camera->pitch(Ogre::Radian(cameraPitch));
			//ship->setOrientation(cameraPitch,roll);
		}
		//else{
		//cameraPitch=0.0f;
		//}
		if (leftKeyDown){
			//  cameraTranslate.x = -TRANSLATION_INCREMENT*dt;
			roll-=ROTATION_INCREMENT*dt;
			//camera->roll(Ogre::Radian(roll));
			//ship->setOrientation(cameraPitch,roll);
		}
		//else{
		//roll=0.0f;
		//}
		if (rightKeyDown){
			roll+=ROTATION_INCREMENT*dt;
			//camera->roll(Ogre::Radian(roll));
			//ship->setOrientation(cameraPitch,roll);
		}
		ship->setOrientation(cameraPitch,roll);
		//else{
		//roll=0.0f;
		//}
		if (!dead){
			cameraPitch=0.0f;
			roll=0.0f;
			frameShipPosition=ship->getPosition();
			ship->setPosition(Ogre::Vector3(0.0f,0.0f,FORWARD_VELOCITY*dt));
		}
		// cameraTranslate.x = TRANSLATION_INCREMENT*dt;
		//	if (shiftKeyDown){
		//		cameraTranslate*=2;
		//	}





		//	cameraTranslate.z=-FORWARD_VELOCITY*dt;
		//cameraTranslate.z=-10*dt;
		frameShipPosition=ship->getPosition();
		//std::cout<<frameShipPosition << std::endl;

		//std::cout<<ship->getPosition()<<std::endl;
		//ship->setPosition(Ogre::Vector3(frameShipPosition.x,frameShipPosition.y,frameShipPosition.z-FORWARD_VELOCITY*dt));

		//flyer->getSceneManager()->getSceneNode("cameraNode")->translate(camera->getPosition()-flyer->getSceneManager()->getSceneNode("cameraNode")->getPosition()*0.1f);
		//camera->moveRelative(cameraTranslate);
	}
	//copy of the camera vector
	Ogre::Vector3 camera2 = camera->getPosition();
	float height = flyer -> getTerrainHeightAt(camera2.x,camera2.z);

	/*
	if (spaceKeyPressed && jumpVelocity ==0.0f){
	jumpVelocity = 10.0f;
	}


	if (jumpVelocity != 0.0f){
	jumpVelocity += gravity*dt*1.5;
	camera2.y+=jumpVelocity/100;
	}
	if (camera2.y<=(height+15.0f)){
	jumpVelocity = 0.0f;
	}
	*/
	// std::cout << camera2.x << " " << camera2.y << " " << camera2.z << "\n";
	frameShipPosition=ship->getPosition();
	if ((frameShipPosition.x<0||frameShipPosition.x>5000||frameShipPosition.z<0||frameShipPosition.z>5000)&&!dead){
		dead=true;
		flyer->explosion();
	}



	if((frameShipPosition.y< flyer->getTerrainHeightAt(frameShipPosition.x,frameShipPosition.z)+2.0)&&!dead){
		dead=true;
		flyer->deadEffect();
		
	}
	if (flyer->getTerrainHeightAt(camera->getPosition().x,camera->getPosition().z)+15.0f >= camera->getPosition().y){
		//flyer->adjustCameraHeightToTerrain();
	}

	if (levelKeyPressed){
		l=(l+1)%3;
		int oldNum=enNum;
		if (l==0)
			enNum=50;
		if (l==1)
			enNum=100;
		if (l==2)
			enNum=200;
		flyer->createNextLevel(l);
		timeLeft=100.0f;
		dead=false;
		score=0;
	}
	//std::cout << "outside level press"<< std::endl;
	int i;
	for(i=0;i<enNum;i++){									//THIS GUY WAS BREAKING EVERYTHING
		/*if (!flyer->e[i]->update(dt)){
		std::cout << "DEATH"<< std::endl;
		dead=true;
		}*/
		score+=flyer->e[i]->update(dt);
		
		updateScore(score);

	}
	if(incSpeedKeyDown && (FORWARD_VELOCITY < 400.0f)){
		FORWARD_VELOCITY +=100*dt;
	}
	else if(decSpeedKeyDown && (FORWARD_VELOCITY > 20.0f)  && (100*dt <
		20.0f) ){
			FORWARD_VELOCITY -=100*dt;
	}

	if(maxSpeedKeyDown){
		FORWARD_VELOCITY = 400.0f;
		maxSpeedKeyDown = false;
	}
	//std::cout << "return true"<< std::endl;
	return true;
}
//docs/manual/entities
//need a scenenode and entity for each sphere

bool RingFlyerFrameListener::frameEnded(const Ogre::FrameEvent& event) { return true; }

bool RingFlyerFrameListener::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID) { return true; }
bool RingFlyerFrameListener::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID) { return true; }

bool RingFlyerFrameListener::mouseMoved(const OIS::MouseEvent& event) {
	cameraPitchIncrement = event.state.Y.rel;
	cameraYawIncrement   = event.state.X.rel;

	return true;
}

bool RingFlyerFrameListener::keyPressed(const OIS::KeyEvent& event) {
	switch (event.key) {
  case OIS::KC_W:
	  forwardKeyDown = true;
	  break;
  case OIS::KC_S:
	  backKeyDown = true;
	  break;
  case OIS::KC_A:
	  leftKeyDown = true;
	  break;
  case OIS::KC_D:
	  rightKeyDown = true;
	  break;
  case OIS::KC_ESCAPE:
	  shutdownKeyPressed = true;
	  break;

  case OIS::KC_SPACE:
	  spaceKeyPressed = true;
	  break;
  case OIS::KC_F1:
	  levelKeyPressed =true;
	  break;

  case OIS::KC_LSHIFT:
	  incSpeedKeyDown=true;
	  break;
  case OIS::KC_LCONTROL:
	  decSpeedKeyDown=true;
	  break;

  case OIS::KC_CAPITAL:
	  maxSpeedKeyDown=true;
	  break;

	}

	return true;
}

bool RingFlyerFrameListener::keyReleased(const OIS::KeyEvent& event) {
	switch (event.key) {
  case OIS::KC_W:
	  forwardKeyDown = false;
	  break;
  case OIS::KC_S:
	  backKeyDown = false;
	  break;
  case OIS::KC_A:
	  leftKeyDown = false;
	  break;
  case OIS::KC_D:
	  rightKeyDown = false;
	  break;

  case OIS::KC_SPACE:
	  spaceKeyPressed = false;
	  break;
  case OIS::KC_F1:
	  levelKeyPressed =false;
	  break;
  case OIS::KC_LSHIFT:
	  incSpeedKeyDown=false;
	  break;
  case OIS::KC_LCONTROL:
	  decSpeedKeyDown=false;
	  break;

  case OIS::KC_CAPITAL:
	  maxSpeedKeyDown=false;
	  break;
	}

	return true;
}
