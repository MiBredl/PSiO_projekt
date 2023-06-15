#include "HealthBar.h"

HealthBar::HealthBar()
{
	texture = new Texture;
	sprite = new Sprite;
	texture->loadFromFile("textures/player/Heart.png");
	sprite->setTexture(*texture);
	
}

HealthBar::~HealthBar()
{
	delete texture;
	delete sprite;
}

void HealthBar::render(RenderWindow* _window)
{
	if(sprite!=nullptr)_window->draw(*sprite);
}
