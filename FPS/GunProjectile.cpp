#include "GunProjectile.h"

#define PROJECTILE_SPEED 985.0f

GunProjectile::GunProjectile(const vector3df& start, const vector3df& end, ISceneManager* smgr) : GameObject(start, PROJECTILE_SPEED, smgr) {
	direction = end;
	prevPos = start;
	sqDistTravelled = 0;
	sceneManager = smgr;

	// Create projectile.
	bill = smgr->addBillboardSceneNode(sceneManager->getRootSceneNode(), dimension2d<f32>(15, 15), start, -3);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("stuff/logos/bulletflying.jpg"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

GunProjectile::~GunProjectile() {
	remove();
}

void GunProjectile::remove() {
	vector3df pos = bill->getPosition();
	bill->remove();
	bill = NULL;

	s32 frameTime = 25;
	scene::ISceneNodeAnimator* anim = NULL;

	// Create animation for explosion.
	c8 tmp[64];
	array<video::ITexture*> textures;
	for (s32 g = 1; g <= 6; ++g) {
		sprintf_s(tmp, "stuff/Impact/%02d.JPG", g);
		textures.push_back(sceneManager->getVideoDriver()->getTexture(tmp));
	}
	anim = sceneManager->createTextureAnimator(textures, frameTime, false);

	// Create explosion.
	bill = sceneManager->addBillboardSceneNode(sceneManager->getRootSceneNode(), dimension2d<f32>(45, 45), pos, -5);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("stuff/Impact/01.JPG"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	bill->addAnimator(anim);
	anim->drop();

	// Create deletion animator to automatically remove the billboard.
	anim = sceneManager->createDeleteAnimator(frameTime * 6);
	bill->addAnimator(anim);
	anim->drop();
}

void GunProjectile::update(f32 deltaTime) {
	if (bNeedsUpdate)
	{
		if (sqDistTravelled > 100000000)
			bNeedsUpdate = false;
		else {
			prevPos = bill->getAbsolutePosition();
			vector3df distance = direction*PROJECTILE_SPEED;

			if (bill)
				bill->setPosition(prevPos + distance);

			sqDistTravelled += distance.getLengthSQ();
		}
	}
}

ISceneNode* GunProjectile::getNode() {
	return bill;
}

inline vector3df GunProjectile::getPosition() {
	return bill->getPosition();
}
