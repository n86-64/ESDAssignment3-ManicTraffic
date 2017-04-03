/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHScenes.h
File Contents - class defincitons for the various 'in-game' scenes.  

Purpose - Contains the scenes which the player will be active in when playing the game. 
*/

#pragma once
#include "RHBaseScene.h"


// the scene where players can create there own levels. 
class RHDevScene : public RHBaseScene {
public:
	static RHDevScene* createScene();

	bool init() override;

	void initBackgroundAndWindows();
	void initGrid();



	CREATE_FUNC(RHDevScene)
};



// the scene where players play the levels and also test the levels. 
class RHGameScene : public RHBaseScene {
public:
	static RHGameScene* createScene();

	bool init() override;

	void initBackgroundAndWindows();
	void initGrid();
	void initUI();

	void addMove();
	void playWinSequense();
	void setLevel(std::string levelToOpen);



	void update(float delta) override;

private:
	RHLevel currentLevel;
	cocos2d::Label* timeLabel = nullptr;
	cocos2d::Label* movesLabel = nullptr;

	cocos2d::Label* levelName = nullptr;
	cocos2d::Label* levelDifficulty = nullptr;

	cocos2d::Label* levelCompleationMessage = nullptr;
	cocos2d::MenuItemLabel* nextLevelButton = nullptr;
	cocos2d::Menu* nextLevelMenu = nullptr;

	float levelTime = 0.0f; 
	int numberOfMoves = 0;
	int levelCounter = 0;

	// game stats
	float totalTimeTaken = 0.0f;
	int numberOfSkippedLevels = 0;

	bool levelComplete = false;

	void initiliseLevelInfo();
	void addButtons();

	void onSkipLevelClicked(cocos2d::Ref* sender);
	void onResetLevelClicked(cocos2d::Ref* sender);

	CREATE_FUNC(RHGameScene)
};
