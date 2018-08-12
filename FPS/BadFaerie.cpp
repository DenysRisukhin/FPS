#include "BadFaerie.h"
#include <iostream>
#include <time.h>

BadFaerie::BadFaerie(vector3df position, f32 newSpeed, ISceneManager* manager, Player* playerTarget, IrrlichtDevice* irrDevice, list<GameObject*> * updateListPtr, IVideoDriver* videoDriver, ISoundEngine* sound) : Enemy(position, newSpeed, manager, playerTarget)
{
	currentState = ENEMY_IDLE;
	driver = videoDriver;
	dodgeStart = 0;
	lastAttack = 0;
	device = irrDevice;
	updateList = updateListPtr;
	_sound = sound;
}

void BadFaerie::attack()
{
	// �������� ����� ���������� BadFaerie 1500.0f
	if ((device->getTimer()->getTime() - lastAttack) < 1500.0f)
		return;
	
	lastAttack = device->getTimer()->getTime();

	node->updateAbsolutePosition();
	core::vector3df posStart = node->getAbsolutePosition();

	// Calculates direction vector
	core::vector3df direction = smgr->getActiveCamera()->getAbsolutePosition() - posStart;
	direction.normalize();

	updateList->push_back( new PowerBallProjectile(posStart, direction, smgr) );

	ISound *bang = _sound->play2D("sounds/lazer.wav", false, true);
	bang->setVolume(0.4f);
	bang->setIsPaused(false);
	bang->drop();
}

void BadFaerie::dodge(f32 deltaTime)
{
	if ((device->getTimer()->getTime() - dodgeStart) > 3000.0f)
	{
		currentState = ENEMY_IDLE;
		return;
	}
	
	vector3df direction = target->getPosition() - node->getAbsolutePosition();
	direction.normalize();

	vector3df normal = direction.crossProduct(vector3df(0, 1, 0));
	normal.normalize();

	node->setPosition(node->getAbsolutePosition() + (normal * speed * deltaTime));
}

void BadFaerie::run(f32 deltaTime)
{
	if (currentState != EnemyState::ENEMY_RUN)
	{
		currentState = EnemyState::ENEMY_RUN;
	}

	target->getNode()->updateAbsolutePosition();
	node->updateAbsolutePosition();

	facePlayer();
	node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - 90, node->getRotation().Z));
	vector3df direction = target->getPosition() - node->getAbsolutePosition();
	direction.normalize();
	node->setPosition(vector3df(node->getAbsolutePosition().X + (direction.X * speed * deltaTime), 135, node->getAbsolutePosition().Z + (direction.Z * speed * deltaTime)));
}

//bool BadFaerie::listHasPowerBall()
//{
//	for each (GameObject* ptr in *listPtr)
//	{
//		if (dynamic_cast<PowerBall*>(ptr) != NULL)
//		{
//			return true;
//		}
//	}
//	return true;
//}

bool BadFaerie::seesPowerBall()
{
	srand(time(NULL));
	u8 chance = rand() % 2;

	if (((node->getAbsolutePosition() - target->getNode()->getAbsolutePosition()).getLength() > 100.0f) && chance == 0)// && listHasPowerBall())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BadFaerie::update(f32 deltaTime)
{
	if (bPushedBack)
	{
		if ((device->getTimer()->getTime() - pushStart) > 3000.0f)
		{
			bPushedBack = false;
		}
		else
		{
			target->getNode()->updateAbsolutePosition();
			node->updateAbsolutePosition();

			facePlayer();
			node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - 90, node->getRotation().Z));
			vector3df direction = target->getPosition() - node->getAbsolutePosition();

			if (direction.getLength() > 800.0f)
			{
				// Enemy is too far away.
			}
			else if (direction.dotProduct(target->getDirection()) > 0)
			{
				// Enemy is behind the player.
			}
			else
			{
				// Push the enemy.
				direction.Y = 0;
				direction *= -1.0f;
				direction.normalize();
				node->setPosition(node->getAbsolutePosition() + (deltaTime * direction * speed * 20.0f));
			}
		}

		return;
	}

	if (bNeedsUpdate)
	{
		if (currentState == ENEMY_DODGE)
		{
			dodge(deltaTime);
			return;
		}
		if (seesPowerBall())
		{
			currentState = ENEMY_DODGE;
			dodgeStart = device->getTimer()->getTime();
			dodge(deltaTime);
			return;
		}

		if ((node->getAbsolutePosition() - target->getNode()->getAbsolutePosition()).getLength() < 25400.0f) // 400
		{
			//node->updateAbsolutePosition();
			//node->getPosition();
			//node->setPosition(node->getAbsolutePosition());
			currentState = ENEMY_ATTACK;
			attack();
		}
		else
		{
			currentState = ENEMY_RUN;
			run(deltaTime);
		}
	}
}

void BadFaerie::loadModel(IAnimatedMesh* mesh, ITexture* texture)
{
	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, texture);
	node->setPosition(origPosition);
	node->addShadowVolumeSceneNode();

	// Make enemy face towards the screen.
	node->setRotation(vector3df(0.0f, -90.0f, 0.0f));
	facingDirection = vector3df(0.0f, 0.0f, 1.0f);
	facingDirection.normalize();

	node->setMD2Animation(EMAT_STAND);
}