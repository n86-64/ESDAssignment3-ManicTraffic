#include "RHCar.h"


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
		
		return car;
	}

	CC_SAFE_DELETE(car);
	return nullptr;
}
