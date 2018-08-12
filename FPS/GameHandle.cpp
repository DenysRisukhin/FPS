#include "GameHandle.h"

GameHandle::GameHandle(){
	updateList = list<GameObject*>();
	timeSinceStart = 0.0f;
	selector = NULL;
	
	bMainMenuDisplayed = false;
	bGameOverDisplayed = false;
	bGameCompleteDisplayed = false;
	numOfEnemies = 0;

	bWaveFinished = false;
	bWaveStarted = false;
}

void GameHandle::setNumOfEnemies(u8 num) {
	numOfEnemies = num;
}

u8 GameHandle::getNumOfEnemies(){
	return numOfEnemies;
}

list<GameObject*>& GameHandle::getUpdateList() {
	return updateList;
}

void GameHandle::updateGameObjects(f32 deltaTime){
	if (updateList.getSize() != 0){
		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		it = updateList.begin();
		for (int i = 0; i < updateList.getSize(); i++){
			GameObject* ptr = NULL;
			list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
			if (updateList.getSize() == 0){
				return;
			}
			if (it.operator!=(tempIterator)){
				ptr = it.operator*();
			}

			if (ptr != NULL){
				if (!ptr->needsUpdate()){
					ptr->kill();
					ptr->getNode()->remove(); 
					updateList.erase(it);
				}
				else{
					ptr->update(deltaTime);
					it.operator++();
				}
			}
		}
	}
}

void GameHandle::handleCollisions(Player* _player, Camera* camera, f32 deltaTime){
	player = _player;
	// Collisions with player.
	handleCollisionWithPlayer(player, camera, deltaTime);
	handleCollisionPlayerPowerBall();

	// Collisions with enemies.
	callHandleCollisionEnemyPowerBall();
}

void GameHandle::handleCollisionWithPlayer(Player* _player, Camera* camera, f32 deltaTime) {
	sound = _player->getSound();
	//-------------------------------

	// Now for the other GameObjects.
	if (updateList.getSize() != 0){
		GameObject* ptr = NULL;
		GameObject* ptr1 = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all the GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i){
			// Check for it.current = NULL.
			if (it.operator==(tempIterator)){
				return;
			}

			// Check for BadFaerie.
			ptr = dynamic_cast<BadFaerie*>(it.operator*());
			if (ptr != NULL){
				// BadFaerie instance.
				const aabbox3df boxForFaerie = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForFaerie.intersectsWithBox(boxForPlayer)){
					//player->moveBackward(deltaTime);
					player->setDamage(MONSTER_ATTACK);

					std::cout << "Collision between player and BadFaire.\n";

					ISound *bang = sound->play2D("sounds/damage.wav", false, true);
					bang->setVolume(0.4f);
					bang->setIsPaused(false);
					bang->drop();
				}

				// Check for it.current = NULL.
				if (tempIterator.operator==(it)){
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++())){
					return;
				}

				continue;
			}
		}

	}
}

void GameHandle::handleCollisionPlayerPowerBall() {
	if (updateList.getSize() != 0){
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i){
			// Check for it.current = NULL.
			if (it.operator==(tempIterator)){
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<PowerBallProjectile*>(it.operator*());
			if (ptr != NULL){				
					// occurred instance.
					if (ptr->getNode() == NULL){
						it.operator++();
						continue;
					}
					// COLLISION WITH BOXES

					aabbox3df boxForBall = ptr->getNode()->getTransformedBoundingBox();
					aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

					if (boxForBall.intersectsWithBox(boxForPlayer)){
						std::cout << "Collision ENEMIES_POWER_BALLwith Player occurred.\n";

						//player->moveBackward(deltaTime);
						player->setDamage(POWER_BALL);

						ISound *bang = sound->play2D("sounds/damage.wav", false, true);
						bang->setVolume(0.4f);
						bang->setIsPaused(false);
						bang->drop();

						// Removing PowerBall from scene and updateList.
						ptr->kill();
						ptr->getNode()->remove();
						updateList.erase(it);
						continue;
					}	
			}
			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++())){
				return;
			}
		}
	}
}

void GameHandle::callHandleCollisionEnemyPowerBall(){
	if (updateList.getSize() != 0){
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i){
			// Check for it.current = NULL.
			if (it.operator==(tempIterator)){
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL){

				// Enemy instance.
				if (collisionsBetweenEnemyAndProjectiles(ptr->getNode())){
					// Removing enemy from updateList.
					--numOfEnemies;
					updateList.erase(it);
					continue;
				}
				handleCollisionBetweenEnemies(ptr);
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++())){
				return;
			}
		}
	}
}

bool GameHandle::collisionsBetweenEnemyAndProjectiles(ISceneNode* enemy){
	if (updateList.getSize() != 0){
		GameObject* ptr1 = NULL, *ptr3 = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects to detect Projectiles.
		for (int i = 0; i < updateList.getSize(); ++i){
			// Check for it.current = NULL.
			if (it.operator==(tempIterator)){
				return false;
			}

			ptr1 = dynamic_cast<GunProjectile*>(it.operator*());
			ptr3 = dynamic_cast<LaserProjectile*>(it.operator*());

			// Check for Projectiles.
			if (ptr1 != NULL){
				// PowerBall instance.
				if (ptr1->getNode() == NULL){
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

				/* COLLISION WITH BOXES

				aabbox3df boxForBall = ptr1->getNode()->getTransformedBoundingBox();
				aabbox3df boxForEnemy = enemy->getTransformedBoundingBox();

				if (boxForBall.intersectsWithBox(boxForEnemy))
				{*/
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
			else if (ptr3 != NULL){
				// LazeProjectile instance.
				if (ptr3->getNode() == NULL){
					it.operator++();
					continue;
				}

				core::line3df ray2(ptr3->getPreviousPosition(), ptr3->getPosition());

				if (enemy->getTransformedBoundingBox().intersectsWithLine(ray2)) {
					std::cout << "Collision with LazeProjectile occurred.\n";

					ISound *bang = sound->play2D("sounds/crash.wav", false, true);
					bang->setVolume(0.9f);
					bang->setIsPaused(false);
					bang->drop();
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
			if (tempIterator.operator==(it)){
				return false;
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++())){
				return false;
			}
		}
	}
	return false;
}

void GameHandle::handleCollisionBetweenEnemies(GameObject* enemy){
	Enemy* firstEnemy = dynamic_cast<Enemy*>(enemy);

	if (firstEnemy == NULL){
		return;
	}

	if (updateList.getSize() != 0){
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i){
			// Check for it.current = NULL.
			if (it.operator==(tempIterator)){
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL){
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
			if (tempIterator.operator==(it.operator++())){
				return;
			}
		}
	}
}

void GameHandle::setBWaveStarted(){
	bWaveStarted = false;
	bWaveFinished = false;

	bGameCompleteDisplayed = false;
	bGameOverDisplayed = false;
}

void GameHandle::clearUpdateList() {

	if (updateList.size()) {
		for (list<GameObject*>::Iterator it = updateList.begin(); it != updateList.end(); ++it)
		{
			//std::cout << "numOfEnemies:" << (int*)--numOfEnemies << std::endl;
			(*it)->getNode()->remove();
			delete *it;
		}
		updateList.clear();
	}
}

void GameHandle::handleWinLoseState(GameState & gameState, Player* player, IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver, TextureManager *&textureMngr){
	switch (gameState){
	case INGAME:
		if (player->getPosition().Y < 0){
			player->kill();
		}
		if (player->isDead()){
			gameState = GAME_OVER;
		}
		else if (bWaveFinished){
			if (!getNumOfEnemies()) {
				std::cout << "GAME_COMPLETE.\n";
				gameState = GAME_COMPLETE;
			}
		}
		else if (!bWaveStarted){
			initiateWave(player, irrDevice, smgr, driver, textureMngr);
			std::cout << "Wave 1 started.\n";
			irrDevice->getGUIEnvironment()->clear();
		}
		else{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	default:
		break;
	}
}

void GameHandle::initiateWave(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, TextureManager *&textureMngr){
	bWaveStarted = true;

	// Spawn BadFaerie.
	for (int i = 0; i < 5; ++i)
		spawnBadFaerie(player, device, smgr, driver, textureMngr->getEnemyTexture()[0]);

	timeSinceStart = device->getTimer()->getTime();
}


void GameHandle::updateWaveStatus(GameState & gameState, IrrlichtDevice* device, Player* player, ISceneManager* smgr, IVideoDriver* driver){
	// Check if updateList has any Enemy objects.
	bool bEnemyFound = false;

	switch (gameState)
	{
	case INGAME:
		if ((device->getTimer()->getTime() - timeSinceStart) > 10000.0f && bWaveStarted && !bWaveFinished)
		{
			//for (int i = 0; i < 10; ++i)
			//	spawnBadFaerie(player, device, smgr, driver);

			std::cout << "Wave 1 afterwave spawned.\n";
			bWaveFinished = true;
		}
		break;

	default:
		break;
	}
}

void GameHandle::spawnBadFaerie(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, ITexture *&texture){
	++numOfEnemies;

	bool bMatched;

	vector3df position = vector3df(0, 80, 0);

	GameObject* ptr = NULL;

	list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
	list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
	it = updateList.begin();

	srand(time(NULL));
	while (true){
		bMatched = false;

		for (int i = 0; i < updateList.getSize(); ++i){
			if (tempIterator.operator==(it)){
				break;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());

			if (ptr != NULL){
				if (ptr->getPosition() == position){
					bMatched = true;
					break;
				}
			}

			if (tempIterator.operator==(it.operator++())){
				break;
			}
		}

		if (!bMatched && (position - player->getPosition()).getLengthSQ() > 250000.0f){
			break;
		}

		position = vector3df(100 + (rand() % 900), 80, 100 + (rand() % 900));
	}

	// Creates badFaerie.
	badFaerie = new BadFaerie(position, 0.1f, smgr, player, device, &updateList, device->getVideoDriver(), player->getSound());
	badFaerie->loadModel(smgr->getMesh("Models/faerie.md2"), texture);
	updateList.push_back(badFaerie);
	const aabbox3df & box2 = badFaerie->getNode()->getBoundingBox();
	vector3df radius = box2.MaxEdge - box2.getCenter();
	badFaerie->getNode()->addAnimator(smgr->createCollisionResponseAnimator(selector, badFaerie->getNode(), radius));

#ifdef DEBUG
	std::cout << "\nBadFaerie spawned.\n";
#endif
}

void GameHandle::processInput(IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, ITriangleSelector* selector, EventReciever* reciever, Player* player, Camera* camera, f32 deltaTime){
	bool pPressed = false;

	if (reciever->isLeftButtonPressed()) 
		player->fire(player->getWeapon(), device);
	
	if (reciever->isKeyDown(KEY_KEY_1))
		player->changeWeapon(REVOLVER);
	
	if (reciever->isKeyDown(KEY_KEY_2))
		player->changeWeapon(REVEVO);
	
	if (reciever->isKeyDown(KEY_KEY_3))
		player->changeWeapon(MGUN);
	
	if (reciever->isKeyDown(KEY_KEY_4))
		player->changeWeapon(MGUNB);
	
	if (reciever->isKeyDown(KEY_KEY_5))
		player->changeWeapon(SMG);
	
	if (reciever->isKeyDown(KEY_KEY_6))
		player->changeWeapon(LASER);
}