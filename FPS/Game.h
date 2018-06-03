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

		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		for (int i = 0; i < updateList.getSize(); ++i)
		{
			if (tempIterator.operator==(it))
			{
				break;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());

			if (ptr != NULL)
			{
				
					// remove enemy from the scene
									
									// Removing enemy from updateList.
									--numOfEnemies;
								//	std::cout << "numOfEnemies:" << (int*)numOfEnemies << std::endl;

									auto temp = it;

									ptr->getNode()->remove();
									ptr = NULL;
								
									updateList.erase(temp);
															
									std::cout << "updateList.getSize():" << updateList.getSize() << std::endl;
				
			}

			if (tempIterator.operator==(it.operator++()))
			{
				break;
			}
		}

		//if (updateList.getSize() != 0)
		//{
		//	

		//	list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		//	//list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		//	it = updateList.begin();

		//	// Going through all GameObjects.
		//	for (int i = 0; i < updateList.getSize(); ++i)
		//	{
		//		std::cout << i << std::endl;
		//		// Check for it.current = NULL.
		//		/*if (it.operator==(tempIterator))
		//		{
		//			std::cout << "it.current = NULL" << std::endl;
		//			return;
		//		}*/
		//		GameObject* ptr = NULL;
		//		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		//		if (updateList.getSize() == 0)
		//		{
		//			std::cout << "updateList.getSize() == 0" << std::endl;
		//			return;
		//		}

		//		// Check for Enemy.
		//		ptr = dynamic_cast<GameObject*>(it.operator*());
		//	/*	if (it.operator!=(tempIterator))
		//		{
		//			ptr = it.operator*();
		//		}*/

		//		if (ptr != NULL)
		//		{
		//			
		//				// remove enemy from the scene
		//				ptr->getNode()->remove();
		//				// Removing enemy from updateList.
		//				--numOfEnemies;
		//				std::cout << "numOfEnemies:" << (int*)numOfEnemies << std::endl;

		//				auto temp = it;
		//				it.operator++();
		//				
		//				//++it;
		//				//tempIterator++;
		//				updateList.erase(temp);
		//			//	continue;
		//		
		//				std::cout << "updateList.getSize():" << updateList.getSize() << std::endl;
		//			//handleCollisionBetweenEnemies(ptr);
		//		}

		//		// Check for it.current->next = NULL.
		//		/*if (tempIterator.operator==(it.operator++()))
		//		{
		//			
		//			std::cout << "current->next = NULL" << std::endl;
		//			return;
		//		}*/

		//		
		//	}
		//}
		
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
