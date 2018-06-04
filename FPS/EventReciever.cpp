#include "EventReciever.h"

EventReciever::EventReciever() : leftButtonPressed(false)
{
	for (bool &i : keys)
		i = false;

}

bool EventReciever::OnEvent(const SEvent &event)
{
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
			{
				// Pass input down to the specific game state mouse handler
				m_cMouse = event.MouseInput.Event;
			}

	if (event.EventType == EET_KEY_INPUT_EVENT)
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;


	return false;
}

bool EventReciever::isKeyDown(EKEY_CODE key) const
{
	return keys[key];
}

position2di EventReciever::getMousePosition() const
{
	return mousePosition;
}

bool EventReciever::isLeftButtonPressed() const
{
	return leftButtonPressed;
}

void EventReciever::setMousePosition(const vector3df position)
{
	mousePosition.Y = position.X;
	mousePosition.X = position.Z;
}

void EventReciever::zeroMouse()
{
	leftButtonPressed = false;
}

bool EventReciever::isMouseMoveActive() const {
	return mouseMove;
}

void EventReciever::zeroMouseMove()
{
	mouseMove = false;
}

bool EventReciever::isKeyUp(EKEY_CODE key) const
{
	return !keys[key];
}

//! Returns mouse event
char EventReciever::getMouse()
{
	return m_cMouse;
}
