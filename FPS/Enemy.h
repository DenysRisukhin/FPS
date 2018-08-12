#pragma once
#include "GameObject.h"
#include "Player.h"

/*!
* Represents the states of behavior of enemies.
*/
enum EnemyState
{
	ENEMY_RUN,
	ENEMY_ATTACK,
	ENEMY_DODGE, 
	ENEMY_IDLE
};

/*!
* Represents the types of damage.
*/

enum AttackRating
{
	POWER_BALL = 1,
	MONSTER_ATTACK
};

/*!
* Represents (abstract class) interface for enemies objects. 
*/
class Enemy : public GameObject
{
public:

	/*!
	Initializes game object data.
	@param target Player object
	@param currentState Enemiesy object behaviour state.
	@param node Enemy object.
	@param facingDirection.
	@param bPushedBack.
	@param pushStart.
	*/
	Enemy(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* enemyTarget);

	/**
	* Rotates enemies to player face.
	*/
	virtual void facePlayer();

	/**
	* Enemies must rotate face to face with the player. 
	* Sets @param bPushedBack = true;
	* Sets @param pushStart = device->getTimer()->getTime();
	*/
	virtual void pushBack();

	/**
	* Returns NULL.
	*/
	ISceneNode* getNode();

	/**
	* Returns current pos.
	*/
	virtual vector3df getPosition();

	//-------------------------------------------------------------------------------------

	/**
	* Interface for inharitance. Empty method.
	*/
	virtual void update(f32 deltaTime);

	/**
	* Interface for inharitance. Empty method.
	*/
	virtual void loadModel(IAnimatedMesh* mesh, ITexture* texture);

	virtual void attack() = 0;
	virtual void dodge(f32 deltaTime) = 0;
	virtual void run(f32 deltaTime) = 0;

protected:

	/**
	* Computes angle value for correct rotating enemies to player face.
	*/
	vector3df getTargetAngle(vector3df enemy, vector3df target);

	IAnimatedMeshSceneNode* node;
	Player* target;
	vector3df facingDirection;
	EnemyState currentState;

	bool bPushedBack;
	f32 pushStart;

	IrrlichtDevice* device;
};

