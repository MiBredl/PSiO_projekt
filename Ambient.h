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
	float speed;
	float posY;
	float posX;


public:
	void updateParalax();
	void updateAmbients();
	Ambient(GameManager*, string, Vector2f, Vector2f);
	Ambient(GameManager*, string, Vector2f, Vector2f,int, float);
};

