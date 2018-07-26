#pragma once

#include "Game.h"

#include "IrrLicht.h"
#include "Irrklang.h"
#include "Player.h"
#include "Timer.h"
#include "Gui.h"
#include "TextureManager.h"
#include <time.h>


#define ENEMY_FIELD_SIZE	{ -250.f, 180.f, 250.f, -160.f }
#define PLAYER_LINE_SIZE	{ -200, 0.f, -500,  200, 0.f, 0 }


#define SCENE_SKYBOX_ROTATION	{ 0.f, 270.f, 0.f }
#define SCENE_SKYBOX_SCALE		{ 1.1f, 1.f, 0.75f }

class Stage
{
private:

	Irrlicht		*engine;
	ISoundEngine	*sound;


	GUI				*gui;
	ISound			*gameMusic;
	TextureManager	*texManager;

	rectf			enemyField;

	// 3D line between two points with intersection methods.
	line3df			playerLine;

	//State			state;
	Time			timer;

	bool			soundPlay;

	void toLevel(bool pause);

	void menu();
	void game();


	void drop();
	void menuClick();

public:

	bool bPressed;
	u32 lastPress;

	f32 deltaTime;
	f32 previousTime, presentTime;

	f32 previous;
	f32 now;

	s32 startTime, elapsedTime, endTime;

	Game app;
	Terrain* terrain;
	EventReciever* reciever;
	ITriangleSelector* selector;
	Camera* camera;
	Player* player;
	Skybox* skybox;
	Stage();
	void loop();

	GameState gameState;

	ISceneNode *skybox1;

	vector3df curCameraPos;
};
