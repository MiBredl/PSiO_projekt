#pragma once
#include"Menu.h"
class DeathMenu :public Menu
{
private:
	Font font;
	Text texts[2];
	string  m_OptionText[2] = { "DEATH","RESTART" };
	class GameManager& m_GameManager;
public:
	DeathMenu(GameManager&);
	void handleInput();
	void render();
};

