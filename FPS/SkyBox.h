#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

/**
* Represents Skybox - element from the block Stage.
*/

class Skybox {
public:
	Skybox(ISceneManager* smgr, IVideoDriver* driver);
	ISceneNode* getNode();

private:
	ISceneNode* node;
	ILightSceneNode* light;
};

