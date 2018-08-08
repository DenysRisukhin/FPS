#include <math.h>
#include "Player.h"
#include <iostream>
#include "GUI.h"

#define SHOT_DELAY_TIME 80

Player::Player(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver, Camera* camera, list<GameObject*> *updateListPtr) :
	WeaponManager(manager, 0),
	device(irrDevice),
	smgr(manager),
	driver(videoDriver),
	sound(createIrrKlangDevice())
{
	listPtr = updateListPtr;
	this->camera = camera;

	// Set weapon by default
	setWeapon(REVOLVER);

	initWeaponAndHandNode();

	lastAttack = 0.0f;
	health = 100;
}

Player::~Player() { 
	sound->drop(); 
	drop();
}

void Player::drop() {
	if (weaponNode)
	{
		weaponNode->remove();
		weaponNode = NULL;

		handNode->remove();
		handNode = NULL;
	}
}

void Player::initWeaponAndHandNode() {
	
	weaponMesh = smgr->getMesh("stuff/weapons/rev.3DS");
	if (!weaponMesh) {
		printf("Weapon Mesh load failed\n");
		return;
	}

	weaponNode = smgr->addAnimatedMeshSceneNode(weaponMesh);
	if (!weaponNode) {
		printf("Weapon Node creation failed\n");
		return;
	}
	
	handMesh = smgr->getMesh("stuff/weapons/hand.3DS");
	if (!handMesh) {
		printf("hand Mesh load failed\n");
		return;
	}
	handNode = smgr->addAnimatedMeshSceneNode(handMesh);
	if (!handNode) {
		printf("hand Node creation failed\n");
		return;
	}

	weaponNode->setParent(camera->getNode());
	weaponNode->setScale(core::vector3df(0.02f, 0.02f, 0.02f));
	weaponNode->setPosition(core::vector3df(7.f, -6.f, 12.f));
	weaponNode->setRotation(core::vector3df(0, 0, 90));
	weaponNode->setMaterialFlag(video::EMF_LIGHTING, true);
	weaponNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	if (weaponNode)
		handNode->setParent(weaponNode);

	handNode->setPosition(core::vector3df(-40.f, 0.f, -250.f));
	handNode->setMaterialFlag(video::EMF_LIGHTING, false);
	handNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
}

void Player::setWeapon(WEAPON weapon) {
	this->weapon = weapon;
}

void Player::setHealth(u8 health) {
	this->health = health;
}

void Player::setDamage(u8 attackRating){
	health -= attackRating * 10;
}

WEAPON Player::getWeapon() {
	return weapon;
}

ISoundEngine* Player::getSound() {
	return sound;
}
ISceneManager* Player::getSmgr() {
	return smgr;
}

IAnimatedMeshSceneNode* Player::getNode() {
	return weaponNode;
}

vector3df Player::getPosition() {
	return weaponNode->getAbsolutePosition();
}

u8 Player::getHealth()
{
	return health;
}

vector3df Player::getDirection()
{
	return forwardDirection;
}

void Player::kill() {
	health = 0;
}

bool Player::isDead() {
	return (health <= 0);
}

void Player::changeWeapon(s32 weapon)
{
	switch (weapon)
	{
	case REVOLVER: {

		setWeapon(REVOLVER);

		weaponMesh = smgr->getMesh("stuff/weapons/rev.3DS");
		if (!weaponMesh) {
			printf("Weapon Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 7.f; pos.Y = -6.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		
		handMesh = smgr->getMesh("stuff/weapons/hand.3DS");
		if (!handMesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 1;
		posh.X = -40.f; posh.Y = 0.f; posh.Z = -250.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;
		break;
	}
	case REVEVO: {
		setWeapon(REVEVO);
		weaponMesh = smgr->getMesh("stuff/weapons/gun.3DS");
		if (!weaponMesh) {
			printf("Weapon Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 7.f; pos.Y = -6.f; pos.Z = 11.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		
		handMesh = smgr->getMesh("stuff/weapons/hand.3DS");
		if (!handMesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 0.9f;
		posh.X = 0.f; posh.Y = -50.f; posh.Z = -300.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;
		break;
	}
	case LASER: {
		setWeapon(LASER);
		weaponMesh = smgr->getMesh("stuff/weapons/laser.3DS");
		if (!weaponMesh) {
			printf("Weapon Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 4.f; pos.Y = -4.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 90; rot.Z = 90;
		
		handMesh = smgr->getMesh("stuff/weapons/hand4.3DS");
		if (!handMesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 1.f;
		posh.X = 0.f; posh.Y = 0.f; posh.Z = 0.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;
		break;
	}
	case MGUN: {
		setWeapon(MGUN);
		weaponMesh = smgr->getMesh("stuff/weapons/mgunold.3DS");
		if (!weaponMesh) {
			printf("Weapon Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 6.f; pos.Y = -5.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		
		handMesh = smgr->getMesh("stuff/weapons/hand2.3DS");
		if (!handMesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 0.8f;
		posh.X = -10.f; posh.Y = -70.f; posh.Z = -320.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;
		break;
	}
	case MGUNB: {
		setWeapon(MGUNB);
		weaponMesh = smgr->getMesh("stuff/weapons/mgun.3DS");
		if (!weaponMesh) {
			printf("Weapon Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 6.f; pos.Y = -5.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		
		handMesh = smgr->getMesh("stuff/weapons/hand3.3DS");
		if (!handMesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 0.8f;
		posh.X = -80.f; posh.Y = -70.f; posh.Z = -320.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;
		break;
	}
	case SMG: {
		setWeapon(SMG);
		weaponMesh = smgr->getMesh("stuff/weapons/smg.3DS");
		if (!weaponMesh) {
			printf("Weapon Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 6.f; pos.Y = -5.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		
		handMesh = smgr->getMesh("stuff/weapons/hand.3DS");
		if (!handMesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 0.8f;
		posh.X = -50.f; posh.Y = -70.f; posh.Z = -300.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;
		break;
	 }
	}

	if (weaponNode) {
		weaponNode->remove();
		weaponNode = smgr->addAnimatedMeshSceneNode(weaponMesh);
		weaponNode->setParent(smgr->getActiveCamera());
		weaponNode->setScale(scale);
		weaponNode->setPosition(pos);
		weaponNode->setRotation(rot);
		weaponNode->setMaterialFlag(video::EMF_LIGHTING, true);
		weaponNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

		if (handNode) {
			handNode = smgr->addAnimatedMeshSceneNode(handMesh);
			handNode->setParent(weaponNode);
			handNode->setScale(scaleh);
			handNode->setPosition(posh);
			handNode->setRotation(roth);
			handNode->setMaterialFlag(video::EMF_LIGHTING, false);
			handNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
		}
	}
	else {
		printf("weaponNode creation failed\n");
		return;
	}
}

void Player::fire(s32 weapon, IrrlichtDevice *device) {

	switch (weapon) {
	case REVOLVER: {
		if ((device->getTimer()->getTime() - lastAttack) > 700 && ammoRev > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(weaponNode, dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			ISound *bang = sound->play2D("stuff/sound/gunshot.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();
		
			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, -30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			
			// Fire projectile
			GunProjectile* proj = new GunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
				
			listPtr->push_back(proj);
			
			if (ammoRev > 0)
				ammoRev--;

			if (ammoRev == 0 && magRev > 0) {
				magRev--;
				ammoRev = 6;
			}
		}
	}break;
	case REVEVO: {
		if ((device->getTimer()->getTime() - lastAttack) > 500 && ammoRevevo > 0) // 400
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(weaponNode, dimension2d<f32>(50, 50), vector3df(-500.f, -700.f, 2000.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			ISound *bang = sound->play2D("stuff/sound/gunshot_short.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, -30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);

			// Fire projectile
			GunProjectile* proj = new GunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			if (ammoRevevo > 0)
				ammoRevevo--;

			if (ammoRevevo == 0 && magRevevo > 0) {
				magRevevo--;
				ammoRevevo = 10;
			}
		}
	}break;
	case MGUN: {
		if ((device->getTimer()->getTime() - lastAttack) > 250 && ammoMgun > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(weaponNode, dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			ISound *bang = sound->play2D("stuff/sound/gunshot.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			
			GunProjectile* proj = new GunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			if (ammoMgun > 0)
				ammoMgun--;

			if (ammoMgun == 0 && magMgun > 0) {
				magMgun--;
				ammoMgun = 25;
			}
		}
	}break;
	case MGUNB: {
		if ((device->getTimer()->getTime() - lastAttack) > 200 && ammoMgunb > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(weaponNode, dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			ISound *bang = sound->play2D("stuff/sound/gunshot_short.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);

			// Fire projectile
			GunProjectile* proj = new GunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			if (ammoMgunb > 0)
				ammoMgunb--;

			if (ammoMgunb == 0 && magMgunb > 0) {
				magMgunb--;
			    ammoMgunb = 25;
			}
		}
	}break;
	case SMG: {
		if ((device->getTimer()->getTime() - lastAttack) > 150 && ammoSmg > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(weaponNode, dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 1500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			ISound *bang = sound->play2D("stuff/sound/gunshot_silencer.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			
			// Fire projectile
			GunProjectile* proj = new GunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			if (ammoSmg > 0)
				ammoSmg--;

			if (ammoSmg == 0 && magSmg > 0) {
				magSmg--;
				ammoSmg = 15;
			}
		}
	}break;
	case LASER: {
		if ((device->getTimer()->getTime() - lastAttack) > SHOT_DELAY_TIME && ammoRev > 0)
		{
			lastAttack = device->getTimer()->getTime();
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);

			// Fire projectile
			LaserProjectile* proj = new LaserProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			ammo--;

			ISound *bang = sound->play2D("stuff/sound/laser.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();
		}
	 }break;
	}
}




