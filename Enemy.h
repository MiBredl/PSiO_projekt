#pragma once
#include"libraries.h"
#include"NPC.h"
#include "Platform.h"
class Player;
class Enemy :public NPC
{
public:
	Enemy(int,GameManager*, Vector2f);
	void movement(float);
	void update(float,sf::RenderTarget*);
	//void jumpControl(float) override;
	void fallControll(float);
	bool gaveExp;

private:
	int type;
	void loadAnimations();
	vector<Platform*> platforms;
	std::string m_Path = "textures/Monsters_Creatures_Fantasy/";
	std::string m_EnemyType[4] = {"Flying eye","Skeleton","Mushroom","Goblin"};
	
};

