#pragma once

#include <irrlicht.h>
#include "Camera.h"
#include "PowerBall.h"
#include "GunProjectile.h"
#include "LaserProjectile.h"
#include "WeaponManager.h"

#include "Irrklang.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class PowerBall;

enum WEAPON {
	REVOLVER,
	REVEVO,
	MGUN,
	MGUNB,
	SMG,
	LASER
};

/*!
* Represents the Player as fps camera with weapons on the hands
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
	* Get weaponNode.
	*/
	IAnimatedMeshSceneNode* getNode();

	/**
	* Get weaponNode absolute position.
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
	void kill();
	bool isDead();

	/**
	* shots 
	*/
	void fire(s32 weapon, IrrlichtDevice *device);

	/**
	* 
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