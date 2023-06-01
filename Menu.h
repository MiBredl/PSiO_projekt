#include"libraries.h"



class Menu  {
private:
	Text m_Texts[2];
	string m_Options[2] = {"PLAY","PAUSE"};
	Font m_Font;
	int m_CurrentOption=0;
	int m_SelectedOption=0;
	
public:
	
	Menu();
	void handleInput();
	void update(RenderWindow*);
};