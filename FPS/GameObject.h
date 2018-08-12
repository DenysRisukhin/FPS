#pragma once

#include <irrlicht.h>
#include "Global.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents base behaviors for game objects in the Action Phase (enemies, projectiles):
* checks activity of the object,
* whether the object need to update,
* sets/gets speed and gets prevPosition.
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
	* Sets the speed for game object.
	*/
	virtual void setSpeed(f32 newSpeed);

	/**
	* Gets the speed for game object.
	*/
	virtual f32 getSpeed();
	
	/**
	* Returns NULL.
	*/
	virtual ISceneNode* getNode();

	/**
	* Returns IDLE_VECTOR.
	*/
	virtual vector3df getPosition();

	virtual void pushBack();

	/**
	* Get current pos for game object.
	*/
	virtual vector3df getPreviousPosition();


	virtual void update(f32 deltaTime);

	/**
	* Cheks if gameobject need updates.
	* Return @param bNeedsUpdate.
	*/
	bool needsUpdate();

	/**
	* Call's if object is dead.
	* Set @param bIsActive = false.
	*/
	virtual void kill();

	/**
	* Checks activity of the object. 
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