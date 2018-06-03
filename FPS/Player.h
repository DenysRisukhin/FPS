#pragma once

#include <irrlicht.h>
#include "Camera.h"
#include "PowerBall.h"

#include "CGunProjectile.h"
#include "CLaserProjectile.h"
//#include "Gui.h"

#include "CCharacter.h"

#include "Irrklang.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class PowerBall;
//class PowerBallEnemy;


#define POWERBALL_COST				20
#define PUSH_COST					30
#define TELEPORT_COST				30
#define MANA_REGENERATE_PER_SEC		5
#define PICKUP_HEAL					30

enum State
{
	IDLE,
	ATTACK,
	RUNNING
};

enum WEAPON {
	REVOLVER,
	REVEVO,
	MGUN,
	MGUNB,
	SMG,
	LASER
};


class Player: public CCharacter {
public:

	WEAPON weapon;
	WEAPON getWeapon();
	void setWeapon(WEAPON);
	Player(IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver, Camera* camera, list<GameObject*> *updateListPtr);
	~Player() { sound->drop(); }

	void setUpdateList(list<GameObject*> *updateListPtr);

	IAnimatedMesh* getMesh();
	IAnimatedMeshSceneNode* getNode();
	vector3df getPosition();
	vector3df getDirection();
	
	
	//PowerBall* Attack();
	bool push();
	void teleport();

	// ущерб
	void takeDamage(u8 attackRating);
	void kill();
	bool isDead();

	// подбирать здоровье
	void takePickup();
	u8 getHealth();
	u8 getMana();
	void incrementMana();

	// 
	//bool update(s32 elapsedTime, s32 weapon, IrrlichtDevice *device);
	//bool update(s32 elapsedTime, s32 weapon, IrrlichtDevice *device);
	void fire(s32 weapon, IrrlichtDevice *device);
	void changeWeapon(s32 weapon);

	//inline scene::IAnimatedMeshSceneNode* getNode() { return GunNode; }
	scene::IAnimatedMeshSceneNode* GunNode;
	scene::IAnimatedMeshSceneNode* HandNode;

	scene::IAnimatedMesh* mesh;
	scene::IAnimatedMesh* handmesh;

	ISceneManager* getSmgr() {
		return smgr;
	}

	f32 lastAttack;

	virtual void drop();

	void setCamera(Camera* myCamera);

private:
	ISoundEngine	*sound;
	list<GameObject*> * listPtr;
	//f32 lastAttack;
	f32 lastPush;
	f32 lastTeleport;
	f32 cameraDistance;
	State state;
	f32 speed;
	IrrlichtDevice* device;
	ISceneManager* smgr;
	IVideoDriver* driver;
	//IAnimatedMesh* mesh;
	IAnimatedMeshSceneNode* node;
	vector3df forwardDirection;
	u8 health;
	u8 mana;
	Camera* camera;

	//
	s32 TimeSinceLastShot;
	
	scene::IMetaTriangleSelector* MetaSelector;
	u32 now;
	ISceneNode* gunflame;
	ITexture* image;

	core::vector3df scale, pos, rot;
	core::vector3df scaleh, posh, roth;
};