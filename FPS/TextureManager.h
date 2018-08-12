#pragma once

#include "Global.h"

#define TEXTURE_PATH			"Textures/"

#define ENEMY01_BADFAERIE		"faerie.bmp"

#define WEAPON01_REVOLVER		"1.jpg"
#define WEAPON02_REVEVO			"2.jpg"
#define WEAPON03_MGUN			"3.jpg"
#define WEAPON04_MGUNB			"4.jpg"
#define WEAPON05_SMG			"5.jpg"
#define WEAPON06_LASER			"6.jpg"

#define BUTTON_START_NAME		"Start1.png"
#define BUTTON_OPTIONS_NAME		"Start1.png"
#define BUTTON_BACK_NAME		"Start1.png"
#define BUTTON_QUIT_NAME		"Start1.png"

#define AMMO_TEXTURE	    	"ammo.png"
#define MAG_TEXTURE		        "mag.png"

#define ENEMY_TEXTURES_COUNT	5
#define BUTTON_TEXTURES_COUNT	4
#define WEAPONS_TEXTURES_COUNT	6

/**
* Represents texture processing
*/
class TextureManager
{
public:

	TextureManager();

	ITexture **getEnemyTexture() const;
	ITexture **getButtonsTexture() const;
	ITexture **getWeaponsTexture() const;
	ITexture **getAmmoTexture() const;
	ITexture **getMagTexture() const;

	void setEnemyTexture(ITexture **texture);
	void setButtonsTexture(ITexture **texture);
	void setWeaponsTexture(ITexture **texture);
	void setAmmoTexture(ITexture **texture);
	void setMagTexture(ITexture **texture);

	void loadTextures(IVideoDriver *video);

	void drop();

private:

	ITexture **enemyTex;
	ITexture **buttonsTex;
	ITexture **weaponsTex;

	ITexture **ammoTex;
	ITexture **magTex;
};