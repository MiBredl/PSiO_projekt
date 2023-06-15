#pragma once
#include"Enemy.h"
class EnemyBar
{
private:
	RectangleShape *healthBarFront, *healthBarBack;
	float m_FrontBarWidth;
public:
	EnemyBar(Vector2f,Vector2f);
	void update(Vector2f,float);
	void render(RenderTarget*);
	FloatRect getGlobalBound() {
		return healthBarBack->getGlobalBounds();
	}
};

