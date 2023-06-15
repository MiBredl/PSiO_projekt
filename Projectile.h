#pragma once
#include"libraries.h"
class Projectile
{
private:
	Sprite* sprite;
	Texture* texture;
	Vector2i m_Direction;
	float m_Speed = 3.f;
	float m_StartingPos;
public:
	int getStartingPos() {
		return m_StartingPos;
	}
	Sprite* getSprite() {
		return this->sprite;
	}
	Projectile(Vector2f, Vector2i);
	~Projectile();
	void update();
	void render(RenderWindow*);
	FloatRect getBounds() {
		return sprite->getGlobalBounds();
	}
};

