#include "HealthBar.h"

HealthBar::HealthBar(Vector2f _position)
{
	texture.loadFromFile("textures/player/Heart.png");
	sprite.setTexture(texture);
	sprite.setPosition(_position);
}

void HealthBar::render(RenderWindow* _window)
{
	_window->draw(sprite);
}
