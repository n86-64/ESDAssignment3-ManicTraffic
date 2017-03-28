#include <limits>

#include "RHCar.h"
#include "RHGameGrid.h"

USING_NS_CC;

// The procedral placement of cars should be based on pivot points hence we can then rotate the cars:
// Base position is (120,125) and to translate the position by (70,70) when moving the car.
// based on the direction we will determine the pivot we need.
// the pivot will be located half way between the diffrence of the two cells with the car rotated according to 
// the direction. 

RHCar* RHCar::create(RHCarTypes carType, RHCarDirections carDirection, bool isMovementFree, RHGridVector carPosition)
{
	std::string spritePath = "red2w.png";
	RHCar* car = new RHCar();

	// determine the sprite that we need to set. 
	spritePath = car->getSpritePath(carType);

	if (car->initWithSpriteFrameName(spritePath)) 
	{
		car->setScale(0.65f);
		car->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
		car->setPosition(cocos2d::Vec2(0, 0));

		if (carType == CAR_LORRY) 
		{
			car->setRotation(90.0f);
		}

		car->setGridPosition(carPosition);

		//car->setFlippedX(false);
		//car->setPosition(cocos2d::Vec2(120 + 210, 125));
		//car->gridPosition.setXY(1, 3);

		// determine the sprite and set the position. 
		switch (carDirection) 
		{
		case DIR_X_NEGATIVE:
			car->setRotation(car->getRotation() + 180.0f);
			break;
		default:
			break;
		}

		// place the cars and lorries here. 
		if (carPosition.getX() != 1) 
		{
			car->setPosition(Vec2(120 + ((car->getGridPosition().getX() - 2) * 70), 125 + ((car->getGridPosition().getY() - 1) * 72)));
		}
		else 
		{
			car->setPosition(Vec2(120 + ((car->getGridPosition().getX() - 1) * 70), 125 + ((car->getGridPosition().getY() - 1) * 72)));
		}


		car->autorelease();
		car->initCar();
		
		return car;
	}

	CC_SAFE_DELETE(car);
	return nullptr;
}

void RHCar::initCar()
{
	// here we will add evenets to move the car according to the cars grid position. 
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(RHCar::onTouchBegin, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(RHCar::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(RHCar::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

RHGridVector RHCar::getGridPosition()
{
	// return the grid position. (Useful for debug maybe)
	return gridPosition;
}

void RHCar::setGridPosition(RHGridVector newPos)
{
	this->gridPosition = newPos;
}

void RHCar::setVehicleType(RHCarTypes carType)
{
	vehicleType = carType;
}

void RHCar::setVehicleDirection(RHCarDirections carDirection)
{
	vehicleDirection = carDirection;
}

// allows us to select and move objects. 
bool RHCar::onTouchBegin(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	// here we can select cars. 
	// yes we will need to transform the cordinates into the gridspace before we perform this test  
	Point location = touchData->getLocation();

	// correct the location value so that it falls within the rectangle.
	auto height = this->convertToNodeSpace(location);
	cocos2d::Rect r = cocos2d::Rect(0,0, this->getContentSize().width, this->getContentSize().height);
	//cocos2d::Rect r = this->getBoundingBox();

	if (r.containsPoint(height)) 
	{
		this->isVehicleCurrentlySelected = true;
		cocos2d::log("YAY I work");
		return true;
	}

	cocos2d::log("coordinate of object - x = %f y = %f ", this->getPosition().x, this->getPositionY());
	return true;
}

void RHCar::onTouchMoved(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	Point location = touchData->getLocation();

	// correct the location value so that it falls within the rectangle.
	auto height = this->convertToNodeSpace(location);
	cocos2d::Rect r = cocos2d::Rect(0, 0, this->getContentSize().width, this->getContentSize().height);

	if (this->isVehicleCurrentlySelected && r.containsPoint(height)) 
	{
		Vec2 mouseDelta = touchData->getDelta();

		// use this for motion instead. placement will use grid position. (treat getDelta aas a velocity and use a velocity function
		// to prevent collisions).

		// here we will add the code for moving the vehicles. 


		if (canMove) 
		{
			if ((!((this->getPositionX() + mouseDelta.x) > 408.5f)) && (!((this->getPositionX() + mouseDelta.x) < 117.0f)))
			{
				this->setPositionX(this->getPositionX() + mouseDelta.x);
			}
		}
	}
}

void RHCar::onTouchEnded(cocos2d::Touch * touchData, cocos2d::Event * event)
{
	// todo - add code that will snap the vehicle to the nearest position when in edit mode. 
	this->isVehicleCurrentlySelected = false;
}

std::string RHCar::getSpritePath(RHCarTypes carType)
{ 
	std::string carColour;
	switch (carType) 
	{
	case CAR_TARGET:
		return "red2w.png";
	case CAR_NORMAL:
		switch (rand() % 2) 
		{
		case 0:
			carColour = "black2w.png";
			break;
		case 1:
			carColour = "blue2w.png";
			break;
		}
		return carColour;
	case CAR_LORRY:
		return "purple3h.png";
	}
}

//bool RHCar::isGoingToCollide(Vec2 mouseDelta)
//{
//	Vec2 newPosition = Vec2(this->getPositionX() + mouseDelta.x, this->getPositionY());
//
//	auto height = this->convertToNodeSpace(newPosition);
//	cocos2d::Rect r = cocos2d::Rect(0, 0, this->getContentSize().width, this->getContentSize().height);
//
//	cocos2d::Rect collisionRect;
//
//	if (RHGameGrid* theGrid = (RHGameGrid*)this->getParent())
//	{
//		for (auto i : theGrid->getChildren()) 
//		{
//			collisionRect = cocos2d::Rect(i->getPosition().x - (i->getContentSize().width/2), i->getPosition().y - (i->getContentSize().height / 2), i->getContentSize().width, i->getContentSize().height);
//
//			if (!collisionRect.equals(r)) 
//			{
//				if (collisionRect.containsPoint(height)) 
//				{
//					return true;
//				}
//			}
//		}
//	}
//
//	return false;
//}


