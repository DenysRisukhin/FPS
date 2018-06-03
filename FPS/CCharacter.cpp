#include "CCharacter.h"
/*
#include <irrKlang.h>
using namespace irrklang;
*/

const s32 CCharacter::MAX_AMMO = 50;
const s32 CCharacter::MAX_HEALTH = 100;
const s32 CCharacter::REFILL_PERIOD = 500;


CCharacter::CCharacter(ISceneManager* smgr, s32 characterType) {

	SceneManager = smgr;
	//AIManager = desc.AIManager;
	RegenerateHealth = false;
	HalfHealth = false;

	IsBrkObj = false;
	BossHealth = false;

	CharacterType = characterType;
	if (HalfHealth)
		Health = MAX_HEALTH - 50;
	else if (IsBrkObj)
		Health = MAX_HEALTH - 85;
	else if (BossHealth)
		Health = MAX_HEALTH + 1000;
	else
		Health = MAX_HEALTH;

	Ammo = MAX_AMMO;
	ammo_rev = MAX_AMMO - 44;
	ammo_revevo = MAX_AMMO - 40;
	ammo_smg = MAX_AMMO - 35;
	ammo_mgun = MAX_AMMO - 25;
	ammo_mgunb = ammo_mgun;
	mag_rev = mag_revevo = 2;
	mag_smg = mag_mgun = mag_revevo;
	mag_mgunb = mag_smg;
	TimeSinceLastRefill = 0;
	//AIEntity = NULL;

	//engine = createIrrKlangDevice();

}

CCharacter::~CCharacter() {

	/*if (AIEntity) {
		AIManager->removeAIEntity(AIEntity);
		AIEntity = NULL;
	}*/

}

bool CCharacter::update(s32 elapsedTime) {

	if (Health <= 0) {
		if (IsBrkObj == true)
			dieWall();
		else
			die();
		return true;
	}

	if (RegenerateHealth && TimeSinceLastRefill > REFILL_PERIOD) {
		if (Health < MAX_HEALTH) ++Health;
		if (Ammo < MAX_AMMO) ++Ammo;
		TimeSinceLastRefill = 0;
	}
	else {
		TimeSinceLastRefill += elapsedTime;
	}

	if (RegenerateAmmo && TimeSinceLastRefill > REFILL_PERIOD) {
		if (Ammo < MAX_AMMO) ++Ammo;
		TimeSinceLastRefill = 0;
	}
	else {
		TimeSinceLastRefill += elapsedTime;
	}

	return false;

}

void CCharacter::die() {

#define FRAME_TIME 50
	scene::ISceneNodeAnimator* anim = NULL;

	//play sound when killed
	/*if (engine)
		engine->play2D("stuff/sound/barf.wav");*/

	/*	//start death animation -- testing....
	scene::EMD2_ANIMATION_TYPE animation;

	animation = scene::EMAT_DEATH_FALLBACK;
	*/
	// create animation for explosion
	c8 tmp[64];
	core::array<video::ITexture*> textures;
	for (s32 g = 1; g <= 11; ++g) {
		snprintf(tmp, 64, "stuff/blood/%02d.jpg", g);
		textures.push_back(SceneManager->getVideoDriver()->getTexture(tmp));
	}
	anim = SceneManager->createTextureAnimator(textures, FRAME_TIME, false);

	// create explosion
	scene::ISceneNode* bill = SceneManager->addBillboardSceneNode(NULL, core::dimension2d<f32>(70, 70), Pos + core::vector3df(0, 10, 0), -4);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("stuff/blood/01.jpg"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->addAnimator(anim);
	anim->drop();
	// create deletion animator to automatically remove the billboard
	anim = SceneManager->createDeleteAnimator(FRAME_TIME * 11);
	bill->addAnimator(anim);
	anim->drop();

}

void CCharacter::dieWall() {

#define FRAME_TIME 50
	scene::ISceneNodeAnimator* anim = NULL;

	//play sound when destroyed
	/*if (engine)
		engine->play2D("stuff/sound/impact.wav");*/

	// create animation for explosion
	c8 tmp[64];
	core::array<video::ITexture*> textures;
	for (s32 g = 1; g <= 11; ++g) {
		snprintf(tmp, 64, "stuff/Explosion/%02d.jpg", g);
		textures.push_back(SceneManager->getVideoDriver()->getTexture(tmp));
	}
	anim = SceneManager->createTextureAnimator(textures, FRAME_TIME, false);

	// create explosion
	scene::ISceneNode* bill = SceneManager->addBillboardSceneNode(NULL, core::dimension2d<f32>(70, 70), Pos + core::vector3df(0, 10, 0), -4);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("stuff/Explosion/01.jpg"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->addAnimator(anim);
	anim->drop();
	// create deletion animator to automatically remove the billboard
	anim = SceneManager->createDeleteAnimator(FRAME_TIME * 11);
	bill->addAnimator(anim);
	anim->drop();

}

//void CCharacter::drop()
//{
//	if (node)
//	{
//		node->removeAnimators();
//		node->remove();
//		node = NULL;
//		animators.clear();
//		collisions.clear();
//	}
//}