#pragma once
#include"libraries.h"
class PlatRects
{
private:
	class GameManager* m_GameManager;
	bool isActive = false;
	IntRect intRect;
public:
	PlatRects(IntRect);
	IntRect getRect() {
		return intRect;
	}

};

