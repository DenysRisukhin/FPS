#pragma once

#include <irrlicht.h>
#include "Camera.h"
#include "GunProjectile.h"
#include "LaserProjectile.h"
#include "WeaponManager.h"

#include "Irrklang.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents types of weapons.
*/
enum WEAPON {
	REVOLVER,
	REVEVO,
	MGUN,
	MGUNB,
	SMG,
	LASER
};

/*!
* Represents the Player as fps camera with weapons on the hands.
*/

class Player: public WeaponManager {
public:

	/*!
	Initializes Player data.
	@param camera FPS camera.
	@param updateListPtr list with handling objects.
	*/
	Player(IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver, Camera* camera, list<GameObject*> *updateListPtr);
	~Player();

	/**
	* Initializes weaponNode & handNode.
	*/
	void initWeaponAndHandNode();

	void setWeapon(WEAPON);
	void setHealth(u8 health);
	
	WEAPON getWeapon();

	/**
	* Gets weaponNode.
	*/
	IAnimatedMeshSceneNode* getNode();

	/**
	* Gets weaponNode absolute position.
	*/
	vector3df getPosition();
	vector3df getDirection();
	u8 getHealth();
	ISoundEngine* getSound();
	ISceneManager* getSmgr();
	
	/**
	*  Reduce Player health.
	*/
	void setDamage(u8 attackRating);

	/**
	*  Sets the health of the player to NULL.
	*/
	void kill();

	/**
	*  Checks the health of the player.
	*/
	bool isDead();

	/**
	* Makes shot by current weapon with correspond projectile.
	*/
	void fire(s32 weapon, IrrlichtDevice *device);

	/**
	* Changes weapon.
	*/
	void changeWeapon(s32 weapon);

	virtual void drop();

private:

	list<GameObject*> *listPtr;

	WEAPON weapon;

	IAnimatedMeshSceneNode* weaponNode;
	IAnimatedMeshSceneNode* handNode;

	IAnimatedMesh* weaponMesh;
	IAnimatedMesh* handMesh;

	ISoundEngine *sound;
	IrrlichtDevice* device;
	ISceneManager* smgr;
	IVideoDriver* driver;
	Camera* camera;

	ISceneNode* gunflame;

	vector3df forwardDirection;

	vector3df scale, pos, rot;
	vector3df scaleh, posh, roth;
	
	f32 lastAttack;
	u8 health;
};