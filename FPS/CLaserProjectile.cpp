#include "CLaserProjectile.h"

#define PROJECTILE_SPEED 85.0f

CLaserProjectile::CLaserProjectile(const core::vector3df& pos, const core::vector3df& dir, scene::ISceneManager* smgr) {

	Direction = dir;
	PrevPos = pos;
	SqDistTravelled = 0;
	SceneManager = smgr;

	// create projectile
	Bill = smgr->addBillboardSceneNode(SceneManager->getRootSceneNode(), core::dimension2d<f32>(15, 15), pos, -3);
	Bill->setMaterialFlag(video::EMF_LIGHTING, false);
	Bill->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("stuff/logos/laser.bmp"));
	Bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

}

CLaserProjectile::~CLaserProjectile() {

	remove();

}

void CLaserProjectile::remove() {

	core::vector3df pos = Bill->getPosition();
	Bill->remove();
	Bill = NULL;

	s32 frameTime = 25;
	scene::ISceneNodeAnimator* anim = NULL;

	// create animation for explosion
	c8 tmp[64];
	core::array<video::ITexture*> textures;
	for (s32 g = 1; g <= 4; ++g) {
		sprintf_s(tmp, "stuff/Impactb/%02d.JPG", g);
		textures.push_back(SceneManager->getVideoDriver()->getTexture(tmp));
	}
	anim = SceneManager->createTextureAnimator(textures, frameTime, false);

	// create explosion
	Bill = SceneManager->addBillboardSceneNode(SceneManager->getRootSceneNode(), core::dimension2d<f32>(25, 25), pos, -5);
	Bill->setMaterialFlag(video::EMF_LIGHTING, false);
	Bill->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("stuff/Impactb/01.JPG"));
	Bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	Bill->addAnimator(anim);
	anim->drop();
	// create deletion animator to automatically remove the billboard
	anim = SceneManager->createDeleteAnimator(frameTime * 6);
	Bill->addAnimator(anim);
	anim->drop();

}

bool CLaserProjectile::update() {

	if (SqDistTravelled > 100000)  // 1000000 it's time which allow a make new shoot. this parameter to influance to destance and time of shoot
		return true;

	PrevPos = Bill->getAbsolutePosition();

	core::vector3df distance = Direction*PROJECTILE_SPEED;

	if (Bill) 
		Bill->setPosition(PrevPos + distance);

	SqDistTravelled += distance.getLengthSQ();

	return false;

}
