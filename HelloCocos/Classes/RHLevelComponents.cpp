#include "RHLevelComponents.h"

RHLevelState::RHLevelState()
{
}

void RHLevelState::init()
{
}

void RHLevelState::getVehicle(int vehicleIndex)
{
}

int RHLevelState::getNumberOfVehicles()
{
	return 0;
}

void RHLevelState::addVehicle(RHCar* theCar)
{
}


// The level data structure //
RHLevel::RHLevel()
{
	levelName = "Blankety Blank";
	author    = "KnickNAC Software";
	levelDifficulty = DIFFICULTY_NOT_SET;
}
