#include "GameHud.h"

GameHud::GameHud(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver)
{
	device = irrDevice;
	smgr = manager;
	driver = videoDriver;
	guienv = device->getGUIEnvironment();
}


void GameHud::displayHealthBar(u8 health)
{
	if (health < 0)
	{
		return;
	}

	//device->getGUIEnvironment()->addImage(driver->getTexture("Textures/crosshair.png"), core::position2d<s32>(512 - 100, 364 - 82));
	device->getGUIEnvironment()->addImage(driver->getTexture("Textures/health.png"),core::position2d<s32>(15, 510));

	/*device->getGUIEnvironment()->addImage(
		driver->getTexture("Textures/1.jpg"),
		core::position2d<s32>(15, 10))->setScaleImage(20);*/

	driver->draw2DRectangle(rect<s32>(30, 400 - (3 * health), 40, 400), SColor(255, 255, 0, 0), SColor(255, 255, 0, 0), SColor(255, 255, 0, 0), SColor(255, 255, 0, 0));
}