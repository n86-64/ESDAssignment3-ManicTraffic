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

// TODO - add refrences to RHLevel and RHLevelState classes to allow the grid to be constructed.

class RHGameGrid : public cocos2d::Sprite {
public:

	RHGameGrid() = default;
	~RHGameGrid() = default;
	static RHGameGrid* create(); // todo add info to fill out the grid.

	void createGrid();

private: 
	void getAndPlaceVehicles();
};