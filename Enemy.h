#pragma once
#include"libraries.h"
#include"NPC.h"
#include"Platform.h"
#include"PlatRects.h"
#include"EnemyBar.h"

class Player;
class EnemyBar;
class Enemy :public NPC
{

protected:
	bool onActive = false;
	string m_Path = "textures/Monsters_Creatures_Fantasy/";
	string m_EnemyType[5] = { "Flying eye","Skeleton","Mushroom","Goblin","Boss" };
	int type;
	void loadAnimations();
	EnemyBar* m_Bar;
public:
	Enemy(int,GameManager*, Vector2f);
	~Enemy();
	void movement(float);
	void update(float,sf::RenderTarget*);
	//void jumpControl(float) override;
	void fallControll(float);
	bool gaveExp;
	float getHPRatio() {
		return m_HP / type;
	}
	
};

