#pragma once
#include "Object.h"
#include "Textures.h"
#include "libraries.h"

class Platform:public Object
{
private:
	string imagePath = "textures/Map/world/";
	void  loadTextures();
public:
	Platform(GameManager*, string ,Vector2f,Vector2f);
};

