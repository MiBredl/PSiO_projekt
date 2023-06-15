#pragma once
#include"Menu.h"
class MainMenu :public Menu
{
private:
	
	vector<string> m_Options {"PLAY", "RESET"};
	vector<Text> m_Texts;
	
protected:
	class GameManager& m_GameManager;
	Font m_Font;
public:
	void overrideChosen(int _option) {
		m_CurrentOption = _option;
	}
	void viewUpdate();
	MainMenu(GameManager&);
	~MainMenu() {};
	void handleInput();
	void render();
	bool collider(Text);
};

