#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents base behaviors for game objects in Action Phase (enemies, projectiles):
* checks object Activity(true/false),
* is object need to update,
* set/get speed,
* get pos.
*/

class GameObject {
public:

	/*!
	Initializes game object data.
	@param bIsActive Game object current active state (true/false).
	@param bNeedsUpdate Game object current update state (true/false).
	@param origPosition Current game object pos.
	@param speed Game object speed.
	@param smgr Irrlicht manager.
	*/
	GameObject(vector3df pos, f32 speed, ISceneManager* manager);

	/*!
	Initializes 
	@param bIsActive Game object current active state (true/false).
	@param bNeedsUpdate Game object current update state (true/false).
	*/
	GameObject();

	/**
	* Set speed for game object
	*/
	virtual void setSpeed(f32 newSpeed);

	/**
	* Get speed for game object
	*/
	virtual f32 getSpeed();

	// ?????? return NULL
	virtual ISceneNode* getNode();

	// ????? return vector3df(0, 0, 0);
	virtual vector3df getPosition();

	// ?????
	virtual void pushBack();

	/**
	* Get current pos for game object
	*/
	virtual vector3df getPreviousPosition();

	/**
	* ??????? free func
	*/
	virtual void update(f32 deltaTime);

	/**
	* Cheked if gameobject need updates
	* Return @param bNeedsUpdate.
	*/
	bool needsUpdate();

	/**
	* Call's if object is dead.
	* Set @param bIsActive = false.
	*/
	virtual void kill();

	/**
	* Chaked object activity (lived/dead)
	* Return @param bIsActive.
	*/
	virtual bool isActive();
	
protected:
	bool bIsActive;
	bool bNeedsUpdate;
	vector3df origPosition;
	f32 speed;
	ISceneManager* smgr;
};