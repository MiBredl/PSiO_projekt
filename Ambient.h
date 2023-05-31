#pragma once
#include "Object.h"
#include "Textures.h"
#include "libraries.h"
class Ambient:public Object
{
private:
	string imagePath = "textures/Map/world/";
	void  loadTextures();
public:
	Ambient(GameManager*, string, Vector2f, Vector2f);
};


