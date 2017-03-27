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
	return numberOfCars;
}

void RHLevelState::addVehicle(RHCar* theCar)
{
	// shouldnt cause a memory leak as the same address is passed through. 
	theCars.push_back(theCar);
	numberOfCars++;
}


// The level data structure //
RHLevel::RHLevel()
{
	levelName = "Blankety Blank";
	author    = "KnickNAC Software";
	levelDifficulty = DIFFICULTY_NOT_SET;
}

void RHLevel::setLevelName(std::string newName)
{
	levelName = newName;
}

void RHLevel::setAuthor(std::string newAuthor)
{
	author = newAuthor;
}

void RHLevel::setLevelDifficulty(RHGameDifficulty difficulty) 
{
	levelDifficulty = difficulty;
}
