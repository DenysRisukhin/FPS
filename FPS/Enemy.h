#pragma once
#include "GameObject.h"
#include "Player.h"

/*!
* Represents enemies behaviours states.
*/
enum EnemyState
{
	ENEMY_RUN,
	ENEMY_ATTACK,
	ENEMY_DODGE, 
	ENEMY_IDLE
};

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

	@param facingDirection ?????? it's vector .


	@param bPushedBack ????.
	@param pushStart ?????.
	*/
	Enemy(vector3df newPosition, f32 newSpeed, ISceneManager* manager, Player* enemyTarget);

	/**
	* Rotating enemies to player face.
	*/
	virtual void facePlayer();

	/**
	* ???? values uses in Badfaire update method
	*/
	//bPushedBack = true;
	//pushStart = device->getTimer()->getTime();
	virtual void pushBack();

	/**
	* ????????????????????? return NULL
	*/
	ISceneNode* getNode();

	/**
	* getNodePos ???????????????????????
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
	//ISceneNode* node;
	Player* target;
	vector3df facingDirection;
	EnemyState currentState;

	bool bPushedBack;
	f32 pushStart;

	IrrlichtDevice* device;
};

