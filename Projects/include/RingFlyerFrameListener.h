// RingFlyerFrameListener.h
// @author Eric D. Wills

#ifndef __RING_FLYER_FRAME_LISTENER_H__
#define __RING_FLYER_FRAME_LISTENER_H__

#include "Ogre.h"
#include "OIS/OIS.h"

class RingFlyer;
class Level;
class Ring;
class Ship;

class RingFlyerFrameListener : public Ogre::FrameListener, public OIS::MouseListener, public OIS::KeyListener {
 private:
  static const float ROTATION_INCREMENT;
  static const float TRANSLATION_INCREMENT;
  static const float FORWARD_VELOCITY;

  RingFlyer*         flyer;
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
  bool				   shiftKeyDown;
  bool				   spaceKeyPressed;
  bool				   levelKeyPressed;
  bool				   dead;
  int				   enNum;
  Ogre::Vector3        frameShipPosition;
  Ship*				   ship;
 public:
  RingFlyerFrameListener(RingFlyer* flyer, Ship* ship);

  ~RingFlyerFrameListener();

	bool frameStarted(const Ogre::FrameEvent& event);
	bool frameEnded(const Ogre::FrameEvent& event);

  bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID);
  bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID buttonID);
  bool mouseMoved(const OIS::MouseEvent& event);

  bool keyPressed(const OIS::KeyEvent& event);
  bool keyReleased(const OIS::KeyEvent& event);
};

#endif
