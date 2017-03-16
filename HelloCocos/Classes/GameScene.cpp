#include "GameScene.h"
USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
	return cocos2d::Scene::create();
}

bool GameScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	return true;
}
