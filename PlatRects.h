#pragma once
#include"libraries.h"

//#include "GameManager.h"

class PlatRects
{
private:
	class GameManager* m_GameManager;
	bool isActive = false;
	FloatRect fRect;
public:
	PlatRects(GameManager*,FloatRect);
	FloatRect getRect() {
		return fRect;
	}
	GameManager* getGameMeneger() {
		return m_GameManager;
	}
	bool isAktiveP();

};

