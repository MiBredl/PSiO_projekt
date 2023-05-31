#include"libraries.h"
#pragma once

class Textures
{
private:
	Texture* texture;
	IntRect TexureRect;
	string name;
public:
	Textures(string,string, IntRect);
	Texture* getTexture() {
		return texture;
	}
	IntRect getRect() {
		return TexureRect;
	}
	string getName() {
		return name;
	}
};


