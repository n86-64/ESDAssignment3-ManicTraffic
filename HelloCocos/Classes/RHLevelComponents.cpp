#include "RHLevelComponents.h"

RHLevelState::RHLevelState()
{
}

void RHLevelState::init()
{
}

RHCar* RHLevelState::getVehicle(int vehicleIndex)
{
	return theCars[vehicleIndex];
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

void RHLevelState::reset()
{
	numberOfCars = 0;
	theCars.clear();
}


// The level data structure //
RHLevel::RHLevel()
{
	levelName = "Blankety Blank";
	author    = "KnickNAC Software";
	levelDifficulty = DIFFICULTY_NOT_SET;
}

std::string RHLevel::getLevelName()
{
	return levelName;
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

RHGameDifficulty RHLevel::getLevelDifficulty() 
{
	return levelDifficulty;
}
