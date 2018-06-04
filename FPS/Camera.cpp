#include "Camera.h"

Camera::Camera(ISceneManager* smgr)
{
	_smgr = smgr;

	SKeyMap keyMap[10];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;

	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_LSHIFT;

	keyMap[9].Action = EKA_CROUCH;
	keyMap[9].KeyCode = KEY_KEY_C;

	node = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.41f, -1, keyMap, 18, false, 9.0f); // 0.21
	node->setPosition(core::vector3df(2700 * 2, 255 * 2, 2600 * 2));
	node->setTarget(core::vector3df(0, 0, 0));
	node->setFarValue(20000.f);
}

ICameraSceneNode* Camera::getNode()
{
	return node;
}

Camera::Camera(ISceneManager* smgr, vector3df curPos) {
	SKeyMap keyMap[10];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;

	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_LSHIFT;

	keyMap[9].Action = EKA_CROUCH;
	keyMap[9].KeyCode = KEY_KEY_C;

	node = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.41f, -1, keyMap, 18, false, 9.0f); 
	node->setPosition(curPos);
	node->setTarget(core::vector3df(0, 0, 0));
	node->setFarValue(20000.f);
}