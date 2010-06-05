#include "RingFlierFrameListener.h"
#include "RingFlier.h"
#include "Ring.h"
#include "Ship.h"

const float RingFlierFrameListener::ROTATION_INCREMENT    = 1.5f;
const float RingFlierFrameListener::TRANSLATION_INCREMENT = 30.0f;
float RingFlierFrameListener::FORWARD_VELOCITY = 120.0f;
const float gravity = -9.8f;
float jumpVelocity = 0.0f;
float roll=0.0f;
Ogre::Vector3 frameShipPosition;
int level =0;
float timeLeft=100.0f;
int score=0;


RingFlierFrameListener::RingFlierFrameListener(RingFlier* flier,Ship* ship) :
flier(flier), renderWindow(flier->getRenderWindow()), camera(flier->getCamera()), cameraTranslate(Ogre::Vector3::ZERO), cameraPitchIncrement(0.0f), cameraYawIncrement(0.0f), forwardKeyDown(false),
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

RingFlierFrameListener::~RingFlierFrameListener() {
	inputManager->destroyInputObject(mouse);
	inputManager->destroyInputObject(keyboard);
	OIS::InputManager::destroyInputSystem(inputManager);
}
void RingFlierFrameListener::setShip(Ship* ship){
	this->ship = ship;
}

bool RingFlierFrameListener::frameStarted(const Ogre::FrameEvent& event) {
	if (shutdownKeyPressed || renderWindow->isClosed())
		return false;

	mouse->capture();
	keyboard->capture();
	float displayedTime;
	float dt = event.timeSinceLastFrame;

	if(timeLeft<=0.0f){
		dead=true;
	}
	else if(timeLeft <= 10.0f){
		flier->clockSound();
	}

	if(!dead){
		timeLeft-=dt;
		int t=timeLeft*100.0f;
		displayedTime=t/100.0f;
		updateTime(displayedTime);
		if (forwardKeyDown){
			cameraPitch+=ROTATION_INCREMENT*dt;
		}
		else if (backKeyDown){
			cameraPitch-=ROTATION_INCREMENT*dt;
		}
		if (leftKeyDown){
			roll-=ROTATION_INCREMENT*dt;
		}
		if (rightKeyDown){
			roll+=ROTATION_INCREMENT*dt;
		}
		ship->setOrientation(cameraPitch,roll);
			cameraPitch=0.0f;
			roll=0.0f;
			ship->setPosition(Ogre::Vector3(0.0f,0.0f,FORWARD_VELOCITY*dt));
			frameShipPosition=ship->getPosition();
	if ((frameShipPosition.x<0||frameShipPosition.x>5000||frameShipPosition.z<0||frameShipPosition.z>5000) &&(level%3)!=0){
		dead=true;
		flier->explosion();

	}
	if((frameShipPosition.y< flier->getTerrainHeightAt(frameShipPosition.x,frameShipPosition.z)+2.0) && (level%3)!=0){
		flier->getSceneManager()->getSceneNode("shipNode")->setPosition(Ogre::Vector3(frameShipPosition.x,flier->getTerrainHeightAt(frameShipPosition.x,frameShipPosition.z)+2.0,frameShipPosition.z));
		dead=true;
		flier->deadEffect();
	}
	}////End if(!dead) for movement


	if (levelKeyPressed){
		level=(level+1)%3;
		if (level==0)
			enNum=50;
		if (level==1)
			enNum=100;
		if (level==2)
			enNum=200;
		flier->createNextLevel(level);
		timeLeft=100.0f;
		dead=false;
		score=0;
		FORWARD_VELOCITY=120.0f;
	}

	int i;
	for(i=0;i<enNum;i++){
		score+=flier->e[i]->update(dt);
		updateScore(score);
	}

	if(incSpeedKeyDown && (FORWARD_VELOCITY < 400.0f)){
		FORWARD_VELOCITY +=10;
	}

	else if(decSpeedKeyDown && (FORWARD_VELOCITY > 20.0f) ){
			FORWARD_VELOCITY -=10;
	}
	if (!decSpeedKeyDown && !incSpeedKeyDown && FORWARD_VELOCITY!=120){
		if(FORWARD_VELOCITY>120){
			FORWARD_VELOCITY-=10;
		}
		else if(FORWARD_VELOCITY<120){
		FORWARD_VELOCITY+=10;
		}
	}

	return true;
}

bool RingFlierFrameListener::frameEnded(const Ogre::FrameEvent& event) { return true; }
bool RingFlierFrameListener::mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID) { return true; }
bool RingFlierFrameListener::mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID) { return true; }
bool RingFlierFrameListener::mouseMoved(const OIS::MouseEvent& event) {
	cameraPitchIncrement = event.state.Y.rel;
	cameraYawIncrement   = event.state.X.rel;
	return true;
}


bool RingFlierFrameListener::keyPressed(const OIS::KeyEvent& event) {
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
	  decSpeedKeyDown = true;
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
	}
	return true;
}

bool RingFlierFrameListener::keyReleased(const OIS::KeyEvent& event) {
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
	  decSpeedKeyDown = false;
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
	}
	return true;
}
