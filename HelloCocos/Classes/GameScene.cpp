#include <iostream>
#include "SimpleAudioEngine.h"
#include "GameScene.h"

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
	playGameLabel->enableOutline(Color4B::BLACK, 4);
	MenuItemLabel* playGameItem = MenuItemLabel::create(playGameLabel, CC_CALLBACK_1(RHMainMenu::playGameClicked, this));

	Menu* theMenu = Menu::createWithItem(playGameItem);
	theMenu->setPosition(Vec2(50, 400));
	theMenu->alignItemsVertically();
	this->addChild(theMenu, 1);
}

void RHMainMenu::playGameClicked(cocos2d::Ref* sender)
{

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