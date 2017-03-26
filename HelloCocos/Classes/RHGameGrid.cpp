#include "RHGameGrid.h"
#include "RHCar.h"

RHGameGrid* RHGameGrid::create()
{
	RHGameGrid* grid = new RHGameGrid();
	if (grid->initWithSpriteFrameName("rush_hour_grid.gif")) 
	{
		grid->autorelease();
		grid->initGrid();

		return grid;
	}

	CC_SAFE_DELETE(grid);
	return NULL;
}

void RHGameGrid::initGrid()
{
	// here based on the level data we will initialise a grid accordingly. 
	auto carSprite = RHCar::create(CAR_NORMAL, DIR_X_POSITIVE, false);
	auto carSprite2 = RHCar::create(CAR_NORMAL, DIR_X_POSITIVE, false);
	carSprite2->setPosition(cocos2d::Vec2(120, 125));
	this->addChild(carSprite,1);
	this->addChild(carSprite2, 1);
}

