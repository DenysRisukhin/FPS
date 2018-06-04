#include "Game.h"

Game::Game()
{
	updateList = list<GameObject*>();
	lastUpdate = 0.0f;
	timeSinceStart = 0.0f;
	selector = NULL;
	delayTimer = 0;
	
	gamePaused = false;
	bMainMenuDisplayed = false;
	bGameOverDisplayed = false;
	bGameCompleteDisplayed = false;
	numOfEnemies = 0;

	bWave1Finished = false;
	bWave1Started = false;
}

u8 Game::getNumOfEnemies()
{
	return numOfEnemies;
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
					ptr->getNode()->remove(); // err
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

//-------------------------------------------------
// Handle all the collisions.
void Game::handleCollisions(Player* player, Camera* camera, f32 deltaTime)
{
	handleCollisionWithPlayer(player, camera, deltaTime);
	handleCollisionEnemyPowerBall();
}

// Handle collisions between Enemies and PowerBalls.
void Game::handleCollisionEnemyPowerBall(void)
{
	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL)
			{

				// Enemy instance.
				if (collisionsBetweenEnemyAndBalls(ptr->getNode()))
				{
					// Removing enemy from updateList.
					--numOfEnemies;
					updateList.erase(it);
					continue;
				}

				handleCollisionBetweenEnemies(ptr);
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				return;
			}
		}
	}
}

// Handle collision of GameObjects with the player.
void Game::handleCollisionWithPlayer(Player* player, Camera* camera, f32 deltaTime)
{
	sound = player->getSound();
	//-------------------------------

	// Now for the other GameObjects.
	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all the GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for BadFaerie.
			ptr = dynamic_cast<BadFaerie*>(it.operator*());
			if (ptr != NULL)
			{
				// BadFaerie instance.
				const aabbox3df boxForFaerie = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForFaerie.intersectsWithBox(boxForPlayer))
				{

					//player->moveBackward(deltaTime);
					player->takeDamage(POWER_BALL);

				

					std::cout << "Collision between player and BadFaire.\n";

					ISound *bang = sound->play2D("sounds/damage.wav", false, true);
					bang->setVolume(0.4f);
					bang->setIsPaused(false);
					bang->drop();
				}


				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}

			
		}
	}
}

// Function to handle collisions between Enemy and Powerball.
bool Game::collisionsBetweenEnemyAndBalls(ISceneNode* enemy)
{
	if (updateList.getSize() != 0)
	{
		GameObject* ptr1 = NULL, *ptr2 = NULL, *ptr3 = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects to detect PowerBalls.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return false;
			}

			ptr1 = dynamic_cast<CGunProjectile*>(it.operator*());
			ptr3 = dynamic_cast<CLaserProjectile*>(it.operator*());

			ptr2 = dynamic_cast<PowerBall*>(it.operator*());

			// Check for PowerBall.
			if (ptr1 != NULL && ptr2 == NULL)
			{
				// PowerBall instance.
				if (ptr1->getNode() == NULL)
				{
					it.operator++();
					continue;
				}

				// COLLISION WITH Ray
				core::line3df ray(ptr1->getPreviousPosition(), ptr1->getPosition());

				if (enemy->getTransformedBoundingBox().intersectsWithLine(ray)) {
					std::cout << "Collision  with GunProjectile occurred.\n";

					ISound *bang = sound->play2D("sounds/crash.wav", false, true);
					bang->setVolume(0.9f);
					bang->setIsPaused(false);
					bang->drop();

					// Removing enemy from the scene.
					enemy->remove();

					// Removing PowerBall from scene and updateList.
					ptr1->getNode()->remove();
					updateList.erase(it);

					// Return value to remove enemy from updateList.
					return true;
				}

				// COLLISION WITH BOXES

				//aabbox3df boxForBall = ptr1->getNode()->getTransformedBoundingBox();
				//aabbox3df boxForEnemy = enemy->getTransformedBoundingBox();

				//if (boxForBall.intersectsWithBox(boxForEnemy))
				//{
				//	std::cout << "Collision occurred.\n";
				//	// Removing enemy from the scene.
				//	enemy->remove();

				//	// Removing PowerBall from scene and updateList.
				//	ptr1->getNode()->remove();
				//	updateList.erase(it);

				//	// Return value to remove enemy from updateList.
				//	return true;
				//}

			}
			else if (ptr3 != NULL && ptr2 == NULL)
			{
				// LazeProjectile instance.
				if (ptr3->getNode() == NULL)
				{
					it.operator++();
					continue;
				}

				core::line3df ray2(ptr3->getPreviousPosition(), ptr3->getPosition());

				if (enemy->getTransformedBoundingBox().intersectsWithLine(ray2)) {
					std::cout << "Collision with LazeProjectile occurred.\n";
					// Removing enemy from the scene.
					enemy->remove();

					// Removing PowerBall from scene and updateList.
					ptr3->getNode()->remove();
					updateList.erase(it);

					// Return value to remove enemy from updateList.
					return true;
				}

			}

			// Check for it.current = NULL.
			if (tempIterator.operator==(it))
			{
				return false;
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				return false;
			}
		}
	}
	return false;
}

// Function to handle collision between two enemies.
void Game::handleCollisionBetweenEnemies(GameObject* enemy)
{
	Enemy* firstEnemy = dynamic_cast<Enemy*>(enemy);

	if (firstEnemy == NULL)
	{
		return;
	}

	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL)
			{
				// Enemy instance.
				Enemy* secondEnemy = dynamic_cast<Enemy*>(ptr);

				const aabbox3df boxForFirst = firstEnemy->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForSecond = secondEnemy->getNode()->getTransformedBoundingBox();

				if (boxForFirst.intersectsWithBox(boxForSecond))
				{
					vector3df direction = firstEnemy->getPosition() - secondEnemy->getPosition();
					direction.normalize();

					firstEnemy->getNode()->setPosition(firstEnemy->getPosition() + (direction * firstEnemy->getSpeed()));
					secondEnemy->getNode()->setPosition(secondEnemy->getPosition() + (-1.0f * direction * secondEnemy->getSpeed()));
				}
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				return;
			}
		}
	}
}
//-------------------------------------------------

void Game::setBWave1Started(){
	bWave1Started = false;
	bWave1Finished = false;

	bGameCompleteDisplayed = false;
	bGameOverDisplayed = false;
}

void Game::clearUpdateList() {

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

// Function to handle Game State.
void Game::handleGameState(GameState & gameState, Player* player, IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver)
{
	switch (gameState)
	{

	case INGAME:
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
			if (!getNumOfEnemies()) {
				std::cout << "GAME_COMPLETE.\n";
				gameState = GAME_COMPLETE;
			}
		}
		else if (!bWave1Started)
		{
			initiateWave1(player, irrDevice, smgr, driver);
			std::cout << "Wave 1 started.\n";
			irrDevice->getGUIEnvironment()->clear();
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	default:
		break;
	}
}

// Function to start Wave 1.
void Game::initiateWave1(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave1Started = true;

	// Spawn BadFaerie.
	for (int i = 0; i < 35; ++i)
	{
		spawnBadFaerie(player, device, smgr, driver);
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
	case INGAME:
		if ((device->getTimer()->getTime() - timeSinceStart) > 10000.0f && bWave1Started && !bWave1Finished)
		{
			/*for (int i = 0; i < 10; ++i)
			{
				spawnBadFaerie(player, device, smgr, driver);
			}*/
			std::cout << "Wave 1 afterwave spawned.\n";
			bWave1Finished = true;
		}
		break;

	default:
		break;
	}
}

// Function to spawn BadFaerie instance.
void Game::spawnBadFaerie(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	++numOfEnemies;

	bool bMatched;

	vector3df position = vector3df(0, 80, 0);

	GameObject* ptr = NULL;

	list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
	list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
	it = updateList.begin();

	srand(time(NULL));
	while (true)
	{
		bMatched = false;

		for (int i = 0; i < updateList.getSize(); ++i)
		{
			if (tempIterator.operator==(it))
			{
				break;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());

			if (ptr != NULL)
			{
				if (ptr->getPosition() == position)
				{
					bMatched = true;
					break;
				}
			}

			if (tempIterator.operator==(it.operator++()))
			{
				break;
			}
		}

		if (!bMatched && (position - player->getPosition()).getLengthSQ() > 250000.0f)
		{
			break;
		}

		position = vector3df(100 + (rand() % 900), 80, 100 + (rand() % 900));
	}

	// Setting up BadFaerie.
	badFaerie = new BadFaerie(position, 0.1f, smgr, player, device, &updateList, device->getVideoDriver());
	badFaerie->loadModel(smgr->getMesh("Models/faerie.md2"), driver->getTexture("Textures/faerie.bmp"));
	updateList.push_back(badFaerie);
	const aabbox3df & box2 = badFaerie->getNode()->getBoundingBox();
	vector3df radius = box2.MaxEdge - box2.getCenter();
	badFaerie->getNode()->addAnimator(smgr->createCollisionResponseAnimator(selector, badFaerie->getNode(), radius));

#ifdef DEBUG
	std::cout << "\nBadFaerie spawned.\n";
#endif
}

void Game::processInput(IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, ITriangleSelector* selector, EventReciever* reciever, Player* player, Camera* camera, f32 deltaTime)
{
	bool pPressed = false;

	if (reciever->getMouse() == EMIE_LMOUSE_PRESSED_DOWN) {

		player->fire(player->getWeapon(), device);
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