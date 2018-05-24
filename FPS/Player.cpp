#include <math.h>
#include "Player.h"
//#include "PowerBall.h"

#define SHOT_DELAY_TIME 80

//DecalSceneNode* decals[MAX_DECALS];

int nextDecal = 0;

WEAPON Player::getWeapon() {
	return weapon;
}

Player::Player(IrrlichtDevice* irrDevice, ISceneManager* manager, IVideoDriver* videoDriver, Camera* myCamera) : CCharacter(manager, 0), device(irrDevice), smgr(manager), driver(videoDriver)
{
	lastTeleport = 0.0f;
	lastPush = 0.0f;
	lastAttack = 0.0f;
	speed = 0.2f;
	health = 100;
	mana = 100;

	camera = myCamera;

	setWeapon(REVOLVER);

	//*******

	/*mesh = smgr->getMesh("Models/sydney.md2");
	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialTexture(0, driver->getTexture("Textures/sydney.bmp"));
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setPosition(vector3df(600, 60, 600));
	node->setRotation(vector3df(0, -90, 0));
	node->addShadowVolumeSceneNode();*/

	//camera->getNode()->updateAbsolutePosition();
	//node->updateAbsolutePosition();

	//camera->getNode()->setTarget(node->getAbsolutePosition());

	// Calculating forwardDirection.
    //vector3df temp = vector3df(camera->getNode()->getAbsolutePosition().X, (camera->getNode()->getAbsolutePosition().Y) - 0, camera->getNode()->getAbsolutePosition().Z);
	//forwardDirection = node->getAbsolutePosition() - temp;
	//forwardDirection.normalize();

	// Initially setting IDLE animation.
	//setIdleAnimation();

	// Calculating cameraDistance.
	//temp = node->getAbsolutePosition() - (camera->getNode()->getAbsolutePosition());
	//cameraDistance = fabs(temp.getLength());

	//*******

	//IAnimatedMeshMD2* weaponMesh = (IAnimatedMeshMD2*)smgr->getMesh("Models/m16.md2"); //Can also change with gun.md2
	//if (0 == weaponMesh)
	//	return;

	//c8 buf[64];

	//if (weaponMesh->getMeshType() == EAMT_MD2)
	//{
	//	s32 count = weaponMesh->getAnimationCount();
	//	for (s32 i = 0; i != count; ++i)
	//	{
	//		snprintf(buf, 64, "Animation: %s", weaponMesh->getAnimationName(i));
	//		device->getLogger()->log(buf, ELL_INFORMATION);
	//	}
	//}

	//auto WeaponNode = smgr->addAnimatedMeshSceneNode(
	//	weaponMesh,
	//	smgr->getActiveCamera(),
	//	10,
	//	vector3df(0, 0, 0),
	//	vector3df(-90, -90, 90)
	//);
	//WeaponNode->setMaterialFlag(EMF_LIGHTING, false);
	//WeaponNode->setMaterialTexture(0, driver->getTexture("Textures/m16.png"));//Can also change with gun.jpg
	//																 //WeaponNode->setFrameLoop(50,51);
	//WeaponNode->setMD2Animation("stand");
	////WeaponNode->setAnimationSpeed(2);
	//WeaponNode->setLoopMode(true);

	////
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
	//revolver
	//if (myCamera) 
		
		GunNode->setParent(camera->getNode());
	/* GunNode = smgr->addAnimatedMeshSceneNode(
		mesh,
		smgr->getActiveCamera(),
		10,
		vector3df(0, 0, 0),
		vector3df(-90, -90, 90)
	);*/

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

void Player::setWeapon(WEAPON weapon) {
	this->weapon = weapon;
}

void Player::changeWeapon(s32 weapon)
{
	//for the new 'change weapon' function
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
			//HandNode->remove();
			HandNode = smgr->addAnimatedMeshSceneNode(handmesh);

			/*if(GunNode)*/ HandNode->setParent(GunNode);
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

bool Player::update(s32 elapsedTime, s32 weapon, IrrlichtDevice *device) {

	//if (CCharacter::update(elapsedTime)) return true;
	//if (AIEntity) {
		// tell the paie where we are now
	core::vector3df pos = smgr->getActiveCamera()->getAbsolutePosition();
	//	AIEntity->setPosition(pos);
	//}

	switch (weapon) {
	case REVOLVER: {
		// Update projectiles and check collisions
		core::list<CGunProjectile*>::Iterator projIterev = GunProjectiles.begin();
		while (projIterev != GunProjectiles.end()) {

			if ((*projIterev)->update()) {
				delete *projIterev;
				projIterev = GunProjectiles.erase(projIterev);
				
			}
			else {
			//	CCharacter* enemy = NULL;
				bool collision = false;
				core::line3df ray((*projIterev)->getPreviousPosition(), (*projIterev)->getPosition());
				core::vector3df outVec;
				core::triangle3df outTri;
				scene::ISceneNode* outNode;
			/*	core::array<IAIEntity*> enemies = ((IPlayerAIEntity*)AIEntity)->getEnemyGroup()->Entities;
				for (u32 i = 0; i < enemies.size(); ++i) {
					enemy = (CCharacter*)(enemies[i]->getUserData());
					if (enemy->getAIEntity()->getNode()->getTransformedBoundingBox().intersectsWithLine(ray)) {
						enemy->registerHit(5);
						collision = true;
						delete *projIterev;
						projIterev = GunProjectiles.erase(projIterev);
						break;
					}
				}*/
				if (smgr->getSceneCollisionManager()->getCollisionPoint(ray, MetaSelector, outVec, outTri, outNode)) {
					collision = true;
					delete *projIterev;
					projIterev = GunProjectiles.erase(projIterev);
					
					//for decals
					
					//decals[nextDecal]->Setup(outTri, outVec);
					//nextDecal++;
					//if (nextDecal >= MAX_DECALS)
					//	nextDecal = 0;
				}
				if (!collision)
					projIterev++;
			}
		}
		if (ammo_rev == 0 && mag_rev > 0) {
			mag_rev--;
			ammo_rev = 6;
		}

		//use this for freakish results (uncomment function below)
		Projectiles.clear();
	} break;
	case REVEVO: {
		// Update projectiles and check collisions
		core::list<CGunProjectile*>::Iterator projIterevevo = GunProjectiles.begin();
		while (projIterevevo != GunProjectiles.end()) {
			if ((*projIterevevo)->update()) {
				delete *projIterevevo;
				projIterevevo = GunProjectiles.erase(projIterevevo);
			}
			else {
				//	CCharacter* enemy = NULL;
				bool collision = false;
				core::line3df ray((*projIterevevo)->getPreviousPosition(), (*projIterevevo)->getPosition());
				core::vector3df outVec;
				core::triangle3df outTri;
				scene::ISceneNode* outNode;
				/*core::array<IAIEntity*> enemies = ((IPlayerAIEntity*)AIEntity)->getEnemyGroup()->Entities;
				for (u32 i = 0; i < enemies.size(); ++i) {
					enemy = (CCharacter*)(enemies[i]->getUserData());
					if (enemy->getAIEntity()->getNode()->getTransformedBoundingBox().intersectsWithLine(ray)) {
						enemy->registerHit(5);
						collision = true;
						delete *projIterevevo;
						projIterevevo = GunProjectiles.erase(projIterevevo);
						break;
					}*/
					//}
				if (smgr->getSceneCollisionManager()->getCollisionPoint(ray, MetaSelector, outVec, outTri, outNode)) {
					collision = true;
										delete *projIterevevo;
					projIterevevo = GunProjectiles.erase(projIterevevo);
					
					//for decals
					/*decals[nextDecal]->Setup(outTri, outVec);
					nextDecal++;
					if (nextDecal >= MAX_DECALS)
						nextDecal = 0;*/
				}
					if (!collision) projIterevevo++;
				}
			}
			if (ammo_revevo == 0 && mag_revevo > 0) {
				mag_revevo--;
				ammo_revevo = 10;
			}
		} break;
	case MGUN: {
		// Update projectiles and check collisions
		core::list<CGunProjectile*>::Iterator projItermg = GunProjectiles.begin();
		while (projItermg != GunProjectiles.end()) {
			if ((*projItermg)->update()) {
				delete *projItermg;
				projItermg = GunProjectiles.erase(projItermg);
			}
			else {
				//CCharacter* enemy = NULL;
				bool collision = false;
				core::line3df ray((*projItermg)->getPreviousPosition(), (*projItermg)->getPosition());
				core::vector3df outVec;
				core::triangle3df outTri;
				scene::ISceneNode* outNode;
				/*core::array<IAIEntity*> enemies = ((IPlayerAIEntity*)AIEntity)->getEnemyGroup()->Entities;
				for (u32 i = 0; i < enemies.size(); ++i) {
					enemy = (CCharacter*)(enemies[i]->getUserData());
					if (enemy->getAIEntity()->getNode()->getTransformedBoundingBox().intersectsWithLine(ray)) {
						enemy->registerHit(15);
						collision = true;
						delete *projItermg;
						projItermg = GunProjectiles.erase(projItermg);
						break;
					}
				}*/
				if (smgr->getSceneCollisionManager()->getCollisionPoint(ray, MetaSelector, outVec, outTri, outNode)) {
					collision = true;
					delete *projItermg;
					projItermg = GunProjectiles.erase(projItermg);
					
					//for decals
					/*decals[nextDecal]->Setup(outTri, outVec);
					nextDecal++;
					if (nextDecal >= MAX_DECALS)
						nextDecal = 0;*/
				}
				if (!collision) projItermg++;
			}//end else
		}//end while
		if (ammo_mgun == 0 && mag_mgun > 0) {
			mag_mgun--;
			ammo_mgun = 25;
		}
	} break;	//end mgun
	case MGUNB: {
		// Update projectiles and check collisions
		core::list<CGunProjectile*>::Iterator projItermgb = GunProjectiles.begin();
		while (projItermgb != GunProjectiles.end()) {
			if ((*projItermgb)->update()) {
				delete *projItermgb;
				projItermgb = GunProjectiles.erase(projItermgb);
			}
			else {
				//CCharacter* enemy = NULL;
				bool collision = false;
				core::line3df ray((*projItermgb)->getPreviousPosition(), (*projItermgb)->getPosition());
				core::vector3df outVec;
				core::triangle3df outTri;
				scene::ISceneNode* outNode;
				/*core::array<IAIEntity*> enemies = ((IPlayerAIEntity*)AIEntity)->getEnemyGroup()->Entities;
				for (u32 i = 0; i < enemies.size(); ++i) {
					enemy = (CCharacter*)(enemies[i]->getUserData());
					if (enemy->getAIEntity()->getNode()->getTransformedBoundingBox().intersectsWithLine(ray)) {
						enemy->registerHit(15);
						collision = true;
						delete *projItermgb;
						projItermgb = GunProjectiles.erase(projItermgb);
						break;
					}
				}*/
				if (smgr->getSceneCollisionManager()->getCollisionPoint(ray, MetaSelector, outVec, outTri, outNode)) {
					collision = true;
					delete *projItermgb;
					projItermgb = GunProjectiles.erase(projItermgb);
					
					//for decals
					/*decals[nextDecal]->Setup(outTri, outVec);
					nextDecal++;
					if (nextDecal >= MAX_DECALS)
						nextDecal = 0;*/
				}
					if (!collision) projItermgb++;
				}//end else
			}//end while
			if (ammo_mgunb == 0 && mag_mgunb > 0) {
				mag_mgunb--;
				ammo_mgunb = 25;
			}
		} break;	//end mgun 2 
	case SMG: {
		// Update projectiles and check collisions
		core::list<CGunProjectile*>::Iterator projItersmg = GunProjectiles.begin();
		while (projItersmg != GunProjectiles.end()) {
			if ((*projItersmg)->update()) {
				delete *projItersmg;
				projItersmg = GunProjectiles.erase(projItersmg);
			}
			else {
				//	CCharacter* enemy = NULL;
				bool collision = false;
				core::line3df ray((*projItersmg)->getPreviousPosition(), (*projItersmg)->getPosition());
				core::vector3df outVec;
				core::triangle3df outTri;
				scene::ISceneNode* outNode;
				/*core::array<IAIEntity*> enemies = ((IPlayerAIEntity*)AIEntity)->getEnemyGroup()->Entities;
				for (u32 i = 0; i < enemies.size(); ++i) {
					enemy = (CCharacter*)(enemies[i]->getUserData());
					if (enemy->getAIEntity()->getNode()->getTransformedBoundingBox().intersectsWithLine(ray)) {
						enemy->registerHit(10);
						collision = true;
						delete *projItersmg;
						projItersmg = GunProjectiles.erase(projItersmg);
						break;
					}
				}*/
				if (smgr->getSceneCollisionManager()->getCollisionPoint(ray, MetaSelector, outVec, outTri, outNode)) {
					collision = true;
					delete *projItersmg;
					projItersmg = GunProjectiles.erase(projItersmg);

					//for decals
					/*decals[nextDecal]->Setup(outTri, outVec);
					nextDecal++;
					if (nextDecal >= MAX_DECALS)
						nextDecal = 0;*/
				}
					if (!collision) projItersmg++;
				}//end else
			}//end while
			if (ammo_smg == 0 && mag_smg > 0) {
				mag_smg--;
				ammo_smg = 15;
			}
		} break;	//end smg
	case LASER: {
		// Update projectiles and check collisions
		core::list<CLaserProjectile*>::Iterator projIter = LaserProjectiles.begin();
		while (projIter != LaserProjectiles.end()) {
			if ((*projIter)->update()) {
				delete *projIter;
				projIter = LaserProjectiles.erase(projIter);
			}
			else {
				//CCharacter* enemy = NULL;
				bool collision = false;
				core::line3df ray((*projIter)->getPreviousPosition(), (*projIter)->getPosition());
				core::vector3df outVec;
				core::triangle3df outTri;
				scene::ISceneNode* outNode;
				//core::array<IAIEntity*> enemies = ((IPlayerAIEntity*)AIEntity)->getEnemyGroup()->Entities;
				//for (u32 i = 0; i < enemies.size(); ++i) {
				//	enemy = (CCharacter*)(enemies[i]->getUserData());
				//	if (enemy->getAIEntity()->getNode()->getTransformedBoundingBox().intersectsWithLine(ray)) {
				//		enemy->registerHit(50);
				//		collision = true;
				//		delete *projIter;
				//		projIter = LaserProjectiles.erase(projIter);
				//		break;
				//	}
				//}
				if (smgr->getSceneCollisionManager()->getCollisionPoint(ray, MetaSelector, outVec, outTri, outNode)) {
					collision = true;
					delete *projIter;
					projIter = LaserProjectiles.erase(projIter);

					//for decals
					/*decals[nextDecal]->Setup(outTri, outVec);
					nextDecal++;
					if (nextDecal >= MAX_DECALS)
						nextDecal = 0;*/
				}
				if (!collision) 
					projIter++;
			}		//end else
		}			//end while
	} break; //laser
	}
   
  
	
	
	TimeSinceLastShot += elapsedTime;

	return false;

}


void Player::fire(s32 weapon, IrrlichtDevice *device) {

	switch (weapon) {
	case REVOLVER: {
		if (TimeSinceLastShot >= SHOT_DELAY_TIME + 2 && ammo_rev > 0) 
		{
			gunflame = smgr->addBillboardSceneNode(GunNode, dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			//play sound
			//if (engine)
			//	engine->play2D("stuff/sound/gunshot.wav");

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, -30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			// Fire projectile
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
			if (proj) GunProjectiles.push_back(proj);
			TimeSinceLastShot = 0;
			TimeSinceLastRefill = 0;

			image = device->getVideoDriver()->getTexture("stuff/logos/bullet.png");
			/*for (int i = 0; i<MAX_DECALS; i++)
			{
				decals[i] = new DecalSceneNode(smgr->getRootSceneNode(),
					smgr, image, 10.2f);
				decals[i]->setLifeSpan(15);
			}*/

			if (ammo_rev > 0)
				ammo_rev--;
		}
	}break;
	case LASER: {
		//originally was: 'CharacterType == ECT_CHASING' but i've changed some things so....
		if (TimeSinceLastShot >= SHOT_DELAY_TIME && Ammo > 0)
		{
			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			// Fire projectile
			CLaserProjectile* proj = new CLaserProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
			if (proj) LaserProjectiles.push_back(proj);
			TimeSinceLastShot = 0;
			
			Ammo--;
			TimeSinceLastRefill = 0;

			//play sound
			//if (engine)
			//	engine->play2D("stuff/sound/laser.wav");

			image = device->getVideoDriver()->getTexture("stuff/logos/burn.png");

			/*for (int i = 0; i<MAX_DECALS; i++)
			{
				decals[i] = new DecalSceneNode(smgr->getRootSceneNode(),
					smgr, image, 10.2f);
				decals[i]->setLifeSpan(15);
			}*/
		}
	}break;
	case MGUN: {
		if (TimeSinceLastShot >= SHOT_DELAY_TIME - 50 && ammo_mgun > 0)
		{
			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			//play sound
			//if (engine)
			//	engine->play2D("stuff/sound/gunshot.wav");

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			// Fire projectile
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
			if (proj) GunProjectiles.push_back(proj);
			TimeSinceLastShot = 0;
			//Ammo--;
			TimeSinceLastRefill = 0;

			image = device->getVideoDriver()->getTexture("stuff/logos/bullet.png");
			/*for (int i = 0; i<MAX_DECALS; i++)
			{
				decals[i] = new DecalSceneNode(smgr->getRootSceneNode(),
					smgr, image, 10.2f);
				decals[i]->setLifeSpan(15);
			}*/

			if (ammo_mgun > 0)
				ammo_mgun--;
		}
	}break;//end mgun
	case REVEVO: {
		if (TimeSinceLastShot >= SHOT_DELAY_TIME + 2 && ammo_revevo > 0) // 400
		{
			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-500.f, -700.f, 2000.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			//play sound
			/*if (engine)
				engine->play2D("stuff/sound/gunshot_short.wav");
*/
			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, -30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			// Fire projectile
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
			if (proj) GunProjectiles.push_back(proj);
			TimeSinceLastShot = 0;
			
			TimeSinceLastRefill = 0;

			image = device->getVideoDriver()->getTexture("stuff/logos/bullet.png");
			/*for (int i = 0; i<MAX_DECALS; i++)
			{
				decals[i] = new DecalSceneNode(smgr->getRootSceneNode(),
					smgr, image, 10.2f);
				decals[i]->setLifeSpan(15);
			}*/

			if (ammo_revevo > 0)
				ammo_revevo--;
		}
	}break;
	case MGUNB: {
		if (TimeSinceLastShot >= SHOT_DELAY_TIME - 50 && ammo_mgunb > 0)
		{
			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 2500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			//play sound
			/*if (engine)
				engine->play2D("stuff/sound/gunshot_short.wav");*/

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			// Fire projectile
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
			if (proj) GunProjectiles.push_back(proj);
			TimeSinceLastShot = 0;
			//Ammo--;
			TimeSinceLastRefill = 0;

			image = device->getVideoDriver()->getTexture("stuff/logos/bullet.png");
			/*for (int i = 0; i<MAX_DECALS; i++)
			{
				decals[i] = new DecalSceneNode(smgr->getRootSceneNode(),
					smgr, image, 10.2f);
				decals[i]->setLifeSpan(15);
			}*/

			if (ammo_mgunb > 0)
				ammo_mgunb--;
		}
	}break;
	case SMG: {
		if (TimeSinceLastShot >= SHOT_DELAY_TIME + 50 && ammo_smg > 0)
		{
			gunflame = smgr->addBillboardSceneNode(GunNode,
				dimension2d<f32>(50, 50), vector3df(-300.f, -500.f, 1500.f));
			gunflame->setMaterialFlag(video::EMF_LIGHTING, false);
			gunflame->setMaterialTexture(0, device->getVideoDriver()->getTexture("stuff/logos/gunFlame.bmp"));
			gunflame->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			ISceneNodeAnimator* gunanim = smgr->createDeleteAnimator(50);
			gunflame->addAnimator(gunanim);
			gunanim->drop();

			//play sound
			/*if (engine)
				engine->play2D("stuff/sound/gunshot_silencer.wav");*/

			// Calculate the position to fire from
			core::vector3df offset = core::vector3df(6.5f, -6.5f, 30);
			core::matrix4 mat = smgr->getActiveCamera()->getAbsoluteTransformation();
			mat.transformVect(offset);
			// Fire projectile
			CGunProjectile* proj = new CGunProjectile(offset, (smgr->getActiveCamera()->getTarget() - smgr->getActiveCamera()->getAbsolutePosition()).normalize(), smgr);
			if (proj) GunProjectiles.push_back(proj);
			TimeSinceLastShot = 0;
			//Ammo--;
			TimeSinceLastRefill = 0;

			image = device->getVideoDriver()->getTexture("stuff/logos/bullet.png");
			/*for (int i = 0; i<MAX_DECALS; i++)
			{
				decals[i] = new DecalSceneNode(smgr->getRootSceneNode(),
					smgr, image, 10.2f);
				decals[i]->setLifeSpan(15);
			}*/

			if (ammo_smg > 0)
				ammo_smg--;
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

IAnimatedMeshSceneNode* Player::getNode()
{
	return node;
}

vector3df Player::getPosition()
{
	//node->updateAbsolutePosition();
	//return node->getAbsolutePosition();

	//camera->getNode()->updateAbsolutePosition();
	//return camera->getNode()->getAbsolutePosition();
	return vector3df(0,0,0);
}

vector3df Player::getDirection()
{
	return forwardDirection;
}

void Player::moveForward(f32 deltaTime)
{
	/*node->updateAbsolutePosition();
	node->setPosition(node->getAbsolutePosition() + (forwardDirection * speed * deltaTime));

	node->updateAbsolutePosition();
	forwardDirection.normalize();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());*/
}

void Player::moveBackward(f32 deltaTime)
{
	/*node->updateAbsolutePosition();
	node->setPosition(node->getAbsolutePosition() + (-1 * forwardDirection * speed * deltaTime));

	node->updateAbsolutePosition();
	forwardDirection.normalize();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
*/
}

void Player::turnLeft(f32 deltaTime)
{
	/*node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y - (0.1f * deltaTime), node->getRotation().Z));
	vector3df rotation = vector3df(0.0f, (-0.1f * deltaTime), 0.0f);
	forwardDirection = rotation.rotationToDirection(forwardDirection);
	forwardDirection.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
*/
}

void Player::turnRight(f32 deltaTime)
{
	/*node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y + (0.1f * deltaTime), node->getRotation().Z));
	vector3df rotation = vector3df(0.0f, (0.1f * deltaTime), 0.0f);
	forwardDirection = rotation.rotationToDirection(forwardDirection);
	forwardDirection.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->setPosition((-1.0f * forwardDirection * cameraDistance) + node->getAbsolutePosition());
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setPosition(vector3df(camera->getNode()->getAbsolutePosition().X, camera->getNode()->getAbsolutePosition().Y + 50, camera->getNode()->getAbsolutePosition().Z));
	camera->getNode()->updateAbsolutePosition();
	camera->getNode()->setTarget(node->getAbsolutePosition());
*/
}

void Player::strafeLeft(f32 deltaTime)
{
	/*vector3df normal = vector3df(0, 1, 0).crossProduct(forwardDirection);
	normal.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	node->setPosition(node->getAbsolutePosition() + (2.0f * speed * normal * deltaTime));
	camera->getNode()->setPosition(camera->getNode()->getAbsolutePosition() + (2.0f * normal * speed * deltaTime));

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	camera->getNode()->setTarget(node->getAbsolutePosition());*/

}

void Player::strafeRight(f32 deltaTime)
{
	/*vector3df normal = forwardDirection.crossProduct(vector3df(0, 1, 0));
	normal.normalize();

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	node->setPosition(node->getAbsolutePosition() + (speed * normal * 2.0f * deltaTime));
	camera->getNode()->setPosition(camera->getNode()->getAbsolutePosition() + (normal * speed * 2.0f * deltaTime));

	node->updateAbsolutePosition();
	camera->getNode()->updateAbsolutePosition();

	camera->getNode()->setTarget(node->getAbsolutePosition());
*/
}

bool Player::push()
{
	if ((device->getTimer()->getTime() - lastPush) > 3000.0f && mana >= PUSH_COST)
	{
		mana -= PUSH_COST;
		lastPush = device->getTimer()->getTime();
		return true;
	}
	return false;
}

void Player::teleport()
{
	if ((device->getTimer()->getTime() - lastTeleport) > 5000.0f && mana >= TELEPORT_COST)
	{
		mana -= TELEPORT_COST;
		lastTeleport = device->getTimer()->getTime();

		node->updateAbsolutePosition();
		camera->getNode()->updateAbsolutePosition();
		forwardDirection.normalize();

		node->setPosition(node->getAbsolutePosition() + (forwardDirection * 500.0f));
		camera->getNode()->setPosition(camera->getNode()->getAbsolutePosition() + (forwardDirection * 500.0f));

		node->updateAbsolutePosition();
		camera->getNode()->updateAbsolutePosition();

		camera->getNode()->setTarget(node->getAbsolutePosition());
	}
}

void Player::setIdleAnimation()
{
	if (state != State::IDLE)
	{
		node->setMD2Animation(EMAT_STAND);
		node->setAnimationSpeed(30);
		state = State::IDLE;
	}
}

void Player::setRunningAnimation()
{
	if (state != State::RUNNING)
	{
		node->setMD2Animation(EMAT_RUN);
		node->setAnimationSpeed(30);
		state = State::RUNNING;
	}
}

void Player::setAttackAnimation()
{
	node->setMD2Animation(EMAT_ATTACK);
	node->setAnimationSpeed(20);
	state = State::ATTACK;
}

PowerBall* Player::Attack()
{
	if ((device->getTimer()->getTime() - lastAttack) < 200.0f) //  || mana < POWERBALL_COST
	{
		return nullptr;
	}

	vector3df start = camera->getNode()->getPosition();
	//vector3df start = core::vector3df(6.5f, -6.5f, 30);

	vector3df end = (camera->getNode()->getTarget() - start);
	end.normalize();
	start += end*20.0f;

	end = start + (end * camera->getNode()->getFarValue());


	//vector3df direction = vector3df(0, 0, 0);// forwardDirection;
	//direction.Y = 0; // походу это координата конечной точки снаряда по Y
	//direction.normalize();

	PowerBall* powerBall = new PowerBall(smgr, driver, start, end, 1.0f);
	lastAttack = device->getTimer()->getTime();
	//mana -= 20;
	return powerBall;
}