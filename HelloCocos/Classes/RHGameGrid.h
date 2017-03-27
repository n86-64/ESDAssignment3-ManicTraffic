/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHGameGrid.h
File Contents - The game grid class definition.

Purpose - The widget object which can be customised for various menus and
contexts.
*/


#pragma once
#include "cocos2d.h"
#include "RHCar.h"
#include "RHLevelComponents.h"

// TODO - add refrences to RHLevel and RHLevelState classes to allow the grid to be constructed.


// we will be taking the level state and using its objects to construct the grid when we enter the game.
// but first we will need to make sure my collision idea works. 
class RHGameGrid : public cocos2d::Sprite {
public:

	RHGameGrid() = default;
	~RHGameGrid() = default;
	static RHGameGrid* create(); // todo add info to fill out the grid.

	void initGrid();
	void setLevelState(RHLevelState levelState);

	// put events here for collision.
	bool onTouchBegin(cocos2d::Touch* touchData, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touchData, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touchData, cocos2d::Event* event);

	void onKeyBoardPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private: 
	RHCar* selectedCar = nullptr;
	RHLevelState theState;

	void getAndPlaceVehicles();
};