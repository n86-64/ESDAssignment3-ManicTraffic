#include <iostream>
#include "SimpleAudioEngine.h"
#include "RHMainMenu.h"
#include "RHGameGrid.h"

USING_NS_CC;

cocos2d::Scene* RHMainMenu::createScene()
{
	return RHMainMenu::create();
}

bool RHMainMenu::init()
{
	if (!cocos2d::Scene::init())
	{
		MessageBoxA(NULL, "Main Scene failed to initialise. Please contact support for more information", "ManicTraffic Error", MB_OK | MB_ICONERROR);
		return false;
	}

	initMenuBackdropAndTitle();
	initMusic();
	createMenuOptions();
	

	return true;
}

void RHMainMenu::initMusic() 
{
	// consider using audio engine instead of simpleaudioengine. 
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/backTrack.mp3");
}

void RHMainMenu::createMenuOptions()
{
	cocos2d::Label* playGameLabel = Label::createWithTTF("Play", "fonts/arial.ttf", 30);
	cocos2d::Label* createLevelsLabel = Label::createWithTTF("Create", "fonts/arial.ttf", 30);
	cocos2d::Label* openSettingsLabel = Label::createWithTTF("Settings", "fonts/arial.ttf", 30);
	cocos2d::Label* quitLabel = Label::createWithTTF("Exit", "fonts/arial.ttf", 30);

	playGameLabel->enableOutline(Color4B::BLACK, 4);
	createLevelsLabel->enableOutline(Color4B::BLACK, 4);
	openSettingsLabel->enableOutline(Color4B::BLACK, 4);
	quitLabel->enableOutline(Color4B::BLACK, 4);

	MenuItemLabel* playGameItem = MenuItemLabel::create(playGameLabel, CC_CALLBACK_1(RHMainMenu::playGameClicked, this));
	MenuItemLabel* createLevelsItem = MenuItemLabel::create(createLevelsLabel, CC_CALLBACK_1(RHMainMenu::createLevelClicked, this));
	MenuItemLabel* openSettingsItem = MenuItemLabel::create(openSettingsLabel, CC_CALLBACK_1(RHMainMenu::openSettingsClicked, this));
	MenuItemLabel* quitItem = MenuItemLabel::create(quitLabel, CC_CALLBACK_1(RHMainMenu::quitClicked, this));

	Menu* theMenu = Menu::create(playGameItem, createLevelsItem, openSettingsItem ,quitItem, nullptr);
	theMenu->setPosition(Vec2(80, 400));
	theMenu->alignItemsVerticallyWithPadding(0.0f);
	this->addChild(theMenu, 1);
}

void RHMainMenu::playGameClicked(cocos2d::Ref* sender)
{
	// here we will open the first level and then we will allow the user to skip levels if they cant solve it and move the user on to another level if nessecery. 

	RHGameScene* gameScene = RHGameScene::createScene();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	gameScene->setLevel("level1.mtlf");
	Director::getInstance()->pushScene(TransitionFade::create(0.5, gameScene));
}

void RHMainMenu::createLevelClicked(cocos2d::Ref* sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->pushScene(TransitionFade::create(0.5,(cocos2d::Scene*)RHDevScene::createScene()));
}

void RHMainMenu::openSettingsClicked(cocos2d::Ref* sender)
{

}

void RHMainMenu::quitClicked(cocos2d::Ref* sender)
{
	Director::getInstance()->end();
}

void RHMainMenu::initMenuBackdropAndTitle() 
{
	cocos2d::Sprite* menuBackground = cocos2d::Sprite::createWithSpriteFrameName("thebigCity.jpg");
	menuBackground->setAnchorPoint(Vec2(0, 0));
	menuBackground->setPosition(Vec2(0, 0));
	menuBackground->setScale(1.4f);
	this->addChild(menuBackground, 0);

	cocos2d::Label* title = Label::createWithTTF("Manic Traffic", "fonts/TRAFFIC5.ttf", 80);
	title->setPosition(Vec2(320, 675));
	title->enableItalics();
	title->setColor(cocos2d::Color3B::BLACK);
	title->enableShadow();
	this->addChild(title, 1);

	cocos2d::Label* copyrightTag = Label::createWithTTF("(C) KnickNAC 2017 (Alpha build do not distribute)", "fonts/Burbin Casual NC.ttf", 20);
	copyrightTag->setPosition(Vec2(1000, 50));
	copyrightTag->setColor(cocos2d::Color3B::BLACK);
	this->addChild(copyrightTag, 1);
}