// RH grid vector adapted from GridVector used in exersice 2 - minesweeper. 
#include "RHGridVector.h"

RHGridVector::RHGridVector()
{
}

RHGridVector::RHGridVector(int X, int Y)
	: x(X),
	y(Y)
{
}

int RHGridVector::getX()
{
	return x;
}

int RHGridVector::getY()
{
	return y;
}

void RHGridVector::setX(int newValue)
{
	x = newValue;
	return;
}

void RHGridVector::setY(int newValue)
{
	y = newValue;
	return;
}

void RHGridVector::setXY(int X, int Y)
{
	x = X;
	y = Y;
	return;
}

void RHGridVector::resetVector()
{
	x = 0;
	y = 0;
	return;
}

void RHGridVector::correctVector()
{
	x -= 1;
	y -= 1;
	return;
}
