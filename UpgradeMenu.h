#pragma once
#include"Menu.h"
#include"Button.h"


class UpgradeMenu : public Menu
{
private:
	class GameManager& m_GameManager;
	Font m_Font;

	enum UPGRADE_TEXT { EXP, OPTIONS, STRENGHT, HP };
	enum BUTTONS { RED_STR, WHITE_STR, RED_HP, WHITE_HP, BACK, ACCEPT };
	enum BUFFER_TEXT {B_STR,B_HP};

	bool m_isOnCoolDown = false;
	bool m_isOpen = false;
	bool Closed = true;
	bool previousOpen=false;
	int m_CoolDown = 30;
	int m_SpriteQuantity=4;
	int m_ScrollsQuantity=2;
	int m_BetweenWidth = 120;
	int totalButtonQuantity = 6;
	int arrowQuantity = 4;
	int actionButtons = 2;
	int bufferShowQuantity = 2;
	int m_BufforHP = 0;
	int m_BufforSTRENGTH = 0;
	int m_BufforEXP = 0;
	string m_Path="textures/Square Buttons/";
	string m_PathScrolls="textures/Scrolls/";
	vector<Text> m_UpgradeTexts;
	vector<string> m_UpgradeStrings = {"EXP: ","UPGRADE OPTIONS: ","STRENGTH", "HP"};
	vector<Text> bufferTexts;
	

	vector<Sprite> m_ButtonSprites;
	vector<Texture> m_ButtonTextures;





	std::unique_ptr<Sprite> m_Scroll;
	vector<Texture> m_ScrollTextures;




	vector<string> m_ScrollTexturePaths = {m_PathScrolls+"closed.png",m_PathScrolls+"medium.png"};
	vector<string> m_TexturePaths = {
		m_Path+"Colored Square Buttons/Back col_Square Button.png",
		m_Path+"Square Buttons/Back Square Button.png",
		"textures/Large Buttons/Large Buttons/Back Button.png",
	"textures/Square Buttons/Square Buttons/V Square Button.png"
		
	};
	/*vector<string> m_TextureActionPaths = { 
	
	};*/
	FloatRect scrollBounds;

	void handleInput();
	void buttonsUpdate();
	void textSetUp();
	void viewUpdateTexts();
	void textUpdate();
	void scrollOpen();
	void scrollCloed();
	void handleInnerInput();
	void update();
	bool collider(FloatRect);
	void upgdateBufferVisuals();
	Vector2f mapToCords(Vector2i);

public:
	UpgradeMenu(GameManager&);
	
	
	void render();
};

