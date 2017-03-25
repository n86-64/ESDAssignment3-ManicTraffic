/*
Module - UFCFWA-30-1
Name - Nathan Butt
Student No - 16013327

Exersice 3 - Rush hour game.
File Name - RHWidgetBase.h
File Contents - The widget class definiiton.

Purpose - The widget object which can be customised for various menus and 
          contexts.
*/

#pragma once
#include <cocos2d.h>
#include "ui\UILayout.h"

class RHWidgetBase : public cocos2d::ui::Layout {
public:

private:
	std::string windowTitle;
};