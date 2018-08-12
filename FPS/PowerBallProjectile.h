#pragma once
#ifndef INC_POWERBALLPROJECTILE_H
#define INC_POWERBALLPROJECTILE_H

#include <irrlicht.h>
#include "GameObject.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents a simple PowerBallProjectile projectile for demo purposes.
*/

class PowerBallProjectile : public GameObject {

public:
	/*!
	@param pos The position to start from.
	@param dir The direction to fly in.
	@param smgr The smgr to create the projectile in.
	*/
	PowerBallProjectile(const core::vector3df& pos, const core::vector3df& dir, scene::ISceneManager* smgr);

	/**
	* Destructor.
	*/
	~PowerBallProjectile();

	/**
	* Removes the projectile, creating an explosion effect at the same time.
	*/
	void remove();

	/**
	* Updates the projectile's position. Returns true if it wishes to be removed.
	*/
	virtual void update(f32 deltaTime);

	/**
	* Returns the current position of the projectile.
	* return a vector3df.
	*/
	vector3df getPosition();

	/**
	* Returns the projectile.
	* return a ISceneNode.
	*/
	ISceneNode* getNode();

private:
	ISceneManager* sceneManager;
	ISceneNode* bill;

	vector3df direction;
	vector3df prevPos;

	f32 sqDistTravelled;
};

#endif /* INC_POWERBALLPROJECTILE_H */
