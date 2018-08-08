#include "PowerBallProjectile.h"

#define PROJECTILE_SPEED 85.0f

PowerBallProjectile::PowerBallProjectile(const vector3df& start, const vector3df& end, ISceneManager* smgr) : GameObject(start, PROJECTILE_SPEED, smgr) {

	direction = end;
	prevPos = start;
	sqDistTravelled = 0;
	sceneManager = smgr;

	// Create projectile.
	bill = smgr->addBillboardSceneNode(sceneManager->getRootSceneNode(), dimension2d<f32>(150, 150), start, -3);
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("stuff/logos/powerball.bmp"));
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

}

PowerBallProjectile::~PowerBallProjectile() {
	remove();
}

void PowerBallProjectile::remove() {
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

void PowerBallProjectile::update(f32 deltaTime) {

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

vector3df PowerBallProjectile::getPosition() {
	return bill->getPosition();
}

ISceneNode* PowerBallProjectile::getNode() {
	return bill;
}
