#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class GameObject {
public:
	GameObject();
	GameObject(vector3df pos, f32 speed, ISceneManager* manager);

	virtual f32 getSpeed();
	virtual void setSpeed(f32 newSpeed);

	virtual void pushBack();
	virtual void update(f32 deltaTime);
	virtual void kill();
	virtual bool isActive();
	virtual ISceneNode* getNode();
	virtual vector3df getPosition();
	virtual vector3df getPreviousPosition();

	bool needsUpdate();

protected:
	bool bIsActive;
	bool bNeedsUpdate;
	vector3df origPosition;
	f32 speed;
	ISceneManager* smgr;
};