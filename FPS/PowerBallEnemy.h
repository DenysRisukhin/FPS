#pragma once

#include "PowerBall.h"

//class PowerBallEnemy : public PowerBall
//{
//public:
//	PowerBallEnemy(ISceneManager* smgr, IVideoDriver* driver, vector3df start, vector3df end, f32 speed);
//};

class PowerBallEnemy : public GameObject
{
public:
	PowerBallEnemy(ISceneManager* smgr, IVideoDriver* driver, vector3df start, vector3df end, f32 speed);
	virtual void update(f32 deltaTime);
	ISceneNode* getNode();

protected:
	IBillboardSceneNode* node;
	vector3df direction;
};