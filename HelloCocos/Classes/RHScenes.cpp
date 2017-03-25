#include "RHScenes.h"

USING_NS_CC;

// The Dev Scene. 
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
	initGrid();

	return true;
}

void RHDevScene::initBackgroundAndWindows()
{
	auto menuBackground = cocos2d::Sprite::createWithSpriteFrameName("thebigCity.jpg");
	menuBackground->setAnchorPoint(Vec2(0, 0));
	menuBackground->setPosition(Vec2(0, 0));
	menuBackground->setScale(1.4f);
	menuBackground->setOpacity(100);
	this->addChild(menuBackground, 0);
}

void RHDevScene::initGrid()
{
	if (levelGrid == nullptr) 
	{
		    levelGrid = RHGameGrid::create();
			levelGrid->setPosition(Vec2(650, 350));
			this->addChild(levelGrid, 1);
	}
}




// The Game Scene.
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
