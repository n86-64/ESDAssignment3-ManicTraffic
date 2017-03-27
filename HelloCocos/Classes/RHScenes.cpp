#include "RHScenes.h"

USING_NS_CC;

// The Dev\Editor Scene. 
RHDevScene* RHDevScene::createScene()
{
	return RHDevScene::create();
}

bool RHDevScene::init()
{
	if (!cocos2d::Scene::initWithPhysics()) 
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
RHGameScene* RHGameScene::createScene()
{
	return RHGameScene::create();
}

bool RHGameScene::init()
{
	if (!cocos2d::Scene::init()) 
	{
		return false;
	}

	initBackgroundAndWindows();
	initGrid();
	initUI();

	return true;
}

void RHGameScene::initBackgroundAndWindows()
{
	auto menuBackground = cocos2d::Sprite::createWithSpriteFrameName("thebigCity.jpg");
	menuBackground->setAnchorPoint(Vec2(0, 0));
	menuBackground->setPosition(Vec2(0, 0));
	menuBackground->setScale(1.4f);
	menuBackground->setOpacity(100);
	this->addChild(menuBackground, 0);
}

void RHGameScene::initGrid()
{
	if (levelGrid == nullptr)
	{
		levelGrid = RHGameGrid::create();
		levelGrid->setPosition(Vec2(650, 350));
		this->addChild(levelGrid, 1);
	}
}

void RHGameScene::initUI()
{
	timeLabel = cocos2d::Label::createWithTTF("Time - " + std::to_string(levelTime), "fonts/Marker Felt.ttf",24);
	timeLabel->setPosition(Vec2(500, 100));
	timeLabel->setColor(Color3B::BLACK);

	movesLabel = cocos2d::Label::createWithTTF("Moves - " + std::to_string(numberOfMoves), "fonts/Marker Felt.ttf", 24);
	movesLabel->setPosition(Vec2(800, 100));
	movesLabel->setColor(Color3B::BLACK);

	this->addChild(timeLabel, 2);
	this->addChild(movesLabel, 2);
}
