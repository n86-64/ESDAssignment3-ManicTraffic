/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHMainMenu.h
File Contents - class definitons for the main menu scene.

Purpose - The scene where the users game starts. Allowing them to chose ther options
        - and well play the game. 
*/

#pragma once

#include <cocos2d.h>
#include "RHScenes.h"
#include "Project\RHLevelParser.h"

class RHMainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	
	// initialisation of the menu
	void initMenuBackdropAndTitle();
	void initMusic();
	void createMenuOptions();

	// event handling for the buttons.
	void playGameClicked(cocos2d::Ref* sender);
	void createLevelClicked(cocos2d::Ref* sender);
	void openSettingsClicked(cocos2d::Ref* sender);
	void quitClicked(cocos2d::Ref* sender);

	CREATE_FUNC(RHMainMenu);

private:
	RHFileParser  levelParser;
};