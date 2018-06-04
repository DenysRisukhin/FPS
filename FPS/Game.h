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
//#include "Monster.h"
//#include "Wraith.h"
#include "GameHud.h"
//#include "HealthPickup.h"

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

	//----
	//void handleCollisions(Player*, Camera*, f32);
	//void handleCollisionWithPlayer(Player*, Camera*, f32);
	//----
	
	void handleCollisions(Player*, Camera*, f32);
	void handleCollisionWithPlayer(Player*, Camera*, f32);
	void handleCollisionEnemyPowerBall(void);
	void handleCollisionBetweenEnemies(GameObject*);
	bool collisionsBetweenEnemyAndBalls(ISceneNode*);
	//void collisionBetweenFaerieAndPlayer(Player*, Camera*, ISceneNode*, f32);

	void updateGameObjects(f32);
	void handleGameState(GameState &, Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	
	void displayGameOverScreen(IVideoDriver*, IGUIEnvironment*);
	void displayGameCompleteScreen(IVideoDriver*, IGUIEnvironment*);

	void displayMainMenu(GameState &, IrrlichtDevice*);
	//f32 getLastUpdate();
	//void setLastUpdate(f32 update);
	u8 getNumOfEnemies();

	bool gamePaused;

	void initiateWave1(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);

	void updateWaveStatus(GameState &, IrrlichtDevice*, Player*, ISceneManager*, IVideoDriver*);

	void spawnBadFaerie(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver);

	list<GameObject*> updateList;

	// updateList = list<GameObject*>();
	//GUI				*gui;

	list<GameObject*>& getUpdateList() {
		return updateList;
	}

	void clearUpdateList() {

		if (updateList.size()) {
			for (list<GameObject*>::Iterator it = updateList.begin(); it != updateList.end(); ++it)
			{
				std::cout << "numOfEnemies:" << (int*)--numOfEnemies << std::endl;
				(*it)->getNode()->remove();
				delete *it;
			}
			updateList.clear();
		}
}

	void setNumOfEnemies(u8 num) {
		numOfEnemies = num;
	}

	void setBWave1Started();

private:
	
	f32 lastUpdate;
	f32 timeSinceStart;
	ITriangleSelector* selector;
	u32 delayTimer;


	bool bMainMenuDisplayed;
	bool bGameOverDisplayed;
	bool bGameCompleteDisplayed;

	//Enemy* enemies[20];

	BadFaerie* badFaerie;

	u8 numOfEnemies;
	bool bWave1Finished;

	bool bWave1Started;
	
};
