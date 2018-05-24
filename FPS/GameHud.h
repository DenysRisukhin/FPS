#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace gui;

class GameHud {
public:
	GameHud(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver);
	void displayHealthBar(u8 health);
	//void displayManaBar(u8 mana);
private:
	IrrlichtDevice* device;
	ISceneManager* smgr;
	IVideoDriver* driver;
	IGUIEnvironment* guienv;

};
