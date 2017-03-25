#include "RHGameGrid.h"

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