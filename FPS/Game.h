#pragma once

#include <irrlicht.h>
#include <iostream>
#include <time.h>
#include "Terrain.h"
#include "Player.h"
#include "Camera.h"
#include "EventReciever.h"
#include "Skybox.h"
#include "PowerBall.h"
#include "PowerBallEnemy.h"
#include "BadFaerie.h"
#include "GameObject.h"

//#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#endif

#define DEBUG

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class Game {
public:
	Game();

	void processInput(IrrlichtDevice*, ISceneManager*, IVideoDriver*, ITriangleSelector*, EventReciever*, Player*, Camera*, f32);

	void handleCollisions(Player*, Camera*, f32);
	void handleCollisionWithPlayer(Player*, Camera*, f32);
	void handleCollisionEnemyPowerBall(void);
	void handleCollisionBetweenEnemies(GameObject*);
	bool collisionsBetweenEnemyAndBalls(ISceneNode*);
	
	void updateGameObjects(f32);
	void handleGameState(GameState &, Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
		
	u8 getNumOfEnemies();

	bool gamePaused;

	void initiateWave1(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);

	void updateWaveStatus(GameState &, IrrlichtDevice*, Player*, ISceneManager*, IVideoDriver*);

	void spawnBadFaerie(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver);

	list<GameObject*> updateList;

	list<GameObject*>& getUpdateList() {
		return updateList;
	}

	void clearUpdateList();

	void setNumOfEnemies(u8 num) {
		numOfEnemies = num;
	}

	void setBWave1Started();

private:
	
	ISoundEngine	*sound;
	f32 lastUpdate;
	f32 timeSinceStart;
	ITriangleSelector* selector;
	u32 delayTimer;


	bool bMainMenuDisplayed;
	bool bGameOverDisplayed;
	bool bGameCompleteDisplayed;

	BadFaerie* badFaerie;

	u8 numOfEnemies;
	bool bWave1Finished;

	bool bWave1Started;
	
};
