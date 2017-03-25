#include "RHScenes.h"

USING_NS_CC;

RHDevScene* RHDevScene::createScene()
{
	return RHDevScene::create();
}

bool RHDevScene::init()
{
	if (!cocos2d::Scene::init()) 
	{
		return false;
	}

	initBackgroundAndWindows();

	return true;
}

void RHDevScene::initBackgroundAndWindows()
{
	cocos2d::Sprite* backgroundSprite = cocos2d::Sprite::createWithSpriteFrameName("thebigCity.jpg");
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	backgroundSprite->setPosition(Vec2(0, 0));
	backgroundSprite->setScale(1.4f);
	backgroundSprite->setOpacity(0.4f);
	this->addChild(backgroundSprite, 0);
}


// the game scene.
RHGameScene * RHGameScene::createScene()
{
	return RHGameScene::create();
}

bool RHGameScene::init()
{
	if (!cocos2d::Scene::init()) 
	{
		return true;
	}

	return false;
}
