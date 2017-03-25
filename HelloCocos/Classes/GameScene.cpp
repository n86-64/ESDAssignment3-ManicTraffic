#include <iostream>
#include "AudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* RHMainMenu::createScene()
{
	return RHMainMenu::create();
}

bool RHMainMenu::init()
{
	if (!cocos2d::Scene::init())
	{
		MessageBoxA(NULL, "Main Scene failed to initialise. Please contact support for more information", "ManicTraffic Error", MB_OK | MB_ICONERROR);
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("manicTrafficSprites/ManicTrafficSprites.plist");
	initMenu();

	return true;
}

void RHMainMenu::initMenu() 
{
	cocos2d::Sprite* menuBackground = cocos2d::Sprite::createWithSpriteFrameName("thebigCity.jpg");
	menuBackground->setAnchorPoint(Vec2(0, 0));
	menuBackground->setPosition(Vec2(0, 0));
	menuBackground->setScale(1.4f);
	this->addChild(menuBackground, 0);

	

}