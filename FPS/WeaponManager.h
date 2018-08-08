#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents the weapons, magazine, ammo.
*/
class WeaponManager {

public:

	static const s32 MAX_AMMO;
	static const s32 MAX_HEALTH;

	/*!
	**Constructor
	@param weaponType Type of character.
	*/
	WeaponManager(ISceneManager* smgr, s32 weaponType);
	
	/**
	* Destructor
	*/
	virtual ~WeaponManager();
	
	/**
	* Returns the character's ammo
	* return a s32
	*/
	inline s32 getAmmo() { return ammo; }

	inline s32 getAmmoRev() { return ammoRev; }

	inline s32 getAmmoRevEvo() { return ammoRevevo; }

	inline s32 getAmmoSMG() { return ammoSmg; }

	inline s32 getAmmoMgun() { return ammoMgun; }

	inline s32 getAmmoMgunB() { return ammoMgunb; }

	/**
	* Return magazines.
	*/
	inline s32 getMagRev() { return magRev; }

	inline s32 getMagRevEvo() { return magRevevo; }

	inline s32 getMagSMG() { return magSmg; }

	inline s32 getMagMgun() { return magMgun; }

	inline s32 getMagMgunB() { return magMgunb; }

	inline void addAmmoRev(s32 amount) {
		ammoRev += amount;
		if (magRev < 2)	++magRev;
		if (ammoRev > 6) ammoRev = 6;
		if (ammoRev < 0) ammoRev = 0;
	}

	inline void addAmmoRevEvo(s32 amount) {
		ammoRevevo += amount;
		if (magRevevo < 2)	++magRevevo;
		if (ammoRevevo > 10) ammoRevevo = 10;
		if (ammoRevevo < 0) ammoRevevo = 0;
	}

	inline void addAmmoSMG(s32 amount) {
		ammoSmg += amount;
		if (magSmg < 2)	++magSmg;
		if (ammoSmg > 15) ammoSmg = 15;
		if (ammoSmg < 0) ammoSmg = 0;
	}

	inline void addAmmoMgun(s32 amount) {
		ammoMgun += amount;
		if (magMgun < 2)	++magMgun;
		if (ammoMgun > 25) ammoMgun = 25;
		if (ammoMgun < 0) ammoMgun = 0;
	}

	inline void addAmmoMgunB(s32 amount) {
		ammoMgunb += amount;
		if (magMgunb < 2)	++magMgunb;
		if (ammoMgunb > 25) ammoMgunb = 25;
		if (ammoMgunb < 0) ammoMgunb = 0;
	}

protected:
	
	scene::ISceneManager* SceneManager;
	core::vector3df Pos;
	s32 health;
	s32 ammo;
	s32 ammoRev, magRev;
	s32 ammoRevevo, magRevevo;
	s32 ammoMgun, magMgun;
	s32 ammoMgunb, magMgunb;
	s32 ammoSmg, magSmg;
};
