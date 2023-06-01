#include "Menu.h"
#include<iostream>

Menu::Menu()
{

	if (!m_Font.loadFromFile("Fonts/Lobster-Regular.ttf"))

		for (int i = 0; i < 2;i++) {
			m_Texts[i].setFont(m_Font);
			m_Texts[i].setCharacterSize(30);
			m_Texts[i].setFillColor(Color::White);
			m_Texts[i].setString(m_Options[i]);
			m_Texts[i].setPosition(300,500);
		}
}

void Menu::handleInput()
{

	Vector2i _mousePos = Mouse::getPosition();
	
	for (int i = 0; i < 2; ++i) {
		if (m_Texts[i].getGlobalBounds().contains(static_cast<float>(_mousePos.x), static_cast<float>(_mousePos.y))) {
			m_Texts[i].setFillColor(sf::Color::Green);
		}
		
	}

	
}

void Menu::update(RenderWindow* window)
{
	
	handleInput();
	for (const Text text : m_Texts) {
		window->draw(text);
	}
}
