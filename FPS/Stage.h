#pragma once

#include "GameHandle.h"
#include "IrrLicht.h"
#include "Irrklang.h"
#include "Player.h"
#include "Timer.h"
#include "Gui.h"
#include "TextureManager.h"
#include <time.h>

/**
* Represents stage - high level building block for the game.
*/

class Stage
{
public:

	/*!
	* Initializes game data: gui, texManager, engine, gameState,
	*                        sound, soundPlay, terrain.
	*/
	Stage();

	/**
	* Handling of the main game process.
	*/
	void loop();

	/**
	* Handling of the menu.
	*/
	void menu();

	/**
	* Handling of the game action phase.
	*/
	void actionPhase();

	/**
	* Sets Game pause.
	*/
	void setPause(bool pause);

	/**
	* Processing GAME_COMPLETE || GAME_OVER states.
	*/
	void processingResultScreen();

	void initGameData();
	void hideCursor();
	void menuClickSound();

	vector3df getGravity(const c8 * surface);

	void drop();
	
private:

	GameState gameState;

	Irrlicht *engine;
	ISoundEngine *sound;
	GUI *gui;
	ISound *gameMusic;
	TextureManager	*texManager;
	Time timer;

	EventReciever* reciever;
	ITriangleSelector* selector;
	bool soundPlay;

	/**
	* Level data.
	*/
	GameHandle gameHandler;
	Terrain* terrain;
	Camera* camera;
	Player* player;
	Skybox* skybox;

	rectf enemyField;
};
