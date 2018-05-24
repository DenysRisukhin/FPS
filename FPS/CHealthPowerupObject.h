#pragma once

#include <irrlicht.h>
#include "Player.h"

using namespace irr;

class CHealthPowerupObject {

public:
	CHealthPowerupObject(Player* plyr, scene::ISceneManager* smgr, const core::vector3df& pos);
	~CHealthPowerupObject();

private:
	//IAIManager* AIManager;
	//IAISensor* Sensor;
	scene::ISceneNode* Cube;
	scene::ISceneNode* Cubeb;

};
