#include "TextureManager.h"

TextureManager::TextureManager() : enemyTex(NULL), buttonsTex(NULL)
{
}

ITexture **TextureManager::getAmmoTexture() const {
	return ammoTex;
}

ITexture **TextureManager::getMagTexture() const {
	return magTex;
}

ITexture **TextureManager::getEnemyTexture() const{
	return enemyTex;
}

ITexture **TextureManager::getWeaponsTexture() const {
	return weaponsTex;
}

ITexture **TextureManager::getButtonsTexture() const{
	return buttonsTex;
}

void TextureManager::setAmmoTexture(ITexture **texture) {
	ammoTex = texture;
}

void TextureManager::setMagTexture(ITexture **texture) {
	magTex = texture;
}

void TextureManager::setWeaponsTexture(ITexture **texture) {
	weaponsTex = texture;
}

void TextureManager::setEnemyTexture(ITexture **texture){
	enemyTex = texture;
}

void TextureManager::setButtonsTexture(ITexture **texture){
	buttonsTex = texture;
}

void TextureManager::loadTextures(IVideoDriver *video){
	path name = TEXTURE_PATH;
	
	enemyTex = new ITexture *[ENEMY_TEXTURES_COUNT];
	enemyTex[0] = video->getTexture(name + ENEMY01_BADFAERIE);

	buttonsTex = new ITexture *[BUTTON_TEXTURES_COUNT];
	buttonsTex[0] = video->getTexture(name + BUTTON_START_NAME);
	buttonsTex[1] = video->getTexture(name + BUTTON_OPTIONS_NAME);
	buttonsTex[2] = video->getTexture(name + BUTTON_BACK_NAME);
	buttonsTex[3] = video->getTexture(name + BUTTON_QUIT_NAME);

	weaponsTex = new ITexture *[WEAPONS_TEXTURES_COUNT];
	weaponsTex[0] = video->getTexture(name + WEAPON01_REVOLVER);
	weaponsTex[1] = video->getTexture(name + WEAPON02_REVEVO);
	weaponsTex[2] = video->getTexture(name + WEAPON03_MGUN);
	weaponsTex[3] = video->getTexture(name + WEAPON04_MGUNB);
	weaponsTex[4] = video->getTexture(name + WEAPON05_SMG);
	weaponsTex[5] = video->getTexture(name + WEAPON06_LASER);

	ammoTex = new ITexture *;
	ammoTex[0] = video->getTexture(name + AMMO_TEXTURE);

	magTex = new ITexture *;
	magTex[0] = video->getTexture(name + MAG_TEXTURE);
}

void TextureManager::drop(){
	
	if (enemyTex)
	{
		for (u32 i = 0; i < ENEMY_TEXTURES_COUNT; i++)
		{
			if (enemyTex[i])
				enemyTex[i] = NULL;
		}
		delete enemyTex;
	}

	if (buttonsTex)
	{
		for (u32 i = 0; i < BUTTON_TEXTURES_COUNT; i++)
		{
			if (buttonsTex[i])
				buttonsTex[i] = NULL;
		}
		delete buttonsTex;
	}

	if (weaponsTex)
	{
		for (u32 i = 0; i < WEAPONS_TEXTURES_COUNT; i++)
		{
			if (weaponsTex[i])
				weaponsTex[i] = NULL;
		}
		delete weaponsTex;
	}

	if (ammoTex)
	{
		ammoTex[0] = NULL;
		delete ammoTex;
	}

	if (magTex)
	{
		magTex[0] = NULL;
		delete magTex;
	}
}