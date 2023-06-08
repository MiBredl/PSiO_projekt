#pragma once
#include"libraries.h"

class HealthBar
{
private:
	Sprite sprite;
	Texture texture;
public:
	HealthBar(Vector2f);
	void render(RenderWindow*);
	Vector2f getPosition() {
		return sprite.getPosition();
	}
};

