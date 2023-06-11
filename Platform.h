#pragma once
#include "Object.h"
#include "Textures.h"
#include "libraries.h"

class Platform:public Object
{
private:
	string imagePath = "textures/Map/world/";
	void  loadTextures();
	bool isMoving=false;
	bool isDissapear=false;
	bool disapearing = false;
	bool isDead=false;
	bool isMovingVertical=false;
	
	int countdown = 120;
	int speed=2;
	Vector2f distance = { 300,100 };
	int alpha = 150;
	bool movingR = 0;
	bool movingUp = false;
	Vector2f startingPos;
public:
	
	Platform(GameManager*, string ,Vector2f,Vector2f);
	Platform(GameManager*, string, Vector2f, Vector2f, bool,bool,bool);
	void platformUpdate();
	bool isDeadPlat();
};

