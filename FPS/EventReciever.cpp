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
				//m_pGameState->MouseEvent(this);
			}

	if (event.EventType == EET_KEY_INPUT_EVENT)
		keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
	else
	{
		/*switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			leftButtonPressed = true;
			break;

		case EMIE_LMOUSE_LEFT_UP:
			leftButtonPressed = false;
			break;

		case EMIE_MOUSE_MOVED:
			mousePosition.X = event.MouseInput.X;
			mousePosition.Y = event.MouseInput.Y;
			break;

		default:

			break;
		}*/

	}

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

//-----------------------------------------------------------------------------
//EventReciever::EventReciever(SAppContext & Context) : context(Context) {
//	for(int i = 0; i < KEY_KEY_CODES_COUNT; ++i)
//		keyDown[i] = false;
//}
//
//bool EventReciever::isKeyDown(EKEY_CODE keyCode) const
//{
//	return keyDown[keyCode];
//}

bool EventReciever::isKeyUp(EKEY_CODE key) const
{
	//return !keyDown[keyCode];
	return !keys[key];
}

//! Returns mouse event
char EventReciever::getMouse()
{
	return m_cMouse;
}
//
//bool EventReciever::OnEvent(const SEvent& event)
//{
//
//	if (event.EventType == EET_MOUSE_INPUT_EVENT)
//	{
//		// Pass input down to the specific game state mouse handler
//		m_cMouse = event.MouseInput.Event;
//		//m_pGameState->MouseEvent(this);
//	}
//	
//
//	switch (event.EventType) {
//
//		case EET_KEY_INPUT_EVENT:
//		{
//			keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
//			break;
//		}
//		
//		case EET_GUI_EVENT:
//		{
//			s32 id = event.GUIEvent.Caller->getID();
//			IGUIEnvironment* env = context.device->getGUIEnvironment();
//
//			switch (event.GUIEvent.EventType) {
//			case EGET_BUTTON_CLICKED: {
//				switch (id) {
//				case GUI_ID_PLAY_BUTTON:
//					// disable mouse cursor
//					context.device->getCursorControl()->setVisible(false);
//
//					env->clear();
//					*(context.gameStatePtr) = WAVE_1;
//					break;
//
//				case GUI_ID_INSTRUCTIONS_BUTTON:
//					env->clear();
//					env->addImage(context.device->getVideoDriver()->getTexture("Textures/Instructions.bmp"), vector2d<s32>(0, 0), false);
//					env->addButton(rect<s32>(270, 380, 370, 420), NULL, GUI_ID_INSTRUCTIONS_BACK_BUTTON, L"Back");
//					break;
//				}
//
//			case GUI_ID_INSTRUCTIONS_BACK_BUTTON:
//				env->clear();
//				env->addImage(context.device->getVideoDriver()->getTexture("Textures/Menu.bmp"), vector2d<s32>(0, 0), false);
//				env->addButton(rect<s32>(210, 100, 450, 170), NULL, GUI_ID_PLAY_BUTTON, L"Play");
//				env->addButton(rect<s32>(210, 200, 450, 270), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"Instructions");
//				env->addButton(rect<s32>(210, 300, 450, 370), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
//				env->addButton(rect<s32>(210, 400, 450, 470), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
//				break;
//
//			case GUI_ID_CONTROLS_BUTTON:
//				env->clear();
//				env->addImage(context.device->getVideoDriver()->getTexture("Textures/Controls.bmp"), vector2d<s32>(0, 0), false);
//				env->addButton(rect<s32>(270, 380, 370, 420), NULL, GUI_ID_CONTROLS_BACK_BUTTON, L"Back");
//				break;
//
//			case GUI_ID_CONTROLS_BACK_BUTTON:
//				env->clear();
//				env->addImage(context.device->getVideoDriver()->getTexture("Textures/Menu.bmp"), vector2d<s32>(0, 0), false);
//				env->addButton(rect<s32>(210, 100, 450, 170), NULL, GUI_ID_PLAY_BUTTON, L"Play");
//				env->addButton(rect<s32>(210, 200, 450, 270), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"Instructions");
//				env->addButton(rect<s32>(210, 300, 450, 370), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
//				env->addButton(rect<s32>(210, 400, 450, 470), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
//				break;
//
//			case GUI_ID_QUIT_BUTTON:
//				env->clear();
//				context.device->closeDevice();
//				break;
//
//			}
//		  }
//		}
//		default:
//			break;
//	}
//	return false;
//}