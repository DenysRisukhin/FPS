#include "PowerBallEnemy.h"


//PowerBallEnemy::PowerBallEnemy(ISceneManager* smgr, IVideoDriver* driver, vector3df start, vector3df end, f32 speed) : PowerBall(smgr, driver, start, end, speed)
//{
//	node->setMaterialTexture(0, driver->getTexture("Textures/powerballenemy.bmp"));
//}

PowerBallEnemy::PowerBallEnemy(ISceneManager* manager, IVideoDriver* driver, vector3df start, vector3df end, f32 ballSpeed) : GameObject(start, ballSpeed, manager), direction(0)
{
	node = smgr->addBillboardSceneNode();
	node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	node->setMaterialTexture(0, driver->getTexture("Textures/powerballenemy.bmp"));
	node->setMaterialFlag(video::EMF_LIGHTING, false);
	node->setSize(core::dimension2d<f32>(20.0f, 20.0f));
	//node->setPosition(vector3df(start.X - 5.0f, start.Y + 20.0f, start.Z));
	node->setPosition(start);

	f32 length = (f32)(end - start).getLength();
	const f32 speed = 5.8f;
	u32 time = (u32)(length / speed);

	ISceneNodeAnimator* anim = 0;

	// set flight line

	anim = smgr->createFlyStraightAnimator(start, end, time);
	node->addAnimator(anim);
	anim->drop();

	//snprintf(buf, 64, "bullet: %s on %.1f,%1.f,%1.f",
	//	imp.when ? "hit" : "nohit", end.X, end.Y, end.Z);
	//node->setName(buf);


	anim = smgr->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();
}

void PowerBallEnemy::update(f32 deltaTime)
{
	if (bNeedsUpdate)
	{
		direction.normalize();
		node->updateAbsolutePosition();
		node->setPosition(node->getAbsolutePosition() + (speed * 0 * deltaTime));
		node->updateAbsolutePosition();

		if ((node->getAbsolutePosition() - origPosition).getLengthSQ() > 1000000.0f)
		{
			bNeedsUpdate = false;
		}
	}
}

ISceneNode* PowerBallEnemy::getNode()
{
	return node;
}
