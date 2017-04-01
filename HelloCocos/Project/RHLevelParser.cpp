#include "RHLevelParser.h"

// TODO - check to see if sprites will auto release when RHLevel is deleated. 
// Possibly yes but im not sure. 


RHFileParser::RHFileParser()
{}

void RHFileParser::openLevel(RHLevel* dataDestination, std::string fileLocation)
{
	theLevel = dataDestination;
	theLevel->reset();

	std::fstream fileStream(fileLocation, std::fstream::in);
	std::string lineContents;

	std::size_t found = fileLocation.find(".mtlf");

	// if file exists read into buffer and start operating
	if (fileStream.fail()) 
	{
		MessageBoxA(NULL, "This file specified does not exist.\n Please ensure your filename is valid", "File Error", MB_OK | MB_ICONERROR);
	}
	else 
	{
		while (std::getline(fileStream, lineContents)) 
		{
			if (!lineContents.empty()) 
			{
				fileContents.push_back(lineContents);
			}
		}

		// Now that we have input we can extract the data using our parser.
		if (fileContents.size() < 3 || (found == std::string::npos)) 
		{
			MessageBoxA(NULL, "This file has an incorrect format. Please open a valid file.", "File Error", MB_OK | MB_ICONERROR);
		}
		else 
		{
			// here we do the data extraction.
			getMetaData();
			getAndConstructVehicles();
		}
	}

	fileStream.clear();
	fileStream.close();
	fileContents.clear();
}

void RHFileParser::saveLevel(RHLevel* levelToSave)
{
	// TODO - add code to save level editor levels. 
	// find out where files get saved. 
	std::fstream fileStream("youmyfile.mtlf", std::fstream::out);
	fileStream << "hello world";
	fileStream.close();
}

void RHFileParser::printMessage()
{
	for (int i = 0; i < fileContents.size(); i++) 
	{
		cocos2d::log("%s", fileContents[i].c_str());
	}
}

void RHFileParser::getMetaData()
{
	theLevel->setLevelName(fileContents[0]);
	theLevel->setAuthor(fileContents[1]);
	theLevel->setLevelDifficulty((RHGameDifficulty)std::stoi(fileContents[2]));
}

void RHFileParser::getAndConstructVehicles()
{
	RHCar* levelCar = nullptr;
	int numberOfSpaces = 0;
	std::string value;

	// vehicle properties.
	RHGridVector carPosition;
	RHCarDirections carDirection;
	RHCarTypes carType;

	for (int e = 3; e < fileContents.size(); e++) 
	{
		// first vehicle is a target vehicle hence we should pass it to the array. 
		for (int i = 0; i < fileContents[e].size(); i++)
		{
			if (fileContents[e][i] == ' ')
			{
				switch (numberOfSpaces)
				{
				case 0:
					carType = (RHCarTypes)std::stoi(value);
					break;
				case 1:
					carPosition.setX(std::stoi(value));
					break;
				case 2:
					carPosition.setY(std::stoi(value));
					break;
				default:
					break;
				}

				value.clear();
				numberOfSpaces++;
			}
			else
			{
				value += fileContents[e][i];
			}
		}
		carDirection = (RHCarDirections)std::stoi(value);

		levelCar = RHCar::create(carType, carDirection, false, carPosition);
		theLevel->addVehicle(levelCar);
		levelCar = nullptr;
		value.clear();
		numberOfSpaces = 0;
	}
}
