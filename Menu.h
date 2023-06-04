#pragma once
#include"libraries.h"
class GameManager;
class Menu
{
public:
	Menu() {};
	virtual void viewUpdate() = 0;
	virtual void handleInput() = 0;
	virtual void render() = 0;
};

