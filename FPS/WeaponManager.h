#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*!
* Represents magazines and ammunition for weapons.
*/
class WeaponManager {

public:

	static const s32 MAX_AMMO;

	/*!
	**Constructor
	@param weaponType Type of character.
	*/
	WeaponManager(ISceneManager* smgr, s32 weaponType);
	
	/**
	* Destructor
	*/
	virtual ~WeaponManager() {}
	
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
	* Returns magazines.
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
	
	s32 ammo;
	s32 ammoRev, magRev;
	s32 ammoRevevo, magRevevo;
	s32 ammoMgun, magMgun;
	s32 ammoMgunb, magMgunb;
	s32 ammoSmg, magSmg;
};

//class Item {
//public:
//	Item(const std::string& name, int id) : name(name), itemID(id) { }
//	const string& getName(void) const { return this->name; }
//	int getID(void) const { return this->itemID; }
//private:
//	string name;
//	int itemID;
//};
//
//class Weapon : public Item {
//private:
//	int ammo;
//public:
//	Weapon(const std::string& name, int id, int ammo) : Item(name, id), ammo(ammo) { }
//	int getAmmo(void) const;
//	virtual int getAccuracy(void) const = 0;
//	virtual int getDamage(void) const = 0;
//	virtual int getMaxAmmo(void) const = 0;
//	virtual int getCurrentAmmo(void) const = 0;
//	virtual float getRange(void) const = 0;
//	//
//	virtual int getMaxMagazine(void) const = 0;
//	virtual int getCurrentMagazine(void) const = 0;
//	virtual string getWeaponModel(void) const = 0;
//	virtual string getWeaponTexture(void) const = 0;
//	virtual string getBulletTexture(void) const = 0;
//	virtual float getRotateY(void) const = 0;
//	virtual float getRotateX(void) const = 0;
//	virtual float getPosY(void) const = 0;
//	virtual float getScale(void) const = 0;
//	virtual void decriseAmmo() = 0;
//	virtual void decriseMagazine() = 0;
//	virtual void addMagazine() = 0;
//	virtual void setAmmo() = 0;
//};
//
//class M_16 : public Weapon {
//public:
//	M_16() : Weapon("M_16", 1, 30) { bullet = 30; magazine = 5; }
//	virtual int getAccuracy(void) const { return 30; } // точность
//	virtual int getDamage(void) const { return 15; }   // ущерб  
//	virtual int getMaxAmmo(void) const { return 30; }  // боеприсы
//	virtual int getCurrentAmmo(void) const { return bullet; }
//	virtual float getRange(void) const { return 30.0; }
//	virtual int getMaxMagazine(void) const { return 5; }
//	virtual int getCurrentMagazine(void) const { return magazine; }
//	virtual string getWeaponModel(void) const { return "m16.c3b"; }
//	virtual string getWeaponTexture(void) const { return "handgun_C.jpg"; }
//	virtual string getBulletTexture(void) const { return "Bullet.c3b"; }
//	virtual float getRotateY(void) const { return 90; }
//	virtual float getRotateX(void) const { return 0; }
//	virtual float getPosY(void) const { return 1.5; }
//	virtual float getScale(void) const { return 0.09; }
//	virtual void addMagazine() { magazine++; }
//	virtual void setAmmo() { bullet = 30; }
//	virtual void decriseAmmo() {
//		if (bullet >= 0)         bullet--;
//	}
//	void decriseMagazine() {
//		if (magazine >= 0)  magazine--;
//	}
//private:
//	int bullet;
//	int magazine;
//};
//
//class AK : public Weapon {
//public:
//	AK() : Weapon("AK", 1, 25) { bullet = 25; magazine = 6; }
//	virtual int getAccuracy(void) const { return 30; } // точность
//	virtual int getDamage(void) const { return 20; }   // ущерб
//	virtual int getMaxAmmo(void) const { return 25; }  // боеприсы
//	virtual int getCurrentAmmo(void) const { return bullet; }
//	virtual float getRange(void) const { return 30.0; }
//	virtual int getMaxMagazine(void) const { return 6; }
//	virtual int getCurrentMagazine(void) const { return magazine; }
//	virtual string getWeaponModel(void) const { return "AKM.c3b"; }
//	virtual string getWeaponTexture(void) const { return "handgun_C.jpg"; }
//	virtual string getBulletTexture(void) const { return "Bullet.c3b"; }
//	virtual float getRotateY(void) const { return 180; }
//	virtual float getRotateX(void) const { return -90; }
//	virtual float getPosY(void) const { return 1.5; }
//	virtual float getScale(void) const { return 0.09; }
//	virtual void addMagazine() { ++magazine; }
//	virtual void setAmmo() { bullet = 25; }
//	virtual void decriseAmmo() {
//		if (bullet >= 0) bullet--;
//		else  bullet = 0;
//	}
//	void decriseMagazine() {
//		if (magazine > 0)  magazine--;
//		else    magazine = 0;
//	}
//private:
//	int bullet, magazine;
//};
//
//#define ROCKET_GUN_NAME "rocketGun.c3b"
//#define ROCKET_GUN_SCALE 0.03
//#define ROCKET_GUN_ROTATE_X 100
//#define ROCKET_GUN_POS_Y 0.5
//class Bazooka : public Weapon {
//public:
//	Bazooka() : Weapon("Bazooka", 1, 10) { rocket = 10; }
//	virtual int getAccuracy(void) const { return 50; } // точность
//	virtual int getDamage(void) const { return 50; }   // ущерб
//	virtual int getMaxAmmo(void) const { return 10; }  // боеприсы
//	virtual float getRange(void) const { return 30.0; }
//	virtual int getCurrentAmmo(void) const { return rocket; }
//	virtual int getMaxMagazine(void) const { return 0; }
//	virtual int getCurrentMagazine(void) const { return 0; }
//	virtual string getWeaponModel(void) const { return "rocketGun.c3b"; }
//	virtual string getWeaponTexture(void) const { return "handgun_C.jpg"; }
//	virtual string getBulletTexture(void) const { return "rocket.c3b"; }
//	virtual float getRotateY(void) const { return 0; }
//	virtual float getRotateX(void) const { return 100; }
//	virtual float getPosY(void) const { return 0.5; }
//	virtual float getScale(void) const { return 0.05; }
//	virtual void addMagazine() {}
//	virtual void setAmmo() {     }
//	virtual void decriseAmmo() { rocket--; }
//	void decriseMagazine() {}
//private:
//	int rocket;
//};
//
//**	*	*	*	*	*	*	*	*	*	*	*	*
//In Action Phase, as first we should declare and init all weapons :
//AK* aka = new AK();
//Bazooka* bazuka = new Bazooka();
//M_16* m16 = new M_16();
//**	*	*	*	*	*	*	*	*	*	*	*	*
//_player->setWeapon(aka);
//Set weapon model & texture
//*	*	*	*	*	*	*	*	*	*	*	*	*	*
//void Test::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
//else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_1) {
//	Set weapon model & texture
//		currentGun = "Bullet.c3b";
//	_player->setWeapon(aka);
//}
//}
//**	*	*	*	*	*	*	*	*	*	*	*	*
//Identification of current weapon :
//if (_player->getWeapon()->getName() == "M_16")  pageView->setCurrentPageIndex(1);
//else if (_player->getWeapon()->getName() == "AK")  pageView->setCurrentPageIndex(0);
//else if (_player->getWeapon()->getName() == "Bazooka") pageView->setCurrentPageIndex(2);
//Get data for current weapon :
//_player->getWeapon()->getCurrentAmmo();
//_player->getWeapon()->getCurrentMagazine();
//
//class Player : public cocos2d::Sprite3D {
//	Player(void) : weapon(0) { }
//	void setWeapon(Weapon* weapon) { this->weapon = weapon; }
//	Weapon* getWeapon(void) const { return this->weapon; }
//	~Player(void) { delete this->weapon; }
//	Weapon* weapon;
//