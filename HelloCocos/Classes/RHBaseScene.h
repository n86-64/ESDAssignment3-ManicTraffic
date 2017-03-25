/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game. 
File Name - RHBaseScene.h
File Contents - The class definition for a Base Scene inheritance class. 

Purpose - Contains the basic objects for the several scene objects that will be used in the system. 
*/

#pragma once
#include "cocos2d.h"
#include "RHGameGrid.h"

class RHBaseScene : public cocos2d::Scene 
{
public:
	RHGameGrid* levelGrid = nullptr;

	// dont overide anything yet. 
	// the individual scenes can do that. 
};