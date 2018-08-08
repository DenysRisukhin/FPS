#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;

/**
* Represents fps camera.
*/

class Camera {
public:
	Camera(ISceneManager* smgr);
	ICameraSceneNode* getNode();
	void remove();

private:
	ICameraSceneNode* node;
};