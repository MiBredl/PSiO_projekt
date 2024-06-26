#pragma once
#include"libraries.h"

//#include "GameManager.h"

class PlatRects
{
private:
	class GameManager* m_GameManager;
	FloatRect fRect;
		
	bool isMoving = false;
	bool isDissapear = false;
	bool movingR = false;
	bool disapearing = false;
	bool isDead= false;
	int countdown = 120;
	float startingPos;
	int speed = 2;
	int m_CurrentSpeed;
	float distance = 300;
	Vector2f m_direction = {0,0};
//	friend class Player;
public:
	PlatRects(GameManager*,FloatRect);
	PlatRects(GameManager*,FloatRect,bool,bool);
	bool isActive = false;
	bool getIsMoving() {
		return isMoving;
	}
	int getCurrentSpeed() {
		return m_CurrentSpeed;
	}
	FloatRect getRect() {
		return fRect;
	}

	
	bool isAktiveP();
	void updatePlatRects();
	bool isDeadPlatRects();
	
};

