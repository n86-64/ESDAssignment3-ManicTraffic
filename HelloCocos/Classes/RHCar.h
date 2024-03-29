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
#include "RHGridVector.h"

enum RHCarTypes 
{
	CAR_TARGET = 0,
	CAR_NORMAL,
	CAR_LORRY,
	CAR_UNDEF
};

// TODO - will need to see if this works or not. 
enum RHCarDirections 
{
	DIR_X_POSITIVE = 1,
	DIR_X_NEGATIVE = -1,
	DIR_Y_POSITIVE = 2,
	DIR_Y_NEGATIVE = -2,
	DIR_UNDEF = 0
};

class RHCar : public cocos2d::Sprite {
public:
	RHCar() = default;
	~RHCar() = default;

	static RHCar* create(RHCarTypes carType, RHCarDirections carDirections, bool isMovementFree, RHGridVector carPosition);

	// create event handlers and initialise sprite and position. 
	void initCar();

	bool canMove = true;
	bool hasMoved = false;

	// used to set our position.
	RHGridVector getGridPosition();
	void setGridPosition(RHGridVector newPos);
	void setVehicleType(RHCarTypes carType);
	void setVehicleDirection(RHCarDirections carDirection);

	RHCarDirections getVehicleDirection();
	RHCarTypes getVehicleType();
	void setGridLimitsX(RHGridVector gridLimit);
	void setGridLimitsY(RHGridVector gridLimit);

	void setOriginalPosition(cocos2d::Vec2 pos);

	void resetCarPosition();

	// add the mouse events here. Dont need to add them yet as we havnt built the rest of the editor. 
	bool onTouchBegin(cocos2d::Touch* touchData, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touchData, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touchData, cocos2d::Event* event);

private: 
	RHGridVector gridPosition;
	RHGridVector gridLimitsX; 
	RHGridVector gradLimitsY;
	bool isVehicleCurrentlySelected = false;
	RHCarTypes vehicleType = CAR_UNDEF;
	RHCarDirections vehicleDirection = DIR_UNDEF;

	cocos2d::Vec2 originalPosition;

	std::string getSpritePath(RHCarTypes carType); 

	bool isOutsideGridLimits(int axis,cocos2d::Vec2 mouseDelta);
};