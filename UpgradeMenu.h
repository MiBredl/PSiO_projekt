#pragma once
#include"Menu.h"


class UpgradeMenu : public Menu
{
private:
	class GameManager& m_GameManager;
	Font m_Font;
	bool m_isOnCoolDown = false;
	int m_CoolDown = 30;
	int m_SpriteQuantity=2;
	int m_BetweenWidth = 120;
	string m_Path="textures/Square Buttons/";
	vector<Text> m_UpgradeTexts;
	vector<string> m_UpgradeStrings = {"CURRENT LEVEL: ","UPGRADE OPTIONS: ","STRENGHT", "HP"};
	vector<Sprite> m_ButtonSprites;
	vector<Texture> m_ButtonTextures;
	vector<string> m_TexturePaths = {m_Path+"Colored Square Buttons/Back col_Square Button.png",m_Path+"Square Buttons/Back Square Button.png"};
public:
	UpgradeMenu(GameManager&);
	void handleInput();
	void viewUpdate();
	
	void render();
};

