#include "Skybox.h"

Skybox::Skybox(ISceneManager* smgr, IVideoDriver* driver){
	node = smgr->addSkyBoxSceneNode(driver->getTexture("Textures/downtron.jpg"), driver->getTexture("Textures/uptron.jpg"), driver->getTexture("Textures/lefttron.jpg"), 
		                            driver->getTexture("Textures/righttron.jpg"), driver->getTexture("Textures/fronttron.jpg"), driver->getTexture("Textures/backtron.jpg"));
	
	light = smgr->addLightSceneNode();

	SLight lightData;
	lightData.Type = ELT_DIRECTIONAL;
	lightData.CastShadows = true;
	lightData.Direction = vector3df(1, -1, 0).normalize();

	light->setLightType(ELT_DIRECTIONAL);
	light->setLightData(lightData);
	light->enableCastShadow();
}

ISceneNode* Skybox::getNode(){
	return node;
}