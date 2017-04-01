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

	// cosmetics
	void initBackgroundAndWindows();
	void initGrid();

	// TODO - add routienes to initialise the elements to allow players
	// to create there own levels. 


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
	// TODO - add routienes to initialise the game according to the 
	// level that the user is playing.

	void setLevel(std::string levelToOpen);

	void update(float delta) override;

private:
	RHLevel currentLevel;
	cocos2d::Label* timeLabel = nullptr;
	cocos2d::Label* movesLabel = nullptr;

	cocos2d::Label* levelName = nullptr;
	cocos2d::Label* levelDifficulty = nullptr;

	float levelTime = 0.0f; // time in secounds.
	int numberOfMoves = 0;
	int levelCounter = 0;

	void initiliseLevelInfo();
	void addButtons();
	void changeLevel(std::string levelToOpen); // TODO - define this function. 

	// events for the buttons. 
	void onNextLevelClicked(cocos2d::Ref* sender);
	void onResetLevelClicked(cocos2d::Ref* sender);

	CREATE_FUNC(RHGameScene)
};
