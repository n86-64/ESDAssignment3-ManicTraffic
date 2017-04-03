#include "SimpleAudioEngine.h"
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

	levelCompleationMessage = cocos2d::Label::createWithTTF("Well done you compleated the Level. \n Now move on to the next one.", "fonts/Marker Felt.ttf", 24);
	levelCompleationMessage->setPosition(Vec2(1100, 200));
	levelCompleationMessage->setVisible(false);

	nextLevelButton = cocos2d::MenuItemLabel::create(
		cocos2d::Label::createWithTTF("Next Level", "fonts/Marker Felt.ttf", 24),
		CC_CALLBACK_1(RHGameScene::onSkipLevelClicked, this)
		);

	nextLevelMenu = cocos2d::Menu::create(nextLevelButton, nullptr);
	nextLevelMenu->setPosition(Vec2(1100, 150));
	nextLevelMenu->setVisible(false);
	nextLevelMenu->setEnabled(false);

	this->addChild(timeLabel, 2);
	this->addChild(movesLabel, 2);
	this->addChild(levelCompleationMessage, 2);
	this->addChild(nextLevelMenu, 2);
}

void RHGameScene::addMove()
{
	numberOfMoves++;
}

void RHGameScene::playWinSequense()
{
	if (!levelComplete) 
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/solved.wav");
		levelComplete = true;
		totalTimeTaken += levelTime;

		// here we will show a message for a few secounds and then move then onto the next level. 
		if (levelCounter + 1 > 8)
		{
			// TODO - Display a well done and give out the results message. 
			if (numberOfSkippedLevels > 0) 
			{
				levelCompleationMessage->setString("Well Done you finished the game. \n Although you skipped " + std::to_string(numberOfSkippedLevels) + " levels."  + "\n Play again and \n see if you can do better.");
			}
			else 
			{
				levelCompleationMessage->setString("Well Done you compleated the game. \n You Compleated the game in: \n" + std::to_string(totalTimeTaken) + "\n Play again and see if you can do better.");
			}
			levelCompleationMessage->setVisible(true);

			nextLevelButton->setString("Back to Menu");
			nextLevelMenu->setVisible(true);
			nextLevelMenu->setEnabled(true);
		}
		else
		{
			levelCompleationMessage->setVisible(true);
			nextLevelMenu->setVisible(true);
			nextLevelMenu->setEnabled(true);
		}
	}
}

void RHGameScene::setLevel(std::string levelToOpen)
{
	std::string levelDifficultyString;

	levelFileSystem.openLevel(&currentLevel, levelToOpen);
	levelGrid->setLevelState((RHLevelState)currentLevel);
	levelGrid->initGrid();

	// place the level details in the corner to give information to the Player. 
	if (levelName != nullptr && levelDifficulty != nullptr) 
	{
		levelName->setString(currentLevel.getLevelName());

		switch (currentLevel.getLevelDifficulty())
		{
		case DIFFICULTY_EASY:
			levelDifficultyString = "Easy";
			break;
		case DIFFICULTY_MEDIUM:
			levelDifficultyString = "Medium";
			break;
		case DIFFICULTY_HARD:
			levelDifficultyString = "Hard";
			break;
		}


		levelDifficulty->setString("Difficulty - " + levelDifficultyString);
	}
	else 
	{
		initiliseLevelInfo();
	}


	levelCounter++;
}

void RHGameScene::update(float delta)
{
	if (!levelComplete) 
	{
		levelTime += delta;
		timeLabel->setString("Time - " + std::to_string(levelTime));
		movesLabel->setString("Moves - " + std::to_string(numberOfMoves));
	}
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
		break;
	case DIFFICULTY_MEDIUM:
		levelDifficultyString = "Medium";
		break;
	case DIFFICULTY_HARD:
		levelDifficultyString = "Hard";
		break;
	}

	levelDifficulty = cocos2d::Label::create("Difficulty - " + levelDifficultyString, "fonts/Marker Felt.ttf", 24);
	levelDifficulty->setPosition(Vec2(100, 570));
	this->addChild(levelDifficulty);
}

void RHGameScene::addButtons()
{
	// here we will add buttons onto the menu.
	auto nextLevelClicked = cocos2d::MenuItemLabel::create(
		cocos2d::Label::create("Skip Level", "fonts/arial.ttf", 20), 
		CC_CALLBACK_1(RHGameScene::onSkipLevelClicked, this)
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

void RHGameScene::onSkipLevelClicked(cocos2d::Ref* sender)
{

	// here we will add the options to allow the end user to skip the level
	if (!(levelCounter + 1 > 8)) 
	{
			// Here we will track the stats of the player.
			// including the number of moves taken and the time taken to complete the game. 

		if (!levelComplete) 
		{
			numberOfSkippedLevels++;
		}

		numberOfMoves = 0;
		levelTime = 0.0f;
		levelCompleationMessage->setVisible(false);
		nextLevelMenu->setEnabled(false);
		nextLevelMenu->setVisible(false);

		this->levelComplete = false;
		this->setLevel("level" + std::to_string(levelCounter + 1) + ".mtlf");
	}
	else 
	{
		Director::getInstance()->popScene();
	}
}

void RHGameScene::onResetLevelClicked(cocos2d::Ref* sender)
{
	// here we will reset the level and allow the user to try again. 
	numberOfMoves = 0;
	levelTime = 0.0f;
	levelGrid->resetGrid();
}
