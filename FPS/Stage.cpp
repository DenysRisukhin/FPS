#include "Stage.h"

Stage::Stage() :
	gui(new GUI()),
	texManager(new TextureManager()),
	engine(new Irrlicht(L"FPS", dimension2du(WINDOW_WIDTH, WINDOW_HEIGHT))),
	gameState(MENU),
	sound(createIrrKlangDevice()),
	soundPlay(true),
	terrain(NULL)
{
	srand(time(NULL));
}

void Stage::setPause(bool pause){
	hideCursor();

	if (!pause){
		timer.zeroTimes();
		engine->setTime(0);
	}
}

void Stage::hideCursor() {
	engine->hideCursor(true);
	engine->setCursorToCenter();
	engine->resetInput();
}

void Stage::menuClickSound() {
	auto bang = sound->play2D("sounds/select.wav", false, true);
	bang->setVolume(0.9f);
	bang->setIsPaused(false);
	bang->drop();
}

void Stage::menu(){
	switch (gameState)
	{
	case MENU:
		if (gui->isButtonPressed(START_BUTTON)){
			menuClickSound();
			gameState = INGAME;
			setPause(false);
		}
		else if (gui->isButtonPressed(OPTIONS_BUTTON)){
			menuClickSound();
			engine->getGUI()->addImage(engine->getVideo()->getTexture("Textures/background1.png"), vector2d<s32>(-235, 0), false);
			gameState = OPTIONS;
			gui->options(engine->getGUI(), texManager);
		}
		else if (gui->isButtonPressed(QUIT_BUTTON)){
			menuClickSound();
			gameState = EXIT;
		}
		break;
	case OPTIONS:
		if (gui->isButtonPressed(BACK_BUTTON)){
			menuClickSound();
			gameState = MENU;
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}
		else if (gui->getMusicSelection() == MUSIC_ENABLE){
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
		if (gui->isButtonPressed(BACK_BUTTON)){
			menuClickSound();
			gameState = MENU;
			drop();
			engine->hideCursor(false);
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}
		else if (gui->isButtonPressed(RESUME_BUTTON)){
			menuClickSound();
			gameState = INGAME;
			camera->getNode()->setInputReceiverEnabled(true);
			timer.addDelta(engine->getCurrentTime() - timer.pauseTime);
			setPause(true);
		}
		else if (gui->isButtonPressed(QUIT_BUTTON)){
			menuClickSound();
			gameState = EXIT;
		}
		break;
	case OVER:
		if (gui->isButtonPressed(START_BUTTON)){
			menuClickSound();
			drop();
			gameState = INGAME;
			setPause(false);
		}
		else if (gui->isButtonPressed(BACK_BUTTON)){
			menuClickSound();
			gameMusic->setIsPaused(false);
			gameState = MENU;
			drop();
			engine->hideCursor(false);
			gui->menu(engine->getGUI(), texManager, engine->getVideo());
		}
		else if (gui->isButtonPressed(QUIT_BUTTON)){
			menuClickSound();
			gameState = EXIT;
		}
		break;
	}
}

void Stage::loop(){

	texManager->loadTextures(engine->getVideo());

	// Loading Menu & logoImage.
	gui->menu(engine->getGUI(), texManager, engine->getVideo());

	gameMusic = sound->play2D("sounds/soundtrack.mp3", true, false, true);
	
	gameState = MENU;

	bool exitFlag = false;

	while (engine->run()){
		switch (gameState)
		{
		case MENU:
		case OPTIONS:
		case PAUSE:
		case OVER:
			menu();
			break;

		case INGAME:
			actionPhase();
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

void Stage::actionPhase(){
	// Counting time since last frame.
	timer.presentTime = engine->getCurrentTime();
	timer.delta = timer.presentTime - timer.lastTime;
	timer.lastTime = timer.presentTime;

	// Re-initialize game data after deletion.
	if (!terrain) 
		initGameData();

	// Add labels, crosshair & health images.
	if (gameState == INGAME) {
		gui->game(engine->getGUI(), texManager, engine->getVideo());
		gui->setHealthLabel(player->getHealth());
	}

	// Activating pause.
	if (reciever->isKeyDown(KEY_ESCAPE)){
		gameState = PAUSE;
		timer.pauseTime = engine->getCurrentTime();
		gui->pause(engine->getGUI(), texManager);

		engine->hideCursor(false);
		engine->resetInput();

		camera->getNode()->setInputReceiverEnabled(false);
	}
	
	// Checking InGame States.
	if (gameState == INGAME || gameState == GAME_COMPLETE || gameState == GAME_OVER) {

		// Cheking GAME_COMPLETE or GAME_OVER states when INGAME state is active.
		app.handleWinLoseState(gameState, player, engine->getDevice(), engine->getManager(), engine->getVideo());
	
		// Handling user input.
		app.processInput(engine->getDevice(), engine->getManager(), engine->getVideo(), selector, reciever, player, camera, timer.delta);
	
		// Updating position for every object from GameObject.
		app.updateGameObjects(timer.delta);
	
		// Handling collisions between BadFaerie and projectiles.
		app.handleCollisions(player, camera, timer.delta);

		gui->setWeaponTexture(engine->getGUI(),engine->getVideo(), player);

		// Processing GAME_COMPLETE || GAME_OVER states.
		processingResultScreen();
	}
}

void Stage::initGameData() {
	// Instantiating game objects.
	terrain = new Terrain(engine->getManager(), engine->getVideo());
	camera = new Camera(engine->getManager());
	player = new Player(engine->getDevice(), engine->getManager(), engine->getVideo(), camera, &(app.getUpdateList()));
	skybox = new Skybox(engine->getManager(), engine->getVideo());
	engine->getManager()->setShadowColor();

	reciever = new EventReciever();
	engine->getDevice()->setEventReceiver(reciever);

	// Adding collision detector for the terrain.
	ITriangleSelector* selector = engine->getManager()->createTerrainTriangleSelector(terrain->getNode());
	terrain->getNode()->setTriangleSelector(selector);

	const aabbox3d<f32> &box = camera->getNode()->getBoundingBox();
	vector3df radius = box.MaxEdge - box.getCenter();

	// Creates a collision auto response animator.
	ISceneNodeAnimator* anim = engine->getManager()->createCollisionResponseAnimator(selector, camera->getNode(),
		vector3df(30, 45, 30),
		getGravity("earth"),
		vector3df(0, 40, 0),
		0.0005f
	);

	camera->getNode()->addAnimator(anim);
}

void Stage::processingResultScreen() {

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
}

void Stage::drop() {
	app.setBWaveStarted();
	app.clearUpdateList();
	app.setNumOfEnemies(0);

	player->getNode()->remove();
	skybox->getNode()->remove();
	camera->getNode()->remove();
	terrain->getNode()->remove();
	terrain = NULL;
}

vector3df Stage::getGravity(const c8 * surface) {
	if (0 == strcmp(surface, "earth")) return vector3df(0.f, -60.f, 0.f);
	if (0 == strcmp(surface, "moon")) return vector3df(0.f, -6.f / 100.f, 0.f);
	if (0 == strcmp(surface, "water")) return vector3df(0.1f / 100.f, -2.f / 100.f, 0.f);
	if (0 == strcmp(surface, "ice")) return vector3df(0.2f / 100.f, -9.f / 100.f, 0.3f / 100.f);

	return vector3df(0.f, 0.f, 0.f);
}