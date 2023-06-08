#pragma once
#include"libraries.h"
class PlatRects
{
private:
	IntRect intRect;
public:
	PlatRects(IntRect);
	IntRect getRect() {
		return intRect;
	}
};

