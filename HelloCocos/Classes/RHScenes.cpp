#include "RHScenes.h"

USING_NS_CC;

//---------------------------------------- The editor Scene where the levels are made ----------------------------------------------------//
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
		levelGrid->initGrid();
		this->addChild(levelGrid, 1);
	}
}




//----------------------------------------The Game Scene where the game is played----------------------------------------------------//
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

	this->scheduleUpdate();
}

void RHGameScene::initUI()
{
	timeLabel = cocos2d::Label::createWithTTF("Time - " + std::to_string(levelTime), "fonts/Marker Felt.ttf",24);
	timeLabel->setPosition(Vec2(500, 100));
	timeLabel->setColor(Color3B::BLACK);

	movesLabel = cocos2d::Label::createWithTTF("Moves - " + std::to_string(numberOfMoves), "fonts/Marker Felt.ttf", 24);
	movesLabel->setPosition(Vec2(800, 100));
	movesLabel->setColor(Color3B::BLACK);

	addButtons();

	this->addChild(timeLabel, 2);
	this->addChild(movesLabel, 2);
}

void RHGameScene::addMove()
{
	numberOfMoves++;
}

void RHGameScene::playWinSequense()
{
	cocos2d::log("Yay we win");
}

void RHGameScene::setLevel(std::string levelToOpen)
{
	levelFileSystem.openLevel(&currentLevel, levelToOpen);
	levelGrid->setLevelState((RHLevelState)currentLevel);
	levelGrid->initGrid();

	// place the level details in the corner to give information to the Player. 
	initiliseLevelInfo();


	levelCounter++;
}

void RHGameScene::update(float delta)
{
	levelTime += delta;
	timeLabel->setString("Time - " + std::to_string(levelTime));
	movesLabel->setString("Moves - " + std::to_string(numberOfMoves));
}

void RHGameScene::initiliseLevelInfo()
{
	std::string levelDifficultyString;
	levelName = cocos2d::Label::create(currentLevel.getLevelName(), "fonts/Marker Felt.ttf", 24);
	levelName->setPosition(Vec2(55, 600));
	this->addChild(levelName);

	switch (currentLevel.getLevelDifficulty()) 
	{
	case DIFFICULTY_EASY:
		levelDifficultyString = "Easy";
	case DIFFICULTY_MEDIUM:
		levelDifficultyString = "Medium";
	case DIFFICULTY_HARD:
		levelDifficultyString = "Hard";
	}

	levelDifficulty = cocos2d::Label::create("Difficulty - " + levelDifficultyString, "fonts/Marker Felt.ttf", 24);
	levelDifficulty->setPosition(Vec2(100, 570));
	this->addChild(levelDifficulty);
}

void RHGameScene::addButtons()
{
	// here we will add buttons onto the menu.
	auto nextLevelClicked = cocos2d::MenuItemLabel::create(
		cocos2d::Label::create("Next Level", "fonts/arial.ttf", 20), 
		CC_CALLBACK_1(RHGameScene::onNextLevelClicked, this)
		);

	auto resetLevelClicked = cocos2d::MenuItemLabel::create(
		cocos2d::Label::create("Reset Level", "fonts/arial.ttf", 20),
		CC_CALLBACK_1(RHGameScene::onResetLevelClicked, this)
		);

	auto gameMenu = Menu::create(nextLevelClicked, resetLevelClicked ,nullptr);
	gameMenu->setPosition(Vec2(80, 200));
	gameMenu->alignItemsVertically();
	this->addChild(gameMenu, 1);
}

void RHGameScene::onNextLevelClicked(cocos2d::Ref* sender)
{
	// here we will add the options to allow the end user to skip the level
	cocos2d::log("Hello we should load up the next level.");
}

void RHGameScene::onResetLevelClicked(cocos2d::Ref* sender)
{
	// here we will reset the level. 
	numberOfMoves = 0;
	levelTime = 0.0f;
	levelGrid->resetGrid();
}
