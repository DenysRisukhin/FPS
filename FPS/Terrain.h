#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

/**
* Represents Terrain - element from the block Stage.
*/

class Terrain
{
public:
	Terrain(ISceneManager* smgr, IVideoDriver* driver);
	ITerrainSceneNode* getNode();
	
private:
	ITerrainSceneNode* terrain;
};