#pragma once

#include <irrlicht.h>
#include <iostream>
#include <time.h>
#include "Terrain.h"
#include "Player.h"
#include "Camera.h"
#include "EventReciever.h"
#include "Skybox.h"
#include "PowerBallProjectile.h"
#include "BadFaerie.h"
#include "GameObject.h"
#include "Global.h"

#define DEBUG

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

/*!
*   Represents handling of various collisions between objects, 
*   handling of eventReciever events & processing of the life cycle of the enemy.
*/
class GameHandle {
public:
	GameHandle();

	/**
	* Handling user input.
	*/
	void processInput(IrrlichtDevice*, ISceneManager*, IVideoDriver*, ITriangleSelector*, EventReciever*, Player*, Camera*, f32);

	/**
	* Handling all the collisions.
	*/
	void handleCollisions(Player*, Camera*, f32);

	/**
	* Handling collision between GameObjects & player.
	*/
	void handleCollisionWithPlayer(Player*, Camera*, f32);

	/**
	* Handling collisions between Enemies and Projectiles.
	*/
	void handleCollisionEnemyPowerBall();

	void handleCollisionPlayerPowerBall();

	/**
	* Handling collision between enemies.
	*/
	void handleCollisionBetweenEnemies(GameObject*);

	/**
	* Handling collisions between Enemy and Projectiles(GunProjectile & LazeProjectile).
	*/
	bool collisionsBetweenEnemyAndProjectiles(ISceneNode*);
	
	/**
	* Update position of all GameObjects.
	*/
	void updateGameObjects(f32);

	/**
	* Handling Game State.
	*/
	void handleWinLoseState(GameState &, Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
		
	/**
	*  Create first enemies wave.
	*/
	void setBWaveStarted();

	/**
	*  Creates enemies wave.
	*/
	void initiateWave(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);

	/**
	* Spawns enemies.
	*/
	void spawnBadFaerie(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver);

	/**
	* Determines, if wave is finished or player is dead.
	*/
	void updateWaveStatus(GameState &, IrrlichtDevice*, Player*, ISceneManager*, IVideoDriver*);

	void setNumOfEnemies(u8 num);

	u8 getNumOfEnemies();

	/**
	* Contains every object which need to handle & update.
	*/
	list<GameObject*> updateList;

	list<GameObject*>& getUpdateList();

	void clearUpdateList();

private:
	
	ISoundEngine *sound;
	BadFaerie* badFaerie;
	ITriangleSelector* selector;

	f32 timeSinceStart;

	bool bMainMenuDisplayed;
	bool bGameOverDisplayed;
	bool bGameCompleteDisplayed;
	bool bWaveFinished;
	bool bWaveStarted;
	//bool collisionWithPlayer;

	u8 numOfEnemies;

	Player* _player;
};
