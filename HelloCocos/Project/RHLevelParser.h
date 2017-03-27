/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHFileParser.h
File Contents - class definitons for the level parsing system.

Purpose - Contains the file parser which is able to read and write files to the users directories
        - Allowing custom levels to be made and loaded.
		- useful for creating the levels in our game. 
*/

#pragma once
#include <fstream>
#include <string>
#include "cocos2d.h"

#include "RHLevelComponents.h"

class RHFileParser {
public:
	RHFileParser();
	
	void openLevel(RHLevel* dataDestination, std::string fileLocation);
	void saveLevel(RHLevel* levelToSave);

	void printMessage();
private:
	RHLevel* theLevel = nullptr;
	std::vector<std::string> fileContents;
	
	void getMetaData();
	void getAndConstructVehicles();
};