#include "Game.h"

Game::Game()
{
	updateList = list<GameObject*>();
	lastUpdate = 0.0f;
	timeSinceStart = 0.0f;
	selector = NULL;
	delayTimer = 0;
	//pickup_0 = NULL;
	//pickup_1 = NULL;
	gamePaused = false;
	bMainMenuDisplayed = false;
	bGameOverDisplayed = false;
	bGameCompleteDisplayed = false;
	//numOfEnemies = 0;

	/*bWave1Finished = false;
	bWave2Finished = false;
	bWave3Finished = false;
	bWave4Finished = false;
	bWave5Finished = false;

	bWave1Started = false;
	bWave2Started = false;
	bWave3Started = false;
	bWave4Started = false;
	bWave5Started = false;*/
}

// Function to handle user input.
void Game::processInput(IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, ITriangleSelector* selector, EventReciever* reciever, Player* player, Camera* camera, f32 deltaTime)
{
	bool pPressed = false;

	if (reciever->getMouse() == EMIE_LMOUSE_PRESSED_DOWN) {
		//add vector maybe ????
		//PowerBall* tempBall = player->Attack();
		//if (tempBall != NULL)

		//{
		////	updateList.push_back(tempBall);
		//}
	}

	//switch (reciever->getMouse())
	//{
	//case EMIE_LMOUSE_PRESSED_DOWN:
	//	//pManager->getScriptManager()->runScript("level_mouse");
	//	//PowerBall* tempBall = player->Attack();
	//	if (tempBall != NULL)
	//	{
	//		updateList.push_back(tempBall);
	//	}
	//	break;

	//case EMIE_LMOUSE_LEFT_UP:	//left mouse released
	//	break;

	//case EMIE_RMOUSE_PRESSED_DOWN:
	//	// right mouse pressed code here
	//	//pManager->getPlayer()->setJumpingFlag(true); 
	//	break;
	//case EMIE_MOUSE_WHEEL:
	//	//pManager->getScriptManager()->runScript("level_mouse");
	//	break;
	//}

	if (reciever->isKeyDown(KEY_KEY_W))
	{
		//player->moveForward(deltaTime);
		//player->setRunningAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_S))
	{
		//player->moveBackward(deltaTime);
		//player->setRunningAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_A))
	{
		//player->turnLeft(deltaTime);
	}
	if (reciever->isKeyDown(KEY_KEY_D))
	{
		//player->turnRight(deltaTime);
	}
	if (reciever->isKeyDown(KEY_KEY_Q))
	{
		//player->strafeRight(deltaTime);
	}
	if (reciever->isKeyDown(KEY_KEY_E))
	{
		//player->strafeLeft(deltaTime);
	}
	if ( reciever->isKeyDown(KEY_RETURN))
	{
		PowerBall* tempBall = player->Attack();
		if (tempBall != NULL)
		{
			updateList.push_back(tempBall);
		}
		//player->setAttackAnimation();

		//player->fire(REVOLVER, device);
	}
	if (reciever->isKeyDown(KEY_KEY_X))
	{
		//pushEnemies(player);
		//player->setAttackAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_C))
	{
		//player->teleport();
	}
	if (reciever->isKeyUp(KEY_KEY_X) && reciever->isKeyUp(KEY_KEY_Z) && reciever->isKeyUp(KEY_KEY_W) && reciever->isKeyUp(KEY_KEY_A) && reciever->isKeyUp(KEY_KEY_S) && reciever->isKeyUp(KEY_KEY_D))
	{
		//player->setIdleAnimation();
	}

	if (reciever->isKeyDown(KEY_KEY_1))
	{
		player->changeWeapon(REVOLVER);
	}
	if (reciever->isKeyDown(KEY_KEY_2))
	{
		player->changeWeapon(REVEVO);
	}
	if (reciever->isKeyDown(KEY_KEY_3))
	{
		player->changeWeapon(MGUN);
	}
	if (reciever->isKeyDown(KEY_KEY_4))
	{
		player->changeWeapon(MGUNB);
	}
	if (reciever->isKeyDown(KEY_KEY_5))
	{
		player->changeWeapon(SMG);
	}
	if (reciever->isKeyDown(KEY_KEY_6))
	{
		player->changeWeapon(LASER);
	}
}

// Function to update position of all GameObjects.
void Game::updateGameObjects(f32 deltaTime)
{
	if (updateList.getSize() != 0)
	{
		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		it = updateList.begin();
		for (int i = 0; i < updateList.getSize(); i++)
		{
			GameObject* ptr = NULL;
			list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
			if (updateList.getSize() == 0)
			{
				return;
			}
			if (it.operator!=(tempIterator))
			{
				ptr = it.operator*();
			}

			if (ptr != NULL)
			{
				if (!ptr->needsUpdate())
				{
					ptr->kill();
					ptr->getNode()->remove();
					updateList.erase(it);
				}
				else
				{
					ptr->update(deltaTime);
					it.operator++();
				}
			}
		}
	}
}

// Function to handle Game State.
void Game::handleGameState(GameState & gameState, Player* player, IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver)
{
	switch (gameState)
	{
	case MAIN_MENU:
		if (!bMainMenuDisplayed)
		{
			displayMainMenu(gameState, irrDevice);
			bMainMenuDisplayed = true;
		}
		bGameCompleteDisplayed = false;
		bGameOverDisplayed = false;
		break;

	case WAVE_1:
		if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		else if (bWave1Finished)
		{
			gameState = WAVE_2;
		}
		else if (!bWave1Started && updateList.getSize() == 0)
		{
			bMainMenuDisplayed = false;
			initiateWave1(player, irrDevice, smgr, driver);
			std::cout << "Wave 1 started.\n";
			irrDevice->getGUIEnvironment()->clear();
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	case WAVE_2:
	/*	if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		if (bWave2Finished)
		{
			gameState = WAVE_3;
		}
		else if (!bWave2Started && updateList.getSize() == 0)
		{
			initiateWave2(player, irrDevice, smgr, driver);
			std::cout << "Wave 2 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}*/
		break;

	case WAVE_3:
		/*if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		if (bWave3Finished)
		{
			gameState = WAVE_4;
		}
		else if (!bWave3Started && updateList.getSize() == 0)
		{
			initiateWave3(player, irrDevice, smgr, driver);
			std::cout << "Wave 3 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}*/
		break;

	case WAVE_4:
	/*	if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		if (bWave4Finished)
		{
			gameState = WAVE_5;
		}
		else if (!bWave4Started && updateList.getSize() == 0)
		{
			initiateWave4(player, irrDevice, smgr, driver);
			std::cout << "Wave 4 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}*/
		break;

	case WAVE_5:
	/*	if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		if (bWave5Finished && updateList.getSize() == 0)
		{
			gameState = GAME_COMPLETE;
		}
		else if (!bWave5Started && updateList.getSize() == 0)
		{
			initiateWave5(player, irrDevice, smgr, driver);
			std::cout << "Wave 5 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}*/
		break;

	case GAME_COMPLETE:
		//if (!bGameCompleteDisplayed)
		//{
		//	displayGameCompleteScreen(driver, irrDevice->getGUIEnvironment());
		//	bGameCompleteDisplayed = true;
		//	delayTimer = irrDevice->getTimer()->getTime();
		//}
		//else
		//{
		//	// Delay for 5 seconds.
		//	if ((irrDevice->getTimer()->getTime() - delayTimer) > 5000)
		//	{
		//		irrDevice->closeDevice();
		//	}
		//}
		break;

	case GAME_OVER:
		//if (!bGameOverDisplayed)
		//{
		//	displayGameOverScreen(driver, irrDevice->getGUIEnvironment());
		//	bGameOverDisplayed = true;
		//	delayTimer = irrDevice->getTimer()->getTime();
		//}
		//else
		//{
		//	// Delay for 5 seconds.
		//	if ((irrDevice->getTimer()->getTime() - delayTimer) > 5000)
		//	{
		//		irrDevice->closeDevice();
		//	}
		//}
		break;

	default:
		break;
	}
}

void Game::displayMainMenu(GameState & gameState, IrrlichtDevice* device)
{
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	IGUISkin* skin = guienv->getSkin();
	IGUIFont* font = guienv->getFont("Textures/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	guienv->addImage(device->getVideoDriver()->getTexture("Textures/Menu.bmp"), vector2d<s32>(0, 0), false);
	guienv->addButton(rect<s32>(210, 100, 450, 170), NULL, GUI_ID_PLAY_BUTTON, L"Play");
	guienv->addButton(rect<s32>(210, 200, 450, 270), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"Instructions");
	guienv->addButton(rect<s32>(210, 300, 450, 370), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
	guienv->addButton(rect<s32>(210, 400, 450, 470), NULL, GUI_ID_QUIT_BUTTON, L"Exit");

}

// Function to start Wave 1.
void Game::initiateWave1(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave1Started = true;

	// Spawn Monster.
	for (int i = 0; i < 3; ++i)
	{
		//spawnMonster(player, device, smgr, driver);
	}

	timeSinceStart = device->getTimer()->getTime();
}

// Function to determine if wave is finished or player is dead.
void Game::updateWaveStatus(GameState & gameState, IrrlichtDevice* device, Player* player, ISceneManager* smgr, IVideoDriver* driver)
{
	// Check if updateList has any Enemy objects.
	bool bEnemyFound = false;

	switch (gameState)
	{
	case WAVE_1:
		if ((device->getTimer()->getTime() - timeSinceStart) > 10000.0f && bWave1Started && !bWave1Finished)
		{
			for (int i = 0; i < 5; ++i)
			{
				//spawnMonster(player, device, smgr, driver);
			}
			std::cout << "Wave 1 afterwave spawned.\n";
			bWave1Finished = true;
		}
		break;

	case WAVE_2:
		/*if ((device->getTimer()->getTime() - timeSinceStart) > 15000.0f && bWave2Started && !bWave2Finished)
		{
			for (int i = 0; i < 5; ++i)
			{
				spawnBadFaerie(player, device, smgr, driver);
			}
			std::cout << "Wave 2 afterwave spawned.\n";
			bWave2Finished = true;
		}*/
		break;

	case WAVE_3:
		/*if ((device->getTimer()->getTime() - timeSinceStart) > 20000.0f && bWave3Started && !bWave3Finished)
		{
			for (int i = 0; i < 3; ++i)
			{
				spawnWraith(player, device, smgr, driver);
			}
			std::cout << "Wave 3 afterwave spawned.\n";
			bWave3Finished = true;
		}*/
		break;

	case WAVE_4:
		/*if ((device->getTimer()->getTime() - timeSinceStart) > 25000.0f && bWave4Started && !bWave4Finished)
		{
			if (pickup_0 != NULL)
				pickup_1 = new HealthPickup(vector3df(200, 50, 200), 0, smgr, driver);
			else
				pickup_1 = new HealthPickup(vector3df(300, 50, 300), 0, smgr, driver);

			for (int i = 0; i < 2; ++i)
			{
				spawnMonster(player, device, smgr, driver);
			}

			for (int i = 0; i < 5; ++i)
			{
				spawnBadFaerie(player, device, smgr, driver);
			}
			std::cout << "Wave 4 afterwave spawned.\n";
			bWave4Finished = true;
		}*/
		break;

	case WAVE_5:
	/*	if ((device->getTimer()->getTime() - timeSinceStart) > 30000.0f && bWave5Started && !bWave5Finished)
		{
			for (int i = 0; i < 5; ++i)
			{
				spawnBadFaerie(player, device, smgr, driver);
			}
			for (int i = 0; i < 5; ++i)
			{
				spawnWraith(player, device, smgr, driver);
			}
			std::cout << "Wave 5 afterwave spawned.\n";
			bWave5Finished = true;
		}*/
		break;

	default:
		break;
	}
}

