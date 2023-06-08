#include "Button.h"

Button::Button( string _filename, Vector2f _scale)
{
	m_Texture = new Texture;
	m_Texture->loadFromFile(_filename);
	setTexture(*m_Texture);
	setScale(_scale);
}

