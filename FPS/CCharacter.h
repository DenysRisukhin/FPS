#pragma once

#include <irrlicht.h>
//#include <IrrAI.h>

//#include <irrKlang.h>
//using namespace irrklang;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

/*! Class to handle a game character */
class CCharacter {

public:

	/*! Struct describing the parameters of a CCharacter */
	struct SCharacterDesc {
		/**
		\brief Constructor
		*/
		SCharacterDesc() {
			SceneManager = NULL;
			//AIManager = NULL;
			StartWaypointID = 1;
			WaypointGroupName = "";
			WaypointGroupIdx = 0;
			NPCRange = 200;
			Name = L"";
			RegenerateHealth = false;
			RegenerateAmmo = false;
			halfHealth = false;
			isBrkObj = false;
			bossHealth = false;
		}
		scene::ISceneManager* SceneManager;
		//IrrAI::IAIManager* AIManager;
		s32 StartWaypointID;
		core::stringc WaypointGroupName;
		s32 WaypointGroupIdx;
		f32 NPCRange;
		core::stringw Name;
		bool RegenerateHealth;
		bool RegenerateAmmo;
		//start with health at 50
		bool halfHealth;
		bool isBrkObj;
		bool bossHealth;


	};

	static const s32 MAX_AMMO;
	static const s32 MAX_HEALTH;
	static const s32 REFILL_PERIOD;

	/**
	\brief Constructor
	\param desc - Description of the character to be created
	\param characterType - Type of character
	*/
	CCharacter(ISceneManager* smgr, s32 characterType);
	/**
	\brief Destructor
	*/
	virtual ~CCharacter();
	/**
	\brief Updates the character
	\param elapsedTime - Time since last update
	*/
	virtual bool update(s32 elapsedTime);
	/**
	\brief Informs the character that it has been hit by an enemy weapon
	*/
	inline virtual void registerHit(s32 val) { Health -= val; TimeSinceLastRefill = 0; }
	/**
	\brief Returns the character's IAIEntity
	\return an IAIEntity*
	*/
	//inline IAIEntity* getAIEntity() { return AIEntity; }
	/**
	\brief Returns the character's absolute position
	\return a vector3df
	*/
	inline core::vector3df getAbsolutePosition() { return {0, 0, 0}; }// AIEntity->getAbsolutePosition();

	/**
	\brief Returns the character's type
	\return a s32
	*/
	inline s32 getCharacterType() { return CharacterType; }
	/**
	\brief Returns the character's health
	\return a s32
	*/
	inline s32 getHealth() { return Health; }

	/**
	\brief Returns the character's ammo
	\return a s32
	*/
	inline s32 getAmmo() { return Ammo; }

	inline s32 getAmmoRev() { return ammo_rev; }

	inline s32 getAmmoRevEvo() { return ammo_revevo; }

	inline s32 getAmmoSMG() { return ammo_smg; }

	inline s32 getAmmoMgun() { return ammo_mgun; }

	inline s32 getAmmoMgunB() { return ammo_mgunb; }

	//return magazines************************************
	inline s32 getMagRev() { return mag_rev; }

	inline s32 getMagRevEvo() { return mag_revevo; }

	inline s32 getMagSMG() { return mag_smg; }

	inline s32 getMagMgun() { return mag_mgun; }

	inline s32 getMagMgunB() { return mag_mgunb; }

	inline void addAmmoRev(s32 amount) {
		ammo_rev += amount;
		if (mag_rev < 2)	++mag_rev;
		if (ammo_rev > 6) ammo_rev = 6;
		if (ammo_rev < 0) ammo_rev = 0;
	}

	inline void addAmmoRevEvo(s32 amount) {
		ammo_revevo += amount;
		if (mag_revevo < 2)	++mag_revevo;
		if (ammo_revevo > 10) ammo_revevo = 10;
		if (ammo_revevo < 0) ammo_revevo = 0;
	}

	inline void addAmmoSMG(s32 amount) {
		ammo_smg += amount;
		if (mag_smg < 2)	++mag_smg;
		if (ammo_smg > 15) ammo_smg = 15;
		if (ammo_smg < 0) ammo_smg = 0;
	}

	inline void addAmmoMgun(s32 amount) {
		ammo_mgun += amount;
		if (mag_mgun < 2)	++mag_mgun;
		if (ammo_mgun > 25) ammo_mgun = 25;
		if (ammo_mgun < 0) ammo_mgun = 0;
	}

	inline void addAmmoMgunB(s32 amount) {
		ammo_mgunb += amount;
		if (mag_mgunb < 2)	++mag_mgunb;
		if (ammo_mgunb > 25) ammo_mgunb = 25;
		if (ammo_mgunb < 0) ammo_mgunb = 0;
	}

	inline void addHealth(s32 amount) {
		Health += amount;
		if (Health > 100) Health = 100;
		if (Health < 0) Health = 0;
	}

	//virtual void drop();

protected:
	//IAIEntity* AIEntity;
	//IAIManager* AIManager;
	scene::ISceneManager* SceneManager;
	core::vector3df Pos;
	s32 Health;
	s32 Ammo;
	s32 ammo_rev, mag_rev;
	s32 ammo_revevo, mag_revevo;
	s32 ammo_mgun, mag_mgun;
	s32 ammo_mgunb, mag_mgunb;
	s32 ammo_smg, mag_smg;
	s32 TimeSinceLastRefill;
	s32 CharacterType;
	bool RegenerateHealth;
	bool RegenerateAmmo;
	//start with health at 50
	bool HalfHealth;
	bool IsBrkObj;
	bool BossHealth;

	/**
	\brief Makes the character play a death animation
	*/
	virtual void die();
	virtual void dieWall();
	//sound
//	ISoundEngine* engine;

};
