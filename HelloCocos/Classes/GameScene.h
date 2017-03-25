#pragma once
#include <cocos2d.h>

class RHMainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	
	// initialisation of the menu
	void initMenu();

	// event handling for the buttons.
	

	CREATE_FUNC(RHMainMenu);
};