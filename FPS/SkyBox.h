#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


class Skybox {
public:
	Skybox(ISceneManager* smgr, IVideoDriver* driver);
	ISceneNode* getNode();

private:
	ISceneNode* node;
	ILightSceneNode* light;
};

