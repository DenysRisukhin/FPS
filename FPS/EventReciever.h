#include <irrlicht.h>

#include "Global.h"

using namespace irr;
using namespace core;
using namespace gui;

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
	virtual bool isKeyDown(EKEY_CODE keyCode) const;
	virtual bool isKeyUp(EKEY_CODE keyCode) const;
	char getMouse();
	char m_cMouse;

	///--------------------
	bool		keys[KEY_KEY_CODES_COUNT];
	position2di	mousePosition;
	bool		leftButtonPressed;
	bool		mouseMove;

	bool keyDown[KEY_KEY_CODES_COUNT];

	///---------------------
	bool		OnEvent(const SEvent &event);
	position2di	getMousePosition() const;
	bool		isLeftButtonPressed() const;
	bool        isMouseMoveActive() const;
	void		setMousePosition(vector3df position);
	void		zeroMouse();
	void        zeroMouseMove();
};