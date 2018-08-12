#pragma once

#include <irrlicht.h>
#include "IrrKlang.h"
#include "Enemy.h"
#include "PowerBallProjectile.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class PowerBallProjectile;

/*!
* Represents BadFaerie object as type of enemies.
*/
class BadFaerie : public Enemy
{
public:
	/*!
	Initializes BadFaerie enemy object.
	@param dodgeStart BadFaerie start dodge after plaet shoot.
	@param lastAttack BadFaerie last attack time.
	@param actionPhaseUpdateList List with Game Objects.

	Initializes Enemies c-tor 
	@param position BadFaerie pos.
	@param newSpeed BadFaerie speed.
	@param manager Irrlicht manager.
	@param playerTarget Player object.
	*/
	BadFaerie(vector3df position, f32 newSpeed, ISceneManager* manager, Player* target, IrrlichtDevice* irrDevice, list<GameObject*> *updateListPtr, IVideoDriver* videoDriver, ISoundEngine* sound);

	/**
	* Loads BadFaerie model.
	*/
	virtual void loadModel(IAnimatedMesh* mesh, ITexture* texture);

	/**
	* Updates method handling next things: 
	* faceplayer rotation,
	* Enemy is too far away,
	* Enemy is behind the player,
	* Push the enemy,
	* currentState.
	*/
	virtual void update(f32 deltaTime);

	
	/**
	* Checks, if BadFaerie see player's ammo
	*/
	bool seesPowerBall();

	/**
	* Checks, if actionPhaseUpdateList has player's ammo
	*/
	//bool listHasPowerBall();

	/**
	* Shots in the player.
	*/
	virtual void attack();

	/**
	* The enemy dodges the player's ammo, after player shoot.
	*/
	virtual void dodge(f32 deltaTime);

	/**
	* Moves of enemies.
	*/
	virtual void run(f32 deltaTime);

private:
	f32 dodgeStart;
	f32 lastAttack;
	IVideoDriver* driver;
	list<GameObject*> *updateList;
	ISoundEngine* _sound;
};

