/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHCar.h
File Contents - class definctions for car objects and supporting types.

Purpose - Contains the car data structure which is a sprite that can be moved within the grid on screen. 
*/

#pragma once
#include "cocos2d.h"

enum RHCarTypes 
{
	CAR_TARGET = 0,
	CAR_NORMAL,
	CAR_LORRY
};

enum RHCarDirections 
{
	DIR_X_POSITIVE = 1,
	DIR_X_NEGATIVE = -1,
	DIR_Y_POSITIVE = 1,
	DIR_Y_NEGATIVE = -1,
};

class RHCar : public cocos2d::Sprite {
public:
	RHCar() = default;
	~RHCar() = default;

	static RHCar* create(RHCarTypes carType, RHCarDirections carDirections,bool isMovementFree);

private: 



	// create functions to initialise.
	// should cars have a movement mode. (Yes as its a single bit )
};