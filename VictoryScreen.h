#pragma once
#include"MainMenu.h"
class VictoryScreen : public MainMenu
{
private:
	vector<Text> m_Texts;
	vector<string> m_Options = {"YOU WON", "PLAY AGAIN"};
public:
	VictoryScreen(GameManager&);
	void handleInput();
	void render();
	void update();
};

