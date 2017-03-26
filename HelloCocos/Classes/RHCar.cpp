#include "RHCar.h"

USING_NS_CC;

// The procedral placement of cars should be based on pivot points hence we can then rotate the cars:
// Base position is (120,125) and to translate the position by (70,70) when moving the car.
// based on the direction we will determine the pivot we need.
// the pivot will be located half way between the diffrence of the two cells with the car rotated according to 
// the direction. 

RHCar* RHCar::create(RHCarTypes carType, RHCarDirections carDirection, bool isMovementFree)
{
	std::string spritePath = "red2w.png";
	RHCar* car = new RHCar();

	if (car->initWithSpriteFrameName(spritePath)) 
	{
		car->setScale(0.65f);
		car->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
		car->setPosition(cocos2d::Vec2(0, 0));
		//car->setFlippedX(false);
		car->setPosition(cocos2d::Vec2(120 + 70, 125 + 70));
		car->autorelease();
		car->initCar();
		
		return car;
	}

	CC_SAFE_DELETE(car);
	return nullptr;
}

void RHCar::initCar()
{
	// here we will add evenets to move the car. 
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(RHCar::onTouchBegin, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(RHCar::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(RHCar::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

RHGridVector RHCar::getGridPosition()
{
	// return the grid position. (Useful for debug maybe)
	return RHGridVector();
}

void RHCar::setGridPosition(RHGridVector newPos)
{

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

	return true;
}

void RHCar::onTouchMoved(cocos2d::Touch* touchData, cocos2d::Event* event)
{
	if (this->isVehicleCurrentlySelected) 
	{
		this->setPosition(this->getPosition() + touchData->getDelta());
	}
}

void RHCar::onTouchEnded(cocos2d::Touch * touchData, cocos2d::Event * event)
{
	this->isVehicleCurrentlySelected = false;
}


