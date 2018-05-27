#ifndef INC_CGUNPROJECTILE_H
#define INC_CGUNPROJECTILE_H

#include <irrlicht.h>
#include "GameObject.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/** A class representing a simple projectile for demo purposes */
class CGunProjectile: public GameObject {

public:
	/**
	\brief Constructor
	\param pos - the position to start from
	\param dir - the direction to fly in
	\param smgr - the smgr to create the projectile in
	*/
	CGunProjectile(const core::vector3df& pos, const core::vector3df& dir, scene::ISceneManager* smgr);
	/**
	\brief Destructor
	*/
	~CGunProjectile();
	/**
	\brief Removes the projectile, creating an explosion effect at the same time
	*/
	void remove();
	/**
	\brief Updates the projectile's position. Returns true if it wishes to be removed
	\return a bool
	*/
	virtual void update(f32 deltaTime);

	/**
	\brief Returns the current position of the projectile
	\return a vector3df
	*/
	inline core::vector3df getPosition() { return Bill->getPosition(); }
	/**
	\brief Returns the position of the projectile at the last frame
	\return a vector3df
	*/
	//inline const core::vector3df& getPreviousPosition() { return PrevPos; }
	ISceneNode* getNode();

private:
	scene::ISceneManager* SceneManager;
	core::vector3df Direction;
	core::vector3df PrevPos;
	scene::ISceneNode* Bill;
	f32 SqDistTravelled;

	vector3df direction;
};

#endif /* INC_CGUNPROJECTILE_H */
