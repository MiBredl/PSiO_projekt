#include "EnemyBar.h"

EnemyBar::EnemyBar(Vector2f _position, Vector2f _scale)
{
	m_FrontBarWidth = _scale.x;
	healthBarBack = new RectangleShape;
	healthBarFront = new RectangleShape;
	healthBarBack->setFillColor(Color(0, 0, 0, 153));
	healthBarBack->setSize(_scale);

	healthBarBack->setPosition(_position);
	healthBarFront->setFillColor(Color(201, 0, 0, 255));
	healthBarFront->setSize(_scale);
	healthBarFront->setPosition(_position);
}

void EnemyBar::update(Vector2f _position,float _ratio)
{
	

	healthBarFront->setSize({ m_FrontBarWidth * _ratio,healthBarFront->getSize().y});
	
	healthBarBack->setPosition(_position);
	healthBarFront->setPosition(_position);
}

void EnemyBar::render(RenderTarget* _window)
{
	_window->draw(*healthBarBack);
	_window->draw(*healthBarFront);
}
