#pragma once
#include <cocos2d.h>
#include "RHScenes.h"

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

	// scenes to link to when requested by the user.
	RHGameScene* gameScene = RHGameScene::createScene();
	RHDevScene*  editorScene = RHDevScene::createScene();

	CREATE_FUNC(RHMainMenu);
};