#include "Gui.h"
#include <iostream>

#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <errno.h>

GUI::GUI() : buttons({}), health(NULL), musicBox(NULL), soundBox(NULL), life(NULL), logo(NULL), ammoLabel(NULL), magLabel(NULL), curWeapon(NULL), ammo(NULL), mag(NULL)
{
}

void GUI::setWeaponTexture(IGUIEnvironment *gui, IVideoDriver *drv, Player *player, TextureManager *&manager) {

	drop(true, true);

	if (player->getWeapon() != LASER) {
		ammo = gui->addImage(manager->getAmmoTexture()[0], core::position2d<int>(135, 70));

		mag = gui->addImage(manager->getMagTexture()[0], core::position2d<int>(125, 10));

		magLabel = gui->addStaticText(L"0", rect<int>(165, 50, 500, 70));
		magLabel->setOverrideColor(BLACK_COLOR);
		magLabel->enableOverrideColor(true);

		ammoLabel = gui->addStaticText(L"0", rect<int>(165, 90, 500, 500));
		ammoLabel->setOverrideColor(BLACK_COLOR);
		ammoLabel->enableOverrideColor(true);
	}
	
	switch ( player->getWeapon() ) {
	case REVOLVER:

		curWeapon = gui->addImage(manager->getWeaponsTexture()[0], core::position2d<int>(10, 10));

		setAmmoLabel(player->getAmmoRev());
		setMagLabel(player->getMagRev());

		break;
	case REVEVO:

		curWeapon = gui->addImage(manager->getWeaponsTexture()[1], core::position2d<int>(10, 10));

		setAmmoLabel(player->getAmmoRevEvo());
		setMagLabel(player->getMagRevEvo());

		break;
	case MGUN:
		curWeapon = gui->addImage(manager->getWeaponsTexture()[2], core::position2d<int>(10, 10));

		setAmmoLabel(player->getAmmoMgun());
		setMagLabel(player->getMagMgun());

		break;
	case MGUNB:
		curWeapon = gui->addImage(manager->getWeaponsTexture()[3], core::position2d<int>(10, 10));

		setAmmoLabel(player->getAmmoMgunB());
		setMagLabel(player->getMagMgunB());

		break;
	case SMG:
		curWeapon = gui->addImage(manager->getWeaponsTexture()[4], core::position2d<int>(10, 10));

		setAmmoLabel(player->getAmmoSMG());
		setMagLabel(player->getMagSMG());

		break;
	case LASER:
		curWeapon = gui->addImage(manager->getWeaponsTexture()[5], core::position2d<int>(10, 10));
		break;
	}
}

void GUI::addButton(IGUIEnvironment *gui, ITexture *&texture, path name, const recti size, u32 id){
	size_t length = strlen(name.c_str()) + 1;
	wchar_t *text = new wchar_t[length];
	
	mbstowcs(text, name.c_str(), length);
	IGUIButton *button = gui->addButton(size, NULL, id, text);
	button->setImage(texture);

	buttons.push_back(button);
}

void GUI::setAmmoLabel(const u32 newScore){
	std::wstring text = std::to_wstring(newScore);
	ammoLabel->setText(text.c_str());
}

void GUI::setMagLabel(const u32 newScore){
	std::wstring text = std::to_wstring(newScore);
	magLabel->setText(text.c_str());
}

void GUI::setHealthLabel(const s32 newHealth){
	std::wstring text = std::to_wstring(newHealth);
	health->setText(text.c_str());
}

bool GUI::isButtonPressed(u32 id) const{
	for (auto &i : buttons)
		if (i && i->getID() == id && i->isPressed())
			return true;

	return false;
}

s32 GUI::getMusicSelection() const{
	if (musicBox)
		return musicBox->getItemData(musicBox->getSelected());

	return UNKNOWN;
}

s32 GUI::getSoundSelection() const{
	if (soundBox)
		return soundBox->getItemData(soundBox->getSelected());
	return UNKNOWN;
}


void GUI::menu(IGUIEnvironment *gui, TextureManager *&manager, IVideoDriver *drv){
	if (buttons.size())
		drop();

	logo = gui->addImage(drv->getTexture("Textures/poster.jpg"), core::position2d<int>(-235, 0));

	addButton(gui, manager->getButtonsTexture()[0], "Start Game",{
		SINGLE_BUTTON_START_H,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, START_BUTTON);

	addButton(gui, manager->getButtonsTexture()[1], "Options",{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, OPTIONS_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 3 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, QUIT_BUTTON);
}

void GUI::options(IGUIEnvironment *gui, TextureManager *&manager){
	drop();

	musicBox = gui->addComboBox({
		WINDOW_WIDTH / 2 - COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 - COMBOBOX_HEIGHT * 2 - COMBOBOX_MARGIN,
		WINDOW_WIDTH / 2 + COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 - COMBOBOX_HEIGHT - COMBOBOX_MARGIN,
	});

	soundBox = gui->addComboBox({
		WINDOW_WIDTH / 2 - COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 - COMBOBOX_HEIGHT / 2,
		WINDOW_WIDTH / 2 + COMBOBOX_WIDTH / 2,
		WINDOW_HEIGHT / 2 + COMBOBOX_HEIGHT / 2 });

	musicBox->addItem(L"Enable music", MUSIC_ENABLE);
	musicBox->addItem(L"Disable Music", MUSIC_DISABLE);
	soundBox->addItem(L"Enable sound", SOUND_ENABLE);
	soundBox->addItem(L"Disable sound", SOUND_DISABLE);

	addButton(gui, manager->getButtonsTexture()[2], "Back",{
		TRIPLE_BUTTON_START_H,
		WINDOW_HEIGHT / 2 + COMBOBOX_HEIGHT / 2 + BUTTON_MARGIN,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_HEIGHT / 2 + COMBOBOX_HEIGHT / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, BACK_BUTTON);
}

void GUI::pause(IGUIEnvironment *gui, TextureManager *&manager){
	if (buttons.size())
		drop(true, true);

	std::cout << "buttons.size() = " << buttons.size() << std::endl;

	addButton(gui, manager->getButtonsTexture()[0], "Resume",{
		TRIPLE_BUTTON_START_H,
		TRIPLE_BUTTON_START_V,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT
	}, RESUME_BUTTON);

	addButton(gui, manager->getButtonsTexture()[2], "Back",{
		TRIPLE_BUTTON_START_H,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT + BUTTON_MARGIN,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT * 2 + BUTTON_MARGIN
	}, BACK_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",{
		TRIPLE_BUTTON_START_H,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT * 2 + BUTTON_MARGIN * 2,
		TRIPLE_BUTTON_START_H + BUTTON_WIDTH,
		TRIPLE_BUTTON_START_V + BUTTON_HEIGHT * 3 + BUTTON_MARGIN * 2
	}, QUIT_BUTTON);
}

void GUI::game(IGUIEnvironment *gui, TextureManager *&manager, IVideoDriver *drv){
	if (buttons.size())
		drop(false, false);

	crosshair = gui->addImage(drv->getTexture("Textures/crosshair.png"), core::position2d<s32>(512 - 100, 364 - 82));

	life = gui->addImage(drv->getTexture("Textures/health.png"), core::position2d<int>(200, 30));

	health = gui->addStaticText(L"100", rect<int>(220, 52.5, 500, 70) );
	health->setOverrideColor(WHITE_COLOR);
	health->enableOverrideColor(true);
}

void GUI::win(IGUIEnvironment *gui, TextureManager *&manager){
	drop(true);

	addButton(gui, manager->getButtonsTexture()[0], "Start Game",{
		SINGLE_BUTTON_START_H,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, START_BUTTON);

	addButton(gui, manager->getButtonsTexture()[2], "Back",{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, BACK_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 3 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, QUIT_BUTTON);
}

void GUI::lose(IGUIEnvironment *gui, TextureManager *&manager){
	drop(true);

	addButton(gui, manager->getButtonsTexture()[0], "Start Game",{
		SINGLE_BUTTON_START_H,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, START_BUTTON);

	addButton(gui, manager->getButtonsTexture()[2], "Back",{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, BACK_BUTTON);

	addButton(gui, manager->getButtonsTexture()[3], "Quit",{
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 2 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN,
		SINGLE_BUTTON_START_H + BUTTON_WIDTH * 3 + BUTTON_MARGIN * 2,
		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2 + BUTTON_MARGIN + BUTTON_HEIGHT
	}, QUIT_BUTTON);
}

void GUI::drop(bool fScore, bool fHealth){
	for (auto &i : buttons){
		if (i){
			i->remove();
			i = NULL;
		}
	}
	buttons.clear();

	if (health && !fHealth){
		health->remove();
		health = NULL;
	}

	if (life && !fHealth){
		life->remove();
		life = NULL;
	}

	if (crosshair && !fHealth){
		crosshair->remove();
		crosshair = NULL;
	}

	if (ammoLabel){
		ammoLabel->remove();
		ammoLabel = NULL;
	}

	if (magLabel){
		magLabel->remove();
		magLabel = NULL;
	}

	if (logo){
		logo->remove();
		logo = NULL;
	}

	if (curWeapon){
		curWeapon->remove();
		curWeapon = NULL;
	}

	if (musicBox){
		musicBox->remove();
		musicBox = NULL;
	}

	if (soundBox){
		soundBox->remove();
		soundBox = NULL;
	}
}