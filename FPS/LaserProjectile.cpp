#include "LaserProjectile.h"

#define PROJECTILE_SPEED 85.0f

LaserProjectile::LaserProjectile(const vector3df& pos, const vector3df& dir, ISceneManager* smgr): GameObject(pos, PROJECTILE_SPEED, smgr) {

	direction = dir;
	prevPos = pos;
	sqDistTravelled = 0;
	sceneManager = smgr;

	// Create projectile.
	bill = smgr->addBillboardSceneNode(sceneManager->getRootSceneNode(), dimension2d<f32>(15, 15), pos, -3);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("stuff/logos/laser.bmp"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

}

LaserProjectile::~LaserProjectile() {
	remove();
}

void LaserProjectile::remove() {
	core::vector3df pos = bill->getPosition();
	bill->remove();
	bill = NULL;

	s32 frameTime = 25;
	scene::ISceneNodeAnimator* anim = NULL;

	// Create animation for explosion.
	c8 tmp[64];
	core::array<video::ITexture*> textures;
	for (s32 g = 1; g <= 4; ++g) {
		sprintf_s(tmp, "stuff/Impactb/%02d.JPG", g);
		textures.push_back(sceneManager->getVideoDriver()->getTexture(tmp));
	}
	anim = sceneManager->createTextureAnimator(textures, frameTime, false);

	// Create explosion.
	bill = sceneManager->addBillboardSceneNode(sceneManager->getRootSceneNode(), core::dimension2d<f32>(25, 25), pos, -5);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("stuff/Impactb/01.JPG"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->addAnimator(anim);
	anim->drop();

	// Create deletion animator to automatically remove the billboard.
	anim = sceneManager->createDeleteAnimator(frameTime * 6);
	bill->addAnimator(anim);
	anim->drop();
}

void LaserProjectile::update(f32 deltaTime) {

	if (bNeedsUpdate)
	{
		if (sqDistTravelled > 100000)
			bNeedsUpdate = false;
		else {
			prevPos = bill->getAbsolutePosition();
			core::vector3df distance = direction*PROJECTILE_SPEED;

			if (bill)
				bill->setPosition(prevPos + distance);

			sqDistTravelled += distance.getLengthSQ();
		}
	}
}

vector3df LaserProjectile::getPosition() {
	return bill->getPosition();
}

ISceneNode* LaserProjectile::getNode() {
	return bill;
}
