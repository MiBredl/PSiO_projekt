#pragma once
#include"libraries.h"
#include"NPC.h"
class Player;
class Enemy :public NPC
{
public:
	Enemy(int,GameManager*);
	void movement(float);
	void update(float,sf::RenderTarget*);
	//void jumpControl(float) override;
	
private:
	
	
	
	std::string m_Path = "textures/Monsters_Creatures_Fantasy/";
	std::string m_EnemyType[4] = {"Flying eye","Skeleton","Mushroom","Goblin"};
};

