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
	float startingPos;
	int countdown = 120;
	int speed=2;
	float distance=300;
	bool movingR = 0;
public:
	
	Platform(GameManager*, string ,Vector2f,Vector2f);
	Platform(GameManager*, string, Vector2f, Vector2f, bool,bool);
	void platformUpdate();
	bool isDeadPlat();
};

