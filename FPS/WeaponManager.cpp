#include "WeaponManager.h"

const s32 WeaponManager::MAX_AMMO = 50;

WeaponManager::WeaponManager(ISceneManager* smgr, s32 weaponType) {
	
	ammo = MAX_AMMO;
	ammoRev = MAX_AMMO - 44;
	ammoRevevo = MAX_AMMO - 40;
	ammoSmg = MAX_AMMO - 35;
	ammoMgun = MAX_AMMO - 25;
	ammoMgunb = ammoMgun;
	magRev = magRevevo = 2;
	magSmg = magMgun = magRevevo;
	magMgunb = magSmg;
}


