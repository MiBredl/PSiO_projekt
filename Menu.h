#pragma once
#include"libraries.h"
class GameManager;
class Menu
{
public:
	Menu() {};
	
	virtual void handleInput() = 0;
	virtual void render() = 0;
};

