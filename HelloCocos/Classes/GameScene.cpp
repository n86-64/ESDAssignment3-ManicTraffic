#include "GameScene.h"
USING_NS_CC;

cocos2d::Scene* RHMainMenu::createScene()
{
	return cocos2d::Scene::create();
}

bool RHMainMenu::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	return true;
}
