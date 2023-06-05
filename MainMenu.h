#pragma once
#include"Menu.h"
class MainMenu :public Menu
{
private:
	class GameManager& m_GameManager;
	vector<string> m_Options {"PLAY", "RESET"};
	vector<Text> m_Texts;
	Font m_Font;
	
public:
	void overrideChosen(int _option) {
	//	cout << "OVER\n";
		m_CurrentOption = _option;
	}
	void viewUpdate();
	MainMenu(GameManager&);
	~MainMenu() {};
	void handleInput();
	void render();
};

