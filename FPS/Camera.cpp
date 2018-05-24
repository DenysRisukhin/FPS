#include "Camera.h"

Camera::Camera(ISceneManager* smgr)
{
	//node = smgr->addCameraSceneNode(0, vector3df(600, 110, 450), vector3df(0, 0, 0));
	//node->setFarValue(42000.0f);

	//ICameraSceneNode* camera = 0;

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

	node = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.21f, -1, keyMap, 9, false, 9.0f);

	//node = smgr->addCameraSceneNodeFPS(NULL, 75.0f, 0.25f, -1, keyMap, 8);

	node->setPosition(core::vector3df(2700 * 2, 255 * 2, 2600 * 2));

	node->setTarget(core::vector3df(0, 0, 0));
	//node->setTarget(core::vector3df(2397 * 2, 343 * 2, 2700 * 2));

	//camera->setFOV ( 100.f * core::DEGTORAD );giu
	node->setFarValue(20000.f);

	//smgr->setActiveCamera(node);
}

ICameraSceneNode* Camera::getNode()
{
	return node;
}