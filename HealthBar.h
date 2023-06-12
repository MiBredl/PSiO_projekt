#pragma once
#include"libraries.h"

class HealthBar
{
private:
	Sprite sprite;
	Texture texture;
public:
	HealthBar();
	void setPosition(Vector2f _position) {
		sprite.setPosition(_position);
	}
	void render(RenderWindow*);
	Vector2f getPosition() {
		return sprite.getPosition();
	}
};

