#pragma once
#include <cocos2d.h>

class RHMainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	
	CREATE_FUNC(RHMainMenu);
};