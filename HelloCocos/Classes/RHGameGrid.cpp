#include "RHScenes.h"
#include "RHGameGrid.h"

USING_NS_CC;

// Known shippable (consider fixing but dont worry too much however we may need to change the collision system) 
// - collision system is slightly broken hence we may have to do a point based collision system rather than (collision fixed - simple inverse of the users delta). 

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
	// here based on the level data we will initialise a grid accordingly. 
	// time to initialise the grid using the algorithm. 
	// events only initialised if we are creating grid for the first time. 
	if (this->getChildrenCount() != 0) 
	{
		// TODO check if in our list we will need to delete all the cars manually or wheteher the system will handle it when we reset the level state. 
		this->removeAllChildren();
	}
	else 
	{
		srand(time(NULL));
		// check to see if we can do collision here
		auto listener = cocos2d::EventListenerTouchOneByOne::create();
		auto listener2 = cocos2d::EventListenerKeyboard::create();
		listener->onTouchBegan = CC_CALLBACK_2(RHGameGrid::onTouchBegin, this);
		listener->onTouchMoved = CC_CALLBACK_2(RHGameGrid::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(RHGameGrid::onTouchEnded, this);
		listener2->onKeyPressed = CC_CALLBACK_2(RHGameGrid::onKeyBoardPressed, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	}

	for (int i = 0; i < theState.getNumberOfVehicles(); i++)
	{
		this->addChild(theState.getVehicle(i), 1);
	}
}

void RHGameGrid::resetGrid()
{
	// here we will place the vehicles according to there grid position. 
	RHCar* allCars;
	for (auto i : this->getChildren()) 
	{
		allCars = static_cast<RHCar*>(i);
		if (allCars != nullptr) 
		{
			allCars->resetCarPosition();
		}
	}
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
	RHGameScene* currentScene = nullptr;

	// here we will check to see if it collides with any objects. 
	for (auto i : this->getChildren()) 
	{
		if (selectedCar != nullptr) 
		{
			if (!(i->getBoundingBox().equals(selectedCar->getBoundingBox())))
			{
				selectedCar->hasMoved = true;
				if (i->getBoundingBox().intersectsRect(selectedCar->getBoundingBox()))
				{
					// stop the vehicle from moving.
					if (selectedCar->getVehicleDirection() == DIR_X_POSITIVE) 
					{
						selectedCar->setPositionX(selectedCar->getPositionX() - mouseDelta.x);
					}
					else 
					{
						selectedCar->setPositionY(selectedCar->getPositionY() - mouseDelta.y);
					}
					// selectedCar->canMove = false;
				}
				else if(selectedCar->getPositionX() > 440.0f && (selectedCar->getVehicleType() == CAR_TARGET)) 
				{
					currentScene = static_cast<RHGameScene*>(this->getParent());
					if (currentScene != nullptr) 
					{
						currentScene->playWinSequense();
						currentScene = nullptr;
					}

					cocos2d::log("Add logic for the win here.");
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
	if (selectedCar != nullptr && selectedCar->hasMoved) 
	{
		localPtr = dynamic_cast<RHGameScene*>(this->getParent());

		if (localPtr != nullptr) 
		{
			localPtr->addMove();
			localPtr = nullptr;
		}

		selectedCar->hasMoved = false;
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