#include "EventReciever.h"

EventReciever::EventReciever(SAppContext & Context) : context(Context) {
	for(int i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		keyDown[i] = false;
}

bool EventReciever::isKeyDown(EKEY_CODE keyCode) const
{
	return keyDown[keyCode];
}

bool EventReciever::isKeyUp(EKEY_CODE keyCode) const
{
	return !keyDown[keyCode];
}

//! Returns mouse event
char EventReciever::getMouse()
{
	return m_cMouse;
}

bool EventReciever::OnEvent(const SEvent& event)
{

	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		// Pass input down to the specific game state mouse handler
		m_cMouse = event.MouseInput.Event;
		//m_pGameState->MouseEvent(this);
	}
	

	switch (event.EventType) {

		case EET_KEY_INPUT_EVENT:
		{
			keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			break;
		}
		
		case EET_GUI_EVENT:
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = context.device->getGUIEnvironment();

			switch (event.GUIEvent.EventType) {
			case EGET_BUTTON_CLICKED: {
				switch (id) {
				case GUI_ID_PLAY_BUTTON:
					// disable mouse cursor
					context.device->getCursorControl()->setVisible(false);

					env->clear();
					*(context.gameStatePtr) = WAVE_1;
					break;

				case GUI_ID_INSTRUCTIONS_BUTTON:
					env->clear();
					env->addImage(context.device->getVideoDriver()->getTexture("Textures/Instructions.bmp"), vector2d<s32>(0, 0), false);
					env->addButton(rect<s32>(270, 380, 370, 420), NULL, GUI_ID_INSTRUCTIONS_BACK_BUTTON, L"Back");
					break;
				}

			case GUI_ID_INSTRUCTIONS_BACK_BUTTON:
				env->clear();
				env->addImage(context.device->getVideoDriver()->getTexture("Textures/Menu.bmp"), vector2d<s32>(0, 0), false);
				env->addButton(rect<s32>(210, 100, 450, 170), NULL, GUI_ID_PLAY_BUTTON, L"Play");
				env->addButton(rect<s32>(210, 200, 450, 270), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"Instructions");
				env->addButton(rect<s32>(210, 300, 450, 370), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
				env->addButton(rect<s32>(210, 400, 450, 470), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
				break;

			case GUI_ID_CONTROLS_BUTTON:
				env->clear();
				env->addImage(context.device->getVideoDriver()->getTexture("Textures/Controls.bmp"), vector2d<s32>(0, 0), false);
				env->addButton(rect<s32>(270, 380, 370, 420), NULL, GUI_ID_CONTROLS_BACK_BUTTON, L"Back");
				break;

			case GUI_ID_CONTROLS_BACK_BUTTON:
				env->clear();
				env->addImage(context.device->getVideoDriver()->getTexture("Textures/Menu.bmp"), vector2d<s32>(0, 0), false);
				env->addButton(rect<s32>(210, 100, 450, 170), NULL, GUI_ID_PLAY_BUTTON, L"Play");
				env->addButton(rect<s32>(210, 200, 450, 270), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"Instructions");
				env->addButton(rect<s32>(210, 300, 450, 370), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
				env->addButton(rect<s32>(210, 400, 450, 470), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
				break;

			case GUI_ID_QUIT_BUTTON:
				env->clear();
				context.device->closeDevice();
				break;

			}
		  }
		}
		default:
			break;
	}
	return false;
}