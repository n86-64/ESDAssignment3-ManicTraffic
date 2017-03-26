#include "RHCar.h"

RHCar* RHCar::create(RHCarTypes carType, RHCarDirections carDirection, bool isMovementFree)
{
	std::string spritePath = "red2w.png";
	RHCar* car = new RHCar();

	if (car->initWithSpriteFrameName(spritePath)) 
	{
		car->setAnchorPoint(cocos2d::Vec2(1, 0));
		car->setScale(0.65f);
		car->setPosition(cocos2d::Vec2(190, 90));
		car->autorelease();
		
		return car;
	}

	CC_SAFE_DELETE(car);
	return nullptr;
}
