#include "EventReciever.h"

EventReciever::EventReciever() : leftButtonPressed(false)
{
	for (bool &i : keys)
		i = false;
}

bool EventReciever::OnEvent(const SEvent &event){

	// Mouse events.
	if (event.EventType == EET_MOUSE_INPUT_EVENT){
		switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			leftButtonPressed = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			leftButtonPressed = false;
			break;

		case EMIE_MOUSE_MOVED:
			//mouseMove = true;
			//MouseState.Position.X = event.MouseInput.X;
			//MouseState.Position.Y = event.MouseInput.Y;
			break;

		default:
			// We won't use the wheel
			break;
		}
		// Pass input down to the specific game state mouse handler
		m_cMouse = event.MouseInput.Event;

	}

	// Keyboard events.
	if (event.EventType == EET_KEY_INPUT_EVENT)
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool EventReciever::isKeyDown(EKEY_CODE key) const{
	return keys[key];
}

bool EventReciever::isKeyUp(EKEY_CODE key) const{
	return !keys[key];
}

char EventReciever::getMouse(){
	return m_cMouse;
}

position2di EventReciever::getMousePosition() const{
	return mousePosition;
}

bool EventReciever::isLeftButtonPressed() const{
	return leftButtonPressed;
}

void EventReciever::setMousePosition(const vector3df position){
	mousePosition.Y = position.X;
	mousePosition.X = position.Z;
}

void EventReciever::zeroMouse(){
	leftButtonPressed = false;
}

bool EventReciever::isMouseMoveActive() const {
	return mouseMove;
}

void EventReciever::zeroMouseMove(){
	mouseMove = false;
}


