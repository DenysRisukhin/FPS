#include "CGunProjectile.h"

#define PROJECTILE_SPEED 985.0f

CGunProjectile::CGunProjectile(const core::vector3df& start, const core::vector3df& end, scene::ISceneManager* smgr) : GameObject(start, PROJECTILE_SPEED, smgr) {

	Direction = end;
	PrevPos = start;
	SqDistTravelled = 0;
	SceneManager = smgr;

	// create projectile
	Bill = smgr->addBillboardSceneNode(SceneManager->getRootSceneNode(), core::dimension2d<f32>(15, 15), start, -3);
	Bill->setMaterialFlag(video::EMF_LIGHTING, false);
	Bill->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("stuff/logos/bulletflying.jpg")); 
	Bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

CGunProjectile::~CGunProjectile() {
	remove();
}

void CGunProjectile::remove() {

	core::vector3df pos = Bill->getPosition();
	Bill->remove();
	Bill = NULL;

	s32 frameTime = 25;
	scene::ISceneNodeAnimator* anim = NULL;

	// create animation for explosion
	c8 tmp[64];
	core::array<video::ITexture*> textures;
	for (s32 g = 1; g <= 6; ++g) {
		sprintf_s(tmp, "stuff/Impact/%02d.JPG", g);
		textures.push_back(SceneManager->getVideoDriver()->getTexture(tmp));
	}
	anim = SceneManager->createTextureAnimator(textures, frameTime, false);

	// create explosion
	Bill = SceneManager->addBillboardSceneNode(SceneManager->getRootSceneNode(), core::dimension2d<f32>(45, 45), pos, -5);
	Bill->setMaterialFlag(video::EMF_LIGHTING, false);
	Bill->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("stuff/Impact/01.JPG"));
	Bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	Bill->addAnimator(anim);
	anim->drop();
	// create deletion animator to automatically remove the billboard
	anim = SceneManager->createDeleteAnimator(frameTime * 6);
	Bill->addAnimator(anim);
	anim->drop();

}

void CGunProjectile::update(f32 deltaTime) {

	if (bNeedsUpdate)
	{
		if (SqDistTravelled > 100000000)
			bNeedsUpdate = false;
		else {

			PrevPos = Bill->getAbsolutePosition();

			core::vector3df distance = Direction*PROJECTILE_SPEED;

			if (Bill)
				Bill->setPosition(PrevPos + distance);

			SqDistTravelled += distance.getLengthSQ();
		}
	}

}

ISceneNode* CGunProjectile::getNode()
{
	return Bill;
}
