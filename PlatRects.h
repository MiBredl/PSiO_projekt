#pragma once
#include"libraries.h"

//#include "GameManager.h"

class PlatRects
{
private:
	class GameManager* m_GameManager;
	FloatRect fRect;
	bool isActive = false;	
	bool isMoving = false;
	bool isDissapear = false;
	bool movingR = false;
	bool disapearing = false;
	bool isDead= false;
	int countdown = 120;
	float startingPos;
	int speed = 2;
	float distance = 300;
	
public:
	PlatRects(GameManager*,FloatRect);
	PlatRects(GameManager*,FloatRect,bool,bool);


	FloatRect getRect() {
		return fRect;
	}
	GameManager* getGameMeneger() {
		return m_GameManager;
	}
	bool isAktiveP();
	void updatePlatRects();
	bool isDeadPlatRects();

};

