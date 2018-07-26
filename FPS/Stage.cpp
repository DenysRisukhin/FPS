#include "Stage.h"

vector3df getGravity(const c8 * surface)
{
	if (0 == strcmp(surface, "earth")) return vector3df(0.f, -60.f, 0.f);
	if (0 == strcmp(surface, "moon")) return vector3df(0.f, -6.f / 100.f, 0.f);
	if (0 == strcmp(surface, "water")) return vector3df(0.1f / 100.f, -2.f / 100.f, 0.f);
	if (0 == strcmp(surface, "ice")) return vector3df(0.2f / 100.f, -9.f / 100.f, 0.3f / 100.f);

	return vector3df(0.f, 0.f, 0.f);
}

Stage::Stage() :
	gui(new GUI()),
	texManager(new TextureManager()),
	engine(new Irrlicht(L"FPS", dimension2du(1024, 768))),
	gameState(MENU),
	sound(createIrrKlangDevice()),
	soundPlay(true),
	terrain(NULL)
{
	srand(time(NULL));
}

void Stage::toLevel(bool pause)
{
	engine->hideCursor(true);
	engine->setCursorToCenter();
	engine->resetInput();

	if (!pause)
	{
		timer.zeroTimes();
		engine->setTime(0);
	}
}

void Stage::menuClick() {
	auto bang = sound->play2D("sounds/select.wav", false, true);
	bang->setVolume(0.9f);
	bang->setIsPaused(false);
	bang->drop();
}

void Stage::menu()
{

	switch (gameState)
	{
	case MENU:
		if (gui->isButtonPressed(START_BUTTON))
		{
			menuClick();
			gameState = INGAME;
			toLevel(false);
		}
		else if (gui->isButtonPressed(OPTIONS_BUTTON))
		{
			menuClick();
			engine->getGUI()->addImage(engine->getVideo()->getTexture("Textures/background1.png"), vector2d<s32>(-235, 0), false);
			gameState = OPTIONS;
			gui->options(engine->getGUI(), texManager);
		}
		else if (gui->isButtonPressed(QUIT_BUTTON)) {
			menuClick();
			gameState = EXIT;
		}
		break;

	case OPTIONS:
		if (gui->isButtonPressed(BACK_BUTTON))
		{
			menuClick();
			gameState = MENU;
			gui->menu(engine->getGUI(), texManager, engine->getVideo());

		
		}

		else if (gui->getMusicSelection() == MUSIC_ENABLE)
		{
			if (gameMusic->getIsPaused())
				gameMusic = sound->play2D("sounds/soundtrack.mp3", true, false, true);
		}

		else if (gui->getMusicSelection() == MUSIC_DISABLE)
			gameMusic->setIsPaused(true);

		if (gui->getSoundSelection() == SOUND_ENABLE)
			soundPlay = true;

		else if (gui->getSoundSelection() == SOUND_DISABLE)
			soundPlay = false;
		break;

	case PAUSE:
		if (gui->isButtonPressed(BACK_BUTTON))
		{
			menuClick();

			gameState = MENU;
			
			app.setBWave1Started();
	
			app.clearUpdateList();
			app.setNumOfEnemies(0);
			
			player->getNode()->remove();
			skybox->getNode()->remove();
			camera->getNode()->remove();
			terrain->getNode()->remove();
			terrain = NULL;
		
			engine->hideCursor(false);
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}

		else if (gui->isButtonPressed(RESUME_BUTTON))
		{
			menuClick();

			gameState = INGAME;

			camera->getNode()->setInputReceiverEnabled(true);

			u32 delta = engine->getNow() - timer.pauseTime;
			timer.addDelta(delta);

			toLevel(true);
		}

		else if (gui->isButtonPressed(QUIT_BUTTON)) {
			menuClick();
			gameState = EXIT;
		}

		break;

	case OVER:
		
		if (gui->isButtonPressed(START_BUTTON))
		{
			menuClick();

			app.setBWave1Started();
			app.clearUpdateList();
			app.setNumOfEnemies(0);

			player->getNode()->remove();
			skybox->getNode()->remove();
			camera->getNode()->remove();
			terrain->getNode()->remove();
			terrain = NULL;

			gameState = INGAME;
			toLevel(false);
		}
		else if (gui->isButtonPressed(BACK_BUTTON))
		{
			menuClick();

			gameMusic->setIsPaused(false);

			gameState = MENU;
			//drop();

			app.setBWave1Started();
			app.clearUpdateList();
			app.setNumOfEnemies(0);

			player->getNode()->remove();
			skybox->getNode()->remove();
			camera->getNode()->remove();
			terrain->getNode()->remove();
			terrain = NULL;

			engine->hideCursor(false);
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}
		else if (gui->isButtonPressed(QUIT_BUTTON)) {
			menuClick();
			gameState = EXIT;
		}
		break;
	}

}

void Stage::loop()
{
	// Textures
	texManager->loadTextures(engine->getVideo());

	// Menu
	gui->menu(engine->getGUI(), texManager, engine->getVideo());

	//// Music
	gameMusic = sound->play2D("sounds/soundtrack.mp3", true, false, true);
	
	gameState = MENU;

	bool exitFlag = false;

	while (engine->run())
	{
		switch (gameState)
		{
		case MENU:
		case OPTIONS:
		case PAUSE:
		case OVER:
			menu();
			break;

		case INGAME:
			game();
			break;

		case EXIT:
			exitFlag = true;
			break;
		}

		if (exitFlag)
			break;

		engine->drawAll();
		
	}

	texManager->drop();
	engine->drop();
	sound->drop();
}

void Stage::drop()
{	
	//player->getNode()->drop();
	//camera->getNode()->drop();
	//app;
	//terrain->getNode()->drop();
	//reciever->re

	//selector->drop();
	//camera->getNode()->drop();
}

void Stage::game()
{
	// Counting time since last frame
	timer.now = engine->getNow();
	timer.delta = (f32)(timer.now - timer.lastTime) / 1000.f;
	timer.lastTime = timer.now;

	if (!terrain) {

	    // Instantiating game objects.
		terrain = new Terrain(engine->getManager(), engine->getVideo());
		camera = new Camera(engine->getManager());
		player = new Player(engine->getDevice(), engine->getManager(), engine->getVideo(), camera, &(app.getUpdateList())); // list<GameObject*>();
		skybox = new Skybox(engine->getManager(), engine->getVideo());
		engine->getManager()->setShadowColor();

		reciever = new EventReciever();
		engine->getDevice()->setEventReceiver(reciever);

		// Adding collision detector for the terrain.
		ITriangleSelector* selector = engine->getManager()->createTerrainTriangleSelector(terrain->getNode());
		terrain->getNode()->setTriangleSelector(selector);

		const aabbox3d<f32> &box = camera->getNode()->getBoundingBox();
		vector3df radius = box.MaxEdge - box.getCenter();

		//create a collision auto response animator
		ISceneNodeAnimator* anim = engine->getManager()->createCollisionResponseAnimator(selector, camera->getNode(),
			vector3df(30, 45, 30),
			getGravity("earth"),
			vector3df(0, 40, 0),
			0.0005f
		);

		camera->getNode()->addAnimator(anim);

		bPressed = false;
		lastPress = 0;

		deltaTime = 0.0f;
		previousTime = 0.0f, presentTime = 0.0f;

#ifdef DEBUG
		previous = 0.0f;
		now = 0.0f;
#endif

		IVideoDriver* driver2 = engine->getVideo();

		auto img = engine->getGUI()->addImage(engine->getVideo()->getTexture("Textures/1.jpg"), core::position2d<int>(10, 10));

		
		startTime = engine->getDevice()->getTimer()->getTime();
		elapsedTime = 0;

		u32 shotPause = 0;
	}

	if (gameState == INGAME) {
		gui->game(engine->getGUI(), texManager, engine->getVideo());
		gui->setHealth(player->getHealth());
	}

	if (reciever->isKeyDown(KEY_ESCAPE))
	{
		gameState = PAUSE;
		timer.pauseTime = engine->getNow();
		gui->pause(engine->getGUI(), texManager);

		engine->hideCursor(false);
		engine->resetInput();

		camera->getNode()->setInputReceiverEnabled(false);
	}

	
	elapsedTime = engine->getDevice()->getTimer()->getTime() - startTime;
	startTime = engine->getDevice()->getTimer()->getTime();

	// Ensuring frame independant update.
	presentTime = engine->getDevice()->getTimer()->getTime();
	deltaTime = presentTime - previousTime;


	previousTime = presentTime;
	
	// Checking Game State.
	if (gameState == INGAME || gameState == GAME_COMPLETE || gameState == GAME_OVER) {
	app.handleGameState(gameState, player, engine->getDevice(), engine->getManager(), engine->getVideo());
	
	// Function to handle user input.
	app.processInput(engine->getDevice(), engine->getManager(), engine->getVideo(), selector, reciever, player, camera, deltaTime);
	
	// Updating position of all GameObjects.
	app.updateGameObjects(deltaTime);
	
	// Handle collisions between faerie and powerballs.
	app.handleCollisions(player, camera, deltaTime);

	gui->setWeapon(engine->getGUI(),engine->getVideo(), player);

}

	ISound *bang = NULL;

	switch (gameState) {
	case GAME_COMPLETE:
		std::cout << "stage GAME_COMPLETE.\n";
		
		bang = sound->play2D("sounds/win.wav", false, true);
		bang->setVolume(0.9f);
		bang->setIsPaused(false);
		bang->drop();

		gameMusic->setIsPaused(true);

			
	    engine->getGUI()->addImage(engine->getVideo()->getTexture("Textures/GameComplete.jpg"), vector2d<s32>(-235, 0), false);

		engine->hideCursor(false);
		gui->win(engine->getGUI(), texManager);
			
		gameState = OVER;

		camera->getNode()->setInputReceiverEnabled(false);
		
		
		break;
	case GAME_OVER:
		std::cout << "stage GAME_OVER.\n";

		bang = sound->play2D("sounds/lose.wav", false, true);
		bang->setVolume(0.9f);
		bang->setIsPaused(false);
		bang->drop();

		gameMusic->setIsPaused(true);
	    engine->getGUI()->addImage(engine->getVideo()->getTexture("Textures/GameOver.jpg"), vector2d<s32>(-235, 0), false);

		engine->hideCursor(false);
		gui->lose(engine->getGUI(), texManager);
			
    	gameState = OVER;
		camera->getNode()->setInputReceiverEnabled(false);
		
		break;
	}

#ifdef DEBUG
	now = engine->getDevice()->getTimer()->getTime();
	if ((now - previous) > 5000.0f)
	{
		//std::cout << "\nDelta Time = " << deltaTime << std::endl;
		//std::cout << "FPS = " << (1000.0f / deltaTime) << "\n\n";
		//std::cout << "Player position = " << player->getPosition().X << ", " << player->getPosition().Y << ", " << player->getPosition().Z << std::endl;
		std::cout << "Number of Enemies = " << (int)app.getNumOfEnemies() << std::endl;
		previous = now;
	}
#endif
}

