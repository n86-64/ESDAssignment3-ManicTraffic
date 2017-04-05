/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHGridVector.h
File Contents - class definctions for the Grid Vector.

Purpose - Contains the vector data structure which is used for calculating the vehicles position.
        - code derived from previous math helper libraray (GridVector) used in Exersice 2 - Minesweeper
*/


#pragma once

class RHGridVector {
public:
	RHGridVector();
	RHGridVector(int X, int Y);

	int getX();
	int getY();
	void setX(int newValue);
	void setY(int newValue);
	void setXY(int X, int Y);

	void resetVector();
	void correctVector();

private:
	int x = 0;
	int y = 0;
};