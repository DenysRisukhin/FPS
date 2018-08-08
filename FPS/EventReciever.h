#include <irrlicht.h>
#include "Global.h"

using namespace irr;
using namespace core;
using namespace gui;

/*!
* Represents game states.
*/
enum GameState {
	MENU,
	OPTIONS,
	INGAME,
	PAUSE,
	OVER,
	EXIT,
	GAME_COMPLETE,
	GAME_OVER
};

/*!
* Represents numbers for buttons set(for menu).
*/
enum {
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_PLAY_BUTTON,
	GUI_ID_CONTROLS_BUTTON,
	GUI_ID_INSTRUCTIONS_BUTTON,
	GUI_ID_INSTRUCTIONS_BACK_BUTTON,
	GUI_ID_CONTROLS_BACK_BUTTON
};

#pragma once

/*!
* Represents mouse & keyboard events.
*/
class EventReciever : public IEventReceiver {
public:

	/*!
	* Initializes keys & leftButtonPressed data.
	*/
	EventReciever();

	/**
	* Returns true if current key is pressed.
	*/
	virtual bool isKeyDown(EKEY_CODE keyCode) const;

	/**
	* Returns false if current key is up.
	*/
	virtual bool isKeyUp(EKEY_CODE keyCode) const;

	/**
	* Returns mouse event.
	*/
	char getMouse();

	/**
	* Returns true if left mouse button is pressed.
	*/
	bool isLeftButtonPressed() const;

	/**
	* Returns true if the mouse is moved.
	*/
	bool isMouseMoveActive() const;
	
	/**
	* Handling mouse & keyboard events.
	*/
	bool OnEvent(const SEvent &event);

	void zeroMouse();
	void zeroMouseMove();

	void setMousePosition(vector3df position);
	position2di	getMousePosition() const;

private:

	bool keys[KEY_KEY_CODES_COUNT];
	char m_cMouse;
	bool leftButtonPressed;

	position2di	mousePosition;
	bool mouseMove;
};