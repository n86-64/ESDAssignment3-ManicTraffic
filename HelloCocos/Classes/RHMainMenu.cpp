#include <iostream>
#include "SimpleAudioEngine.h"
#include "RHMainMenu.h"

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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("manicTrafficSprites/ManicTrafficSprites.plist");
	initMenuBackdropAndTitle();
	initMusic();
	createMenuOptions();

	return true;
}

void RHMainMenu::initMusic() 
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/backTrack.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
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

}

void RHMainMenu::createLevelClicked(cocos2d::Ref* sender)
{

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
}