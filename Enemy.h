#pragma once
#include"libraries.h"
#include"NPC.h"
#include "Platform.h"
#include "PlatRects.h"
class Player;
class Enemy :public NPC
{
public:
	Enemy(int, GameManager*, Vector2f);
	void movement(float);
	void update(float, sf::RenderTarget*);
	//void jumpControl(float) override;
	void fallControll(float);
	bool gaveExp;

private:
	bool onActive = false;
	int type;
	void loadAnimations();
	vector<PlatRects*> platforms;
	std::string m_Path = "textures/Monsters_Creatures_Fantasy/";
	std::string m_EnemyType[4] = { "Flying eye","Skeleton","Mushroom","Goblin" };

};

