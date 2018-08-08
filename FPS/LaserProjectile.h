#ifndef INC_CLASERPROJECTILE_H
#define INC_CLASERPROJECTILE_H

#include <irrlicht.h>
#include "GameObject.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents a simple lazer projectile for demo purposes.
*/

class LaserProjectile: public GameObject {

public:
	/*!
	**Constructor
	@param pos The position to start from.
	@param dir The direction to fly in.
	@param smgr The smgr to create the projectile in.
	*/
	LaserProjectile(const core::vector3df& pos, const core::vector3df& dir, scene::ISceneManager* smgr);

	/**
	* Destructor
	*/
	~LaserProjectile();

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

#endif /* INC_CLASERPROJECTILE_H */
