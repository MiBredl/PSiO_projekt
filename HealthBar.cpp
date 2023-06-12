#include "HealthBar.h"

HealthBar::HealthBar()
{
	texture.loadFromFile("textures/player/Heart.png");
	sprite.setTexture(texture);
	
}

void HealthBar::render(RenderWindow* _window)
{
	_window->draw(sprite);
}
