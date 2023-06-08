#pragma once
#include "Object.h"
#include "Textures.h"
#include "libraries.h"
//#include "GameManager.h"
#include <iostream>
class Ambient :public Object
{
private:
	string imagePath = "textures/Map/world/";
	void  loadTextures();
	void loadBackgroundTextures();
	float speed;
	float posY;
	bool isDoor = false;

public:
	void updateParalax();
	void updateAmbients();
	Ambient(GameManager*, string, Vector2f, Vector2f);
	Ambient(GameManager*, string, Vector2f, Vector2f, int, float);
	Ambient(GameManager*, string, Vector2f, Vector2f, bool);
};

