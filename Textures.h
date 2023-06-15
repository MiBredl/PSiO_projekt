#pragma once
#include"libraries.h"

class Textures
{
private:
	Texture* texture;
	IntRect TexureRect;
	string name;
public:
	Textures(string,string, IntRect);
	~Textures();
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


