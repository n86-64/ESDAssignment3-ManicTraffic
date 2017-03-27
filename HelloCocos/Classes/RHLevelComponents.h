/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name  - RHLevelComponents.h
File Contents - Level and LevelState class Definitions.

Purpose - The level data structure which both tracks the level state 
        - and metadata about the level which is used for saving and loading levels
		- into the editor or when playing a level. 
*/


#pragma once
#include "RHCar.h"

enum RHGameDifficulty 
{
	DIFFICULTY_EASY = 0,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD,
	DIFFICULTY_NOT_SET
};


class RHLevelState {
public:
	RHLevelState();

	void init();

	void getVehicle(int vehicleIndex);
	int  getNumberOfVehicles();


	void addVehicle(RHCar* theCar);

private:
	std::vector<RHCar*> theCars;
	int minimumMovesNeeded = 0;
	int numberOfCars = 0;
};

class RHLevel : public RHLevelState {
public:
	// Sets up a blank level
	RHLevel();

	void setLevelName(std::string newName);
	void setAuthor(std::string newAuthor);
	void setLevelDifficulty(RHGameDifficulty difficulty);

	// TODO - add functions to get the information later. 
private:
	std::string       levelName;
	std::string       author;
	RHGameDifficulty  levelDifficulty;
};