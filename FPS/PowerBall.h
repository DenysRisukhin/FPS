#pragma once

#include <irrlicht.h>
#include "GameObject.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class PowerBall : public GameObject
{
public:
	PowerBall(ISceneManager* smgr, IVideoDriver* driver, vector3df start, vector3df end, f32 speed);
	virtual void update(f32 deltaTime);
	ISceneNode* getNode();

	ISceneNode* node;
protected:
	vector3df direction;
};