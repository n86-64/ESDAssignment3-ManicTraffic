#include "RHScenes.h"
#include "RHGameGrid.h"

USING_NS_CC;

RHGameGrid* RHGameGrid::create()
{
	RHGameGrid* grid = new RHGameGrid();
	if (grid->initWithSpriteFrameName("rush_hour_grid.gif")) 
	{
		grid->autorelease();

		return grid;
	}

	CC_SAFE_DELETE(grid);
	return NULL;
}

void RHGameGrid::initGrid()
{
	// check to see if we can do collision here
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	auto listener2 = cocos2d::EventListenerKeyboard::create();
	listener->onTouchBegan = CC_CALLBACK_2(RHGameGrid::onTouchBegin, this);
	listener->onTouchMoved = CC_CALLBACK_2(RHGameGrid::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(RHGameGrid::onTouchEnded, this);
	listener2->onKeyPressed = CC_CALLBACK_2(RHGameGrid::onKeyBoardPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	// here based on the level data we will initialise a grid accordingly. 
	// time to initialise the grid using the algorithm. 
	for (int i = 0; i < theState.getNumberOfVehicles(); i++) 
	{
		this->addChild(theState.getVehicle(i), 1);
	}




	/*auto carSprite = RHCar::create(CAR_NORMAL, DIR_X_POSITIVE, false,RHGridVector(0,0));
	auto carSprite2 = RHCar::create(CAR_NORMAL, DIR_X_POSITIVE, false, RHGridVector(0,0));
	carSprite2->setPosition(cocos2d::Vec2(120, 125));
	this->addChild(carSprite,  1);
	this->addChild(carSprite2, 1);*/
}

bool RHGameGrid::onTouchBegin(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	// get the sprite that we are moving if any and store in a buffer. 
	Vec2 ptrPosition = touchData->getLocation();
	ptrPosition = this->convertToNodeSpace(ptrPosition);

	for (auto i : this->getChildren()) 
	{
		if (i->getBoundingBox().containsPoint(ptrPosition)) 
		{
			selectedCar = dynamic_cast<RHCar*>(i);
			cocos2d::log("Yay its detecting that we have selected a car");
		}
	}

	cocos2d::log("Hello world this works");
	return true;
}

void RHGameGrid::onTouchMoved(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	Vec2 mouseDelta = touchData->getDelta();

	// here we will check to see if it collides with any objects. 
	for (auto i : this->getChildren()) 
	{
		if (selectedCar != nullptr) 
		{
			if (!(i->getBoundingBox().equals(selectedCar->getBoundingBox())))
			{
				// TODO - use precalculated collision rather than rectangle intersection.
				// This is good for now but will need to be changed.
				// That is check before we move. 
				if (i->getBoundingBox().intersectsRect(selectedCar->getBoundingBox()))
				{
					// stop the vehicle from moving.
					selectedCar->setPositionX(selectedCar->getPositionX() - ((mouseDelta.x / abs(mouseDelta.x)) * 15));
					selectedCar->canMove = false;
					cocos2d::log("Yay we can now detect collisions and change the position accordingly");
				}
				else
				{
					selectedCar->canMove = true;
				}
			}
		}
	}
}

void RHGameGrid::onTouchEnded(cocos2d::Touch* touchData, cocos2d::Event* event) 
{
	RHGameScene* localPtr;
	if (selectedCar != nullptr) 
	{
		localPtr = dynamic_cast<RHGameScene*>(this->getParent());

		if (localPtr != nullptr) 
		{
			localPtr->addMove();
			localPtr = nullptr;
		}

		selectedCar = nullptr;
	}
}

void RHGameGrid::onKeyBoardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) 
	{
		Director::getInstance()->popScene();
	}
}

void RHGameGrid::setLevelState(RHLevelState levelState) 
{
	theState = levelState;
}