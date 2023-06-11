#include "Object.h"

void Object::renderPlat(RenderWindow* window)
{
	this->sprite->setTextureRect(current_Texture->getRect());

	window->draw(*sprite);
}

void Object::setTextures(string map)
{
	if (this->m_Texture.find(map) == this->m_Texture.end()) return;
	if (this->current_Texture != nullptr)
	if (this->current_Texture->getName() != map) return;


	this->current_Texture = this->m_Texture[map];

	this->sprite->setTexture(*this->current_Texture->getTexture());
}

void Object::addTextures(Textures* _text)
{
	if (this->m_Texture.find(_text->getName()) != this->m_Texture.end()) return;

	this->m_Texture.insert(pair<string, Textures*>(_text->getName(), _text));
}

void Object::setColor(Color& color)
{
	sprite->setColor(color);
}
