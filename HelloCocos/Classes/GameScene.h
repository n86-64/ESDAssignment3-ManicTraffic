#pragma once
#include <cocos2d.h>

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

	CREATE_FUNC(RHMainMenu);
};