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
	auto carSprite = RHCar::create(CAR_NORMAL, DIR_X_POSITIVE, false);
	this->addChild(carSprite,1);
}

