#include "CHealthPowerupObject.h"

Player* player;

//static void healthPickupCallback(IAISensor* caller, IAIEntity* entity, E_AISENSOR_EVENT_TYPE eventType) {
//
//	switch (eventType) {
//	case EAISET_ENTER:
//		if (entity == player->getAIEntity()) {
//			// The entity which entered the AI Sensor is the player so give them some health
//			if (player) {
//				player->addHealth(25);
//				player->addAmmoMgun(25);
//				player->addAmmoMgunB(25);
//				player->addAmmoRev(6);
//				player->addAmmoRevEvo(10);
//				player->addAmmoSMG(15);
//			}
//		}
//		break;
//	case EAISET_EXIT:
//		//printf("Exit healthpup\n");
//		break;
//	}
//
//}

CHealthPowerupObject::CHealthPowerupObject(Player* plyr, scene::ISceneManager* smgr, const core::vector3df& pos) {

//	AIManager = aimgr;

	player = plyr;

	player->addHealth(25);
	player->addAmmoMgun(25);
	player->addAmmoMgunB(25);
	player->addAmmoRev(6);
	player->addAmmoRevEvo(10);
	player->addAmmoSMG(15);

	s32 h = player->getHealth();

	// Create a health pickup sensor
	//SAIEntityDesc sensorDesc;
	/*sensorDesc.Scale = core::vector3df(5, 5, 5);
	sensorDesc.Offset = core::vector3df(0, 2.5f, 0);
	sensorDesc.Name = "HealthPickupSensor";
	sensorDesc.UserData = this;*/
//	Sensor = AIManager->createEntryExitSensor(sensorDesc);
	/*if (player) {
		if (Sensor) {
			Sensor->setCallback(&healthPickupCallback);
			if (h > 0)
				Sensor->addEntity(player->getAIEntity());
			Sensor->setPosition(pos);
		}
		else printf("ERROR: Failed health pickup creation\n");
	}*/

	// Create a visual representation
	Cube = smgr->addCubeSceneNode(5);
	if (Cube) {
		Cube->setPosition(pos + core::vector3df(0, 2.5f, 0));
		Cube->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("stuff/life.jpg"));
		Cube->setMaterialFlag(video::EMF_LIGHTING, false);
	}
	else printf("ERROR: Failed cube creation\n");

	//ammo
	Cubeb = smgr->addCubeSceneNode(5);
	if (Cubeb) {
		Cubeb->setPosition(pos + core::vector3df(0, 8.5f, 0));
		Cubeb->setMaterialTexture(0, smgr->getVideoDriver()->getTexture("stuff/ammo.jpg"));
		Cubeb->setMaterialFlag(video::EMF_LIGHTING, false);
	}
	else printf("ERROR: Failed cube creation\n");

}

CHealthPowerupObject::~CHealthPowerupObject() {

	if (Cube) {
		Cube->remove();
		Cube = NULL;
	}

	if (Cubeb) {
		Cubeb->remove();
		Cubeb = NULL;
	}

	/*if (Sensor) {
		AIManager->removeAIEntity(Sensor);
		Sensor = NULL;
	}*/

}