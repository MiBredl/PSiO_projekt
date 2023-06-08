#pragma once
#include"libraries.h"
class GameManager;
class Menu
{
protected:
	int m_CurrentOption = 0;
	int m_ChosenOption = 0;
public:
	Menu() {};
	//virtual void viewUpdate() = 0;
	virtual void handleInput() = 0;
	virtual void render() = 0;
};

