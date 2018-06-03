#include <irrlicht.h>

#include "Global.h"

using namespace irr;
using namespace core;
using namespace gui;

//enum GameState
//{
//	MAIN_MENU,
//	WAVE_1,
//	GAME_COMPLETE,
//	GAME_OVER
//};

//struct SAppContext
//{
//	IrrlichtDevice* device;
//	GameState * gameStatePtr;
//
//	SAppContext(IrrlichtDevice* irrDevice, GameState * gameState)
//	{
//		device = irrDevice;
//		gameStatePtr = gameState;
//	}
//};

enum GameState
{
	MENU,
	OPTIONS,
	INGAME,
	PAUSE,
	OVER,
	EXIT,
	//WAVE_1,
	GAME_COMPLETE,
	GAME_OVER
};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_PLAY_BUTTON,
	GUI_ID_CONTROLS_BUTTON,
	GUI_ID_INSTRUCTIONS_BUTTON,
	GUI_ID_INSTRUCTIONS_BACK_BUTTON,
	GUI_ID_CONTROLS_BACK_BUTTON
};

#pragma once
class EventReciever : public IEventReceiver {
public:
	EventReciever();
	//EventReciever(SAppContext & Context);
	//virtual bool OnEvent(const SEvent& event);
	virtual bool isKeyDown(EKEY_CODE keyCode) const;
	virtual bool isKeyUp(EKEY_CODE keyCode) const;
	char getMouse();
	char m_cMouse;

	///--------------------
	bool		keys[KEY_KEY_CODES_COUNT];
	position2di	mousePosition;
	bool		leftButtonPressed;
	bool		mouseMove;

//private:
	bool keyDown[KEY_KEY_CODES_COUNT];
	//SAppContext &context;

	///---------------------
	bool		OnEvent(const SEvent &event);
//	bool		isKeyDown(EKEY_CODE key) const;
	position2di	getMousePosition() const;
	bool		isLeftButtonPressed() const;
	bool        isMouseMoveActive() const;
	void		setMousePosition(vector3df position);
	void		zeroMouse();
	void        zeroMouseMove();
};