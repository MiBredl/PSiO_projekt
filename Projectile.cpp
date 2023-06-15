#include "Projectile.h"

Projectile::Projectile(Vector2f _position,Vector2i _direction)
{
	sprite = new Sprite;
	texture = new Texture;
	//cout << "Projectile\n";
	texture->loadFromFile("textures/Monsters_Creatures_Fantasy/Boss/Flame.png");
	sprite->setScale(4,4);
	sprite->setTexture(*texture);
	sprite->setPosition(_position);
	m_StartingPos = _position.x;
	m_Direction = _direction;
}

Projectile::~Projectile()
{
	delete texture;
	delete sprite;
}

void Projectile::update()
{
	sprite->move(m_Direction.x*m_Speed,m_Direction.y*m_Speed);
}

void Projectile::render(RenderWindow* _window)
{
	_window->draw(*sprite);
}
