#include <math.h>
#include "Player.h"
#include <iostream>
#include "GUI.h"

#define SHOT_DELAY_TIME 80

int nextDecal = 0;

void Player::drop()
{
	if (GunNode)
	{
		GunNode->remove();
		GunNode = NULL;
	}
}

WEAPON Player::getWeapon() {
	return weapon;
}

void Player::setCamera(Camera* myCamera) {
	GunNode->setParent(myCamera->getNode());
}

Player::Player(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver, Camera* myCamera, list<GameObject*> *updateListPtr) : 
	CCharacter(manager, 0), 
	device(irrDevice), 
	smgr(manager),
	driver(videoDriver),
	sound(createIrrKlangDevice())
{
	lastTeleport = 0.0f;
	lastPush = 0.0f;
	lastAttack = 0.0f;
	speed = 0.2f;
	health = 100;
	mana = 100;

	listPtr = updateListPtr;

	camera = myCamera;

	setWeapon(REVOLVER);

	//weapons
	mesh = smgr->getMesh("stuff/weapons/rev.3DS");
	if (!mesh) {
		printf("Gun Mesh load failed\n");
		return;
	}
	GunNode = smgr->addAnimatedMeshSceneNode(mesh);
	if (!GunNode) {
		printf("Gun Node creation failed\n");
		return;
	}
	//for hand 
	handmesh = smgr->getMesh("stuff/weapons/hand.3DS");
	if (!handmesh) {
		printf("hand Mesh load failed\n");
		return;
	}
	HandNode = smgr->addAnimatedMeshSceneNode(handmesh);
	if (!HandNode) {
		printf("hand Node creation failed\n");
		return;
	}
		
	GunNode->setParent(camera->getNode());
	
	GunNode->setScale(core::vector3df(0.02f, 0.02f, 0.02f));
	GunNode->setPosition(core::vector3df(7.f, -6.f, 12.f));
	GunNode->setRotation(core::vector3df(0, 0, 90));
	GunNode->setMaterialFlag(video::EMF_LIGHTING, true);
	GunNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

	//hand
	if (GunNode)
		HandNode->setParent(GunNode);

	HandNode->setPosition(core::vector3df(-40.f, 0.f, -250.f));
	HandNode->setMaterialFlag(video::EMF_LIGHTING, false);
	HandNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
}

void Player::setUpdateList(list<GameObject*> *updateListPtr) {
	listPtr = updateListPtr;
}

IAnimatedMeshSceneNode* Player::getNode()
{
	return GunNode;
}

vector3df Player::getPosition()
{
	return GunNode->getAbsolutePosition();
}

void Player::setWeapon(WEAPON weapon) {
	this->weapon = weapon;
}

void Player::changeWeapon(s32 weapon)
{
	switch (weapon)
	{
	case REVOLVER: {

		setWeapon(REVOLVER);

		mesh = smgr->getMesh("stuff/weapons/rev.3DS");
		if (!mesh) {
			printf("Gun Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 7.f; pos.Y = -6.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		//for hand 
		handmesh = smgr->getMesh("stuff/weapons/hand.3DS");
		if (!handmesh) {
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
		mesh = smgr->getMesh("stuff/weapons/gun.3DS");
		if (!mesh) {
			printf("Gun Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 7.f; pos.Y = -6.f; pos.Z = 11.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		//for hand 
		handmesh = smgr->getMesh("stuff/weapons/hand.3DS");
		if (!handmesh) {
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
		mesh = smgr->getMesh("stuff/weapons/laser.3DS");
		if (!mesh) {
			printf("Gun Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 4.f; pos.Y = -4.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 90; rot.Z = 90;
		//for hand 
		handmesh = smgr->getMesh("stuff/weapons/hand4.3DS");
		if (!handmesh) {
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
		mesh = smgr->getMesh("stuff/weapons/mgunold.3DS");
		if (!mesh) {
			printf("Gun Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 6.f; pos.Y = -5.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		//for hand 
		handmesh = smgr->getMesh("stuff/weapons/hand2.3DS");
		if (!handmesh) {
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
		mesh = smgr->getMesh("stuff/weapons/mgun.3DS");
		if (!mesh) {
			printf("Gun Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 6.f; pos.Y = -5.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		//for hand 
		handmesh = smgr->getMesh("stuff/weapons/hand3.3DS");
		if (!handmesh) {
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
		mesh = smgr->getMesh("stuff/weapons/smg.3DS");
		if (!mesh) {
			printf("Gun Mesh load failed\n");
			return;
		}
		scale.X = scale.Y = scale.Z = 0.02f;
		pos.X = 6.f; pos.Y = -5.f; pos.Z = 12.f;
		rot.X = 0; rot.Y = 0; rot.Z = 90;
		//for hand 
		handmesh = smgr->getMesh("stuff/weapons/hand.3DS");
		if (!handmesh) {
			printf("hand Mesh load failed\n");
			return;
		}
		scaleh.X = scaleh.Y = scaleh.Z = 0.8f;
		posh.X = -50.f; posh.Y = -70.f; posh.Z = -300.f;
		roth.X = 0; roth.Y = 0; roth.Z = 0;

		break;
	}
	}

	if (GunNode) {
		GunNode->remove();
		GunNode = smgr->addAnimatedMeshSceneNode(mesh);

		//if (Camera) GunNode->setParent(Camera);

		GunNode->setParent(smgr->getActiveCamera());

		GunNode->setScale(scale);
		GunNode->setPosition(pos);
		GunNode->setRotation(rot);
		GunNode->setMaterialFlag(video::EMF_LIGHTING, true);
		GunNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);

		if (HandNode) {
			HandNode = smgr->addAnimatedMeshSceneNode(handmesh);

			HandNode->setParent(GunNode);
			HandNode->setScale(scaleh);
			HandNode->setPosition(posh);
			HandNode->setRotation(roth);
			HandNode->setMaterialFlag(video::EMF_LIGHTING, false);
			HandNode->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
		}
	}
	else {
		printf("Gun Node creation failed\n");
		return;
	}
}

void Player::fire(s32 weapon, IrrlichtDevice *device) {

	switch (weapon) {
	case REVOLVER: {
	
		if ((device->getTimer()->getTime() - lastAttack) > 700 && ammo_rev > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(GunNode, dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
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
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
				
			listPtr->push_back(proj);
			
			TimeSinceLastShot = 0;
			TimeSinceLastRefill = 0;

	
			if (ammo_rev > 0)
				ammo_rev--;

			if (ammo_rev == 0 && mag_rev > 0) {
				mag_rev--;
				ammo_rev = 6;
			}
		}
	}break;
	case REVEVO: {
		if ((device->getTimer()->getTime() - lastAttack) > 500 && ammo_revevo > 0) // 400
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(GunNode,dimension2d<f32>(50, 50), vector3df(-500.f, -700.f, 2000.f));
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
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			TimeSinceLastShot = 0;

			TimeSinceLastRefill = 0;

			if (ammo_revevo > 0)
				ammo_revevo--;

			if (ammo_revevo == 0 && mag_revevo > 0) {
				mag_revevo--;
				ammo_revevo = 10;
			}
		}
	}break;
	case MGUN: {
		if ((device->getTimer()->getTime() - lastAttack) > 250 && ammo_mgun > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
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
			
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);
			
			TimeSinceLastShot = 0;
			TimeSinceLastRefill = 0;

			if (ammo_mgun > 0)
				ammo_mgun--;

			if (ammo_mgun == 0 && mag_mgun > 0) {
				mag_mgun--;
				ammo_mgun = 25;
			}
		}
	}break;
	case MGUNB: {
		if ((device->getTimer()->getTime() - lastAttack) > 200 && ammo_mgunb > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
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
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			TimeSinceLastShot = 0;
			TimeSinceLastRefill = 0;

			if (ammo_mgunb > 0)
				ammo_mgunb--;

			if (ammo_mgunb == 0 && mag_mgunb > 0) {
				mag_mgunb--;
			    ammo_mgunb = 25;
			}
		}
	}break;
	case SMG: {
		if ((device->getTimer()->getTime() - lastAttack) > 150 && ammo_smg > 0)
		{
			lastAttack = device->getTimer()->getTime();

			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 1500.f));
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
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			TimeSinceLastShot = 0;
			TimeSinceLastRefill = 0;

			if (ammo_smg > 0)
				ammo_smg--;

			if (ammo_smg == 0 && mag_smg > 0) {
				mag_smg--;
				ammo_smg = 15;
			}
		}
	}break;
	case LASER: {
		
		if ((device->getTimer()->getTime() - lastAttack) > SHOT_DELAY_TIME && ammo_rev > 0)
		{
			lastAttack = device->getTimer()->getTime();
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);

			// Fire projectile
			CLaserProjectile* proj = new CLaserProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);

			listPtr->push_back(proj);

			TimeSinceLastShot = 0;

			Ammo--;

			ISound *bang = sound->play2D("stuff/sound/laser.wav", false, true);
			bang->setVolume(0.4f);
			bang->setIsPaused(false);
			bang->drop();
		}
	}break;
	}//end switch
}//end function

void Player::takeDamage(u8 attackRating)
{
	// Reduce Player Health.
	health -= attackRating * 10;
}


void Player::takePickup()
{
	health += PICKUP_HEAL;
	if (health > 100)
	{
		health = 100;
	}
}

void Player::kill()
{
	health = 0;
}

bool Player::isDead()
{
	return (health <= 0);
}

u8 Player::getHealth()
{
	return health;
}

u8 Player::getMana()
{
	return mana;
}

void Player::incrementMana()
{
	mana += MANA_REGENERATE_PER_SEC;
	if (mana > 100)
	{
		mana = 100;
	}
}

IAnimatedMesh* Player::getMesh()
{
	return mesh;
}

vector3df Player::getDirection()
{
	return forwardDirection;
}


