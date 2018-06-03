#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

class Camera {
public:
	Camera(ISceneManager* smgr);
	ICameraSceneNode* getNode();
	void remove() {
		node->removeAnimators();
		node->remove();
		node = NULL;
	 }
	Camera(ISceneManager* smgr, vector3df curPos);
private:
	ICameraSceneNode* node;
	ISceneManager* _smgr;
	vector3df curPos;
};