#pragma once

#include "Global.h"
#include "EventReciever.h"

#define WINDOW_COLOR_DEPTH		32
#define WINDOW_BACKGROUND_COLOR	{0, 0, 0, 0}

/*!
*Represents Irrlicht's basic data: device, video, manager, gui, event reciever, etc.
*/
class Irrlicht {

public:
	
	/*!
	Initializes window using provided info.
	@param name Window name.
	@param size Window size.
	*/
	Irrlicht(wchar_t *name, dimension2du size);
	Irrlicht();

	void setTime(u32 newTime);
	void setCursorPosition(const dimension2du position);
	void setCursorToCenter();
	void hideCursor(const bool flag);

	vector2di getCursorPosition() const;
	IrrlichtDevice *getDevice() const;
	ISceneManager *getManager() const;
	IGUIEnvironment	*getGUI() const;
	IVideoDriver *getVideo() const;
	ISceneNode *getSkyBox(path fileName) const;
	dimension2du getCenter() const;
	u32	getCurrentTime() const;

	bool isKeyPressed(EKEY_CODE key) const;

	void resetInput();
	void resetMouseMove();
	bool isMouseActive();

	bool run();

	void drawAll();

	bool drop();

private:

	EventReciever *reciever;
	IrrlichtDevice *device;
	IVideoDriver *video;
	ISceneManager *manager;
	IGUIEnvironment *gui;

	dimension2du windowSize;
};
#pragma once
