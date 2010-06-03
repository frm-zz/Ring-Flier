
#ifndef __RING_FLIER_FRAME_LISTENER_H__
#define __RING_FLIER_FRAME_LISTENER_H__

#include "Ogre.h"
#include "OIS/OIS.h"

class RingFlier;
class Level;
class Ring;
class Ship;

class RingFlierFrameListener : public Ogre::FrameListener, public OIS::MouseListener, public OIS::KeyListener {
private:
	static const float ROTATION_INCREMENT;
	static const float TRANSLATION_INCREMENT;
	static float FORWARD_VELOCITY;

	RingFlier*           flier;
	Ogre::RenderWindow*  renderWindow;
	Ogre::Camera*        camera;
	OIS::InputManager*   inputManager;
	OIS::Mouse*          mouse;
	OIS::Keyboard*       keyboard;
	Ogre::Vector3        cameraTranslate;
	float                cameraPitch;
	float                cameraYaw;
	float                cameraPitchIncrement;
	float                cameraYawIncrement;
	bool                 forwardKeyDown;
	bool                 backKeyDown;
	bool                 leftKeyDown;
	bool                 rightKeyDown;
	bool                 shutdownKeyPressed;
	bool				 shiftKeyDown;
	bool				 incSpeedKeyDown;
	bool				 decSpeedKeyDown;
	bool				 maxSpeedKeyDown;
	bool				 spaceKeyPressed;
	bool				 levelKeyPressed;
	bool				 dead;
	int				     enNum;
	Ogre::Vector3        frameShipPosition;
	Ship*				 ship;
public:
	RingFlierFrameListener(RingFlier* flier, Ship* ship);

	~RingFlierFrameListener();
	void RingFlierFrameListener::setShip(Ship* ship);
	bool frameStarted(const Ogre::FrameEvent& event);
	bool frameEnded(const Ogre::FrameEvent& event);

	bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID);
	bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID);
	bool mouseMoved(const OIS::MouseEvent& event);

	bool keyPressed(const OIS::KeyEvent& event);
	bool keyReleased(const OIS::KeyEvent& event);
	void showTimeOverlay(bool show)
	{
		Ogre::Overlay* o
			=Ogre::OverlayManager::getSingleton().getByName("Core/TimeOverlay");
		if (!o)
			OGRE_EXCEPT( Ogre::Exception::ERR_ITEM_NOT_FOUND, "Could not find overlay Core/DebugOverlay", "showDebugOverlay" );
		if (show)
			o->show();
		else
			o->hide();
	}
	void showScoreOverlay(bool show)
	{
		Ogre::Overlay* o
			=Ogre::OverlayManager::getSingleton().getByName("Core/ScoreOverlay");
		if (!o)
			OGRE_EXCEPT( Ogre::Exception::ERR_ITEM_NOT_FOUND, "Could not find overlay Core/DebugOverlay", "showDebugOverlay" );
		if (show)
			o->show();
		else
			o->hide();
	}

	void updateTime(float time)
	{
		// update stats when necessary
		Ogre::OverlayElement* timePanel =
			Ogre::OverlayManager::getSingleton().getOverlayElement("Core/Time");
		timePanel->setCaption( Ogre::StringConverter::toString(time));
	}

	void updateScore(int score)
	{
		// update stats when necessary
		Ogre::OverlayElement* scorePanel =
			Ogre::OverlayManager::getSingleton().getOverlayElement("Core/ScoreCount");
		scorePanel->setCaption( Ogre::StringConverter::toString(score));
	}
};

#endif
