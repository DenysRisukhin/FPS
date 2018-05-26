#include "Game.h"
#include "CHealthPowerupObject.h"


/*!
gets a accumulated force on a given surface
*/
vector3df getGravity(const c8 * surface)
{
	if (0 == strcmp(surface, "earth")) return vector3df(0.f, -60.f, 0.f);
	if (0 == strcmp(surface, "moon")) return vector3df(0.f, -6.f / 100.f, 0.f);
	if (0 == strcmp(surface, "water")) return vector3df(0.1f / 100.f, -2.f / 100.f, 0.f);
	if (0 == strcmp(surface, "ice")) return vector3df(0.2f / 100.f, -9.f / 100.f, 0.3f / 100.f);

	return vector3df(0.f, 0.f, 0.f);
}

int main() {
	
	// Initializing the engine.
	IrrlichtDevice* device = createDevice(EDT_OPENGL, dimension2d<u32>(1024, 768), 32U, false, true);
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	// Making instance of our game.
	Game app;
	//list<GameObject*> &vm = app.getUpdateList();
	//app->getUpdateList();

	// Instantiating game objects.
	Terrain* terrain = new Terrain(smgr, driver);
	Camera* camera = new Camera(smgr);
	Player* player = new Player(device, smgr, driver, camera, &(app.getUpdateList()) ); // list<GameObject*>();
	Skybox* skybox = new Skybox(smgr, driver);
	smgr->setShadowColor();

	// Setup gameHud.
	GameHud* gameHud = new GameHud(device, smgr, driver);

	GameState gameState = GameState::MAIN_MENU;

	// Instantiating EventReciever instance.
	SAppContext context = SAppContext(device, &gameState);
	EventReciever* reciever = new EventReciever(context);
	device->setEventReceiver(reciever);

	// Adding collision detector for the terrain.
	ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain->getNode());
	terrain->getNode()->setTriangleSelector(selector);

	const aabbox3d<f32> &box = camera->getNode()->getBoundingBox();
	vector3df radius = box.MaxEdge - box.getCenter();

	/*if (selector)
	{
		ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector, camera->getNode(), radius);
		camera->getNode()->addAnimator(anim);
	}*/

	//create a collision auto response animator
	ISceneNodeAnimator* anim =
		smgr->createCollisionResponseAnimator(selector, camera->getNode(),
			vector3df(30, 45, 30),
			getGravity("earth"),
			vector3df(0, 40, 0),
			0.0005f
		);
	camera->getNode()->addAnimator(anim);

	bool bPressed = false;
	u32 lastPress = 0;

	f32 deltaTime = 0.0f;
	f32 previousTime = 0.0f, presentTime = 0.0f;

#ifdef DEBUG
	f32 previous = 0.0f;
	f32 now = 0.0f;
#endif

	IVideoDriver* driver2 = device->getVideoDriver();

	///

	bool playerShoot = true;
	s32 startTime, elapsedTime, endTime;

//	device->getTimer()->start();
	//device->getTimer()->setTime(0);
	

	//// Create a visual representation
	//scene::ISceneNode* Cube = smgr->addCubeSceneNode(5);
	//if (Cube) {
	//	Cube->setPosition(core::vector3df(0, 2.5f, 0));
	//	Cube->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("stuff/life.jpg"));
	//	Cube->setMaterialFlag(video::EMF_LIGHTING, false);
	//}
	//else printf("ERROR: Failed cube creation\n");

	////ammo
	//scene::ISceneNode* Cubeb = smgr->addCubeSceneNode(5);
	//if (Cubeb) {
	//	Cubeb->setPosition(core::vector3df(0, 8.5f, 0));
	//	Cubeb->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("stuff/ammo.jpg"));
	//	Cubeb->setMaterialFlag(video::EMF_LIGHTING, false);
	//}
	//else printf("ERROR: Failed cube creation\n");


	//IGUIEnvironment* env1 = device->getGUIEnvironment();

	//video::ITexture* images = driver->getTexture("Textures/1.jpg");
	//images->setSca

	//env1->addImage(images, position2d<int>(10, 10));

	ITexture* tex = driver->getTexture("Textures/1.jpg");

	// Give to addImage() the XY coords of 2 points :
	IGUIImage* img = guienv->addImage(core::rect<s32>(10, 10, 100, 225));
	img->setImage(tex);
	img->setScaleImage(true);
	//driver->removeTexture(tex);

	//driver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
	//driver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;

	//app.processInput(device, smgr, driver, selector, reciever, player, camera, deltaTime);
	//CHealthPowerupObject pi(player, smgr, {0,0,0});

	startTime = device->getTimer()->getTime();
	elapsedTime = 0;

	u32 shotPause = 0;
	// Main game loop.
	while (device->run())
	{
		if (!device->isWindowActive())
		{
			device->yield();
			continue;
		}

		elapsedTime = device->getTimer()->getTime() - startTime;
		startTime = device->getTimer()->getTime();

		// Ensuring frame independant update.
		presentTime = device->getTimer()->getTime();
		deltaTime = presentTime - previousTime;

		
		// To pause/unpause the game.
		if (reciever->isKeyDown(KEY_KEY_P) && (device->getTimer()->getTime() - lastPress) > 2000)
		{
			app.gamePaused = !(app.gamePaused);

#ifdef DEBUG
			std::cout << "\ngamePaused = " << std::boolalpha << app.gamePaused << std::endl;
#endif

			lastPress = device->getTimer()->getTime();
		}

		
//
//		// Maintaining FPS around 60
		if (deltaTime > 16 && !app.gamePaused)
		{
			previousTime = presentTime;
			driver->beginScene(true, true, SColor(255, 255, 255, 255));

			//elapsedTime = device->getTimer()->getTime() - startTime;
			//startTime = device->getTimer()->getTime();
//
//			// Checking Game State.
			app.handleGameState(gameState, player, device, smgr, driver);
//
//			// Function to handle user input.
			app.processInput(device, smgr, driver, selector, reciever, player, camera, deltaTime);
//
//			// Update Player's Mana.
//			/*if ((device->getTimer()->getTime() - app.getLastUpdate()) > 1000.0f)
//			{
//				player->incrementMana();
//				app.setLastUpdate(device->getTimer()->getTime());
//			}*/
//
//			// Updating position of all GameObjects.
			app.updateGameObjects(deltaTime);
//
//			// Handle collisions between faerie and powerballs.
			app.handleCollisions(player, camera, deltaTime);
//
			//driver->draw2DImage(driver->getTexture("Textures/crosshair.png"), core::position2d<s32>(300, 200));

			//driver->draw2DImage(driver->getTexture("Textures/health.png"), core::position2d<s32>(15, 510));

			

			if (gameState != MAIN_MENU && gameState != GAME_COMPLETE && gameState != GAME_OVER)
			{
				if (reciever->getMouse() == EMIE_LMOUSE_PRESSED_DOWN)
					playerShoot = true;
				else
					playerShoot = false;


				//CHealthPowerupObject pi(player, smgr, { 0,0,0 });

				//update player
				//if (player)
				//{
				//	/*vector3df playerpos = player->getAbsolutePosition();
				//	printf("Pos: %f %f %f \n", playerpos.X, playerpos.Y, playerpos.Z);
				//	*/
				//	//if (crosshairEl->isVisible() && playerShoot) {
				//	if (playerShoot) {
				//		//player->lastAttack = device->getTimer()->getTime();
				//		player->fire(player->getWeapon(), device);
				//	}

				//	if (player->update(elapsedTime, player->getWeapon(), device))
				//	{
				//		delete player;
				//		player = NULL;
				//	}
				//}




				// draw fire & dragons background world
				//driver->draw2DImage(driver->getTexture("Textures/crosshair.png"), core::position2d<s32>(300, 200));

				//driver->enableMaterial2D();
				//driver->draw2DImage(driver->getTexture("Textures/health.png"), core::position2d<s32>(15, 510));
					//core::rect<s32>(0, 0, 342, 224), 0,
					//video::SColor(255, 255, 255, 255));

				
				//driver->enableMaterial2D(false);
				/*device->getGUIEnvironment()->addImage(
					driver->getTexture("Textures/crosshair.png"),
					core::position2d<s32>(300, 200));
				device->getGUIEnvironment()->addImage(
					driver->getTexture("Textures/health.png"),
					core::position2d<s32>(15, 510));*/

				//device->getGUIEnvironment()->drawAll();
				// Render everything.
				//guienv->drawAll();
				smgr->drawAll();

				// Update Game Hud.
				gameHud->displayHealthBar(player->getHealth());
				//gameHud->displayManaBar(player->getMana());
				//driver->draw2DRectangle(video::SColor(100, 255, 255, 255),
				//	core::rect<s32>(300, 300, 300, 300));

				//device->getGUIEnvironment()->
				guienv->drawAll();

			}
			else
			{
				// Display the GUI.
				

				guienv->drawAll();
			}

			driver->endScene();

#ifdef DEBUG
			now = device->getTimer()->getTime();
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
	}

	return 0;
}