#include <limits>

#include "RHCar.h"
#include "RHGameGrid.h"

USING_NS_CC;

// The procedral placement of cars should be based on pivot points hence we can then rotate the cars:
// Base position is (120,125) and to translate the position by (70,72 (Due to collision issues)) when moving the car.
// based on the direction we will determine the pivot we need.
// the pivot will be located half way between the diffrence of the two cells with the car rotated according to 
// the direction. 

// Nathan Butt (n86) - All vehicles will be placed in a positiove direction all the time. (due to certain bugs which I may fix I may not.)

RHCar* RHCar::create(RHCarTypes carType, RHCarDirections carDirection, bool isMovementFree, RHGridVector carPosition)
{
	std::string spritePath;
	RHCar* car = new RHCar();
	Vec2 offset;
	Vec2 baseVector(120,125);
	Vec2 moveDelta(70, 72);
	Vec2 moveMultiplier(2,1);
	offset.y = 0;

	// determine the sprite that we need to set. 
	spritePath = car->getSpritePath(carType);

	if (car->initWithSpriteFrameName(spritePath)) 
	{
		car->setScale(0.61f);
		car->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

		if (carType == CAR_LORRY) 
		{
			car->setRotation(90.0f);
			car->setGridLimitsX(RHGridVector(370, 150));
			offset.x = -35.0f;
		}
		else 
		{
			if (carType != CAR_TARGET) 
			{
				car->setGridLimitsX(RHGridVector(409, 117));
			}
			else 
			{
				car->setGridLimitsX(RHGridVector(609, 117));
			}
		}

		car->setVehicleType(carType);
		car->setGridPosition(carPosition);
		car->setVehicleDirection(carDirection);

		switch (carDirection) 
		{
		case DIR_X_NEGATIVE:
			car->setRotation(car->getRotation() + 180.0f);
			offset.x = 55.0f;
			break;
		case DIR_Y_POSITIVE:
			car->setRotation(car->getRotation() - 90.0f);
			baseVector = Vec2(80, 160);
			moveDelta = Vec2(72, 72);
			moveMultiplier = Vec2(1, 1);
			car->setGridLimitsX(RHGridVector(409, 79));
			car->setGridLimitsY(RHGridVector(455, 160));
			offset.y -= 72;

			if (carType == CAR_LORRY)
			{
				offset.x += 35.0f;
				offset.y -= 38.0f;
				car->setGridLimitsY(RHGridVector(420, 190));
			}

			break;
		default:
			break;
		}

		// place the cars and lorries here after calculating the base coordinates. 
		if (carPosition.getX() != 1)
		{
			car->setPosition(Vec2(baseVector.x + ((car->getGridPosition().getX() - moveMultiplier.x) * moveDelta.x) + offset.x, baseVector.y + ((car->getGridPosition().getY() - 1) * moveDelta.y) + offset.y));
		}
		else
		{
			car->setPosition(Vec2(baseVector.x + ((car->getGridPosition().getX() - moveMultiplier.y) * moveDelta.x) + offset.x, baseVector.y + ((car->getGridPosition().getY() - 1) * moveDelta.y) + offset.y));
		}
 
		car->setOriginalPosition(car->getPosition());
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

void RHCar::setGridLimitsX(RHGridVector gridLimit)
{
	gridLimitsX = gridLimit;
}

void RHCar::setGridLimitsY(RHGridVector gridLimit)
{
	gradLimitsY = gridLimit;
}

void RHCar::setOriginalPosition(Vec2 pos)
{
	originalPosition = pos;
}

void RHCar::resetCarPosition()
{
	//Vec2 offset;
	//Vec2 baseVector(120, 125);
	//Vec2 moveDelta(70, 72);
	//Vec2 moveMultiplier(2, 1);

	//if (vehicleType == CAR_LORRY) 
	//{
	//	offset.x += 35.0f;
	//	offset.y -= 38.0f;
	//}

	//switch (vehicleDirection)
	//{
	//case DIR_X_NEGATIVE:
	//	this->setRotation(this->getRotation() + 180.0f);
	//	offset.x = 55.0f;
	//	break;
	//case DIR_Y_POSITIVE:
	//	this->setRotation(this->getRotation() - 90.0f);
	//	baseVector = Vec2(80, 160);
	//	moveDelta = Vec2(72, 72);
	//	moveMultiplier = Vec2(1, 1);
	//	this->setGridLimitsX(RHGridVector(409, 79));
	//	this->setGridLimitsY(RHGridVector(455, 160));
	//	offset.y -= 72;

	//	if (vehicleType == CAR_LORRY)
	//	{
	//		offset.x += 35.0f;
	//		offset.y -= 38.0f;
	//		this->setGridLimitsY(RHGridVector(420, 190));
	//	}

	//	break;
	//default:
	//	break;
	//}

	//// place the cars and lorries here after calculating the base coordinates. 
	//if (gridPosition.getX() != 1)
	//{
	//	this->setPosition(Vec2(baseVector.x + ((this->getGridPosition().getX() - moveMultiplier.x) * moveDelta.x) + offset.x, baseVector.y + ((this->getGridPosition().getY() - 1) * moveDelta.y) + offset.y));
	//}
	//else
	//{
	//	this->setPosition(Vec2(baseVector.x + ((this->getGridPosition().getX() - moveMultiplier.y) * moveDelta.x) + offset.x, baseVector.y + ((this->getGridPosition().getY() - 1) * moveDelta.y) + offset.y));
	//}
	this->setPosition(originalPosition);
}

// used to select and move the cars. 
bool RHCar::onTouchBegin(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	// here we can select cars. 
	// yes we will need to transform the cordinates into the gridspace before we perform this test  
	Point location = touchData->getLocation();

	// correct the location value so that it falls within the rectangle.
	auto height = this->convertToNodeSpace(location);
	cocos2d::Rect r = cocos2d::Rect(0,0, this->getContentSize().width, this->getContentSize().height);

	if (r.containsPoint(height)) 
	{
		this->isVehicleCurrentlySelected = true;
		return true;
	}

	return true;
}

void RHCar::onTouchMoved(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	Point location = touchData->getLocation();

	// correct the location value so that it falls within the rectangle.
	auto height = this->convertToNodeSpace(location);
	cocos2d::Rect r = cocos2d::Rect(0, 0, this->getContentSize().width, this->getContentSize().height);

	if (this->isVehicleCurrentlySelected) 
	{
		Vec2 mouseDelta = touchData->getDelta();

		// use this for motion instead. placement will use grid position. (treat getDelta aas a velocity and use a velocity function
		// to prevent collisions).

		// here we will add the code for moving the vehicles. 
		if(isOutsideGridLimits(vehicleDirection, mouseDelta))
		{
			if (this->vehicleDirection == DIR_X_POSITIVE || this->vehicleDirection == DIR_X_NEGATIVE)
			{
				this->setPositionX(this->getPositionX() + mouseDelta.x);
			}
			else
			{
				this->setPositionY(this->getPositionY() + mouseDelta.y);
			}

			// cocos2d::log("Position - x = %f, y = %f", this->getPositionX(), this->getPositionY());
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
		switch (rand() % 2) 
		{
		case 0:
			carColour = "purple3h.png";
			break;
		case 1:
			carColour = "yellow3h.png";
			break;
		}
		return carColour;
	}
}

bool RHCar::isOutsideGridLimits(int axis, cocos2d::Vec2 mouseDelta)
{
	switch (axis) 
	{
	case 1:
		return (!(this->getPositionX() + mouseDelta.x > gridLimitsX.getX())) && (!(this->getPositionX() + mouseDelta.x < gridLimitsX.getY()));
	case 2:
		return (!(this->getPositionY() + mouseDelta.y > gradLimitsY.getX())) && (!(this->getPositionY() + mouseDelta.y < gradLimitsY.getY()));
	}

	return true;
}

RHCarDirections RHCar::getVehicleDirection() 
{
	return vehicleDirection;
}

RHCarTypes RHCar::getVehicleType()
{
	return vehicleType;
}
