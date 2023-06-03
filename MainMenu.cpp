#include "MainMenu.h"
#include"GameManager.h"

MainMenu::MainMenu(GameManager& _GameManager): m_GameManager(_GameManager)
{
	if (!m_Font.loadFromFile("Fonts/Roboto-Black.ttf")) {}
	m_Texts.resize(m_Options.size());
	for (int i = 0; i < m_Options.size();i++) {
		m_Texts[i].setFont(m_Font);
		m_Texts[i].setString(m_Options[i]);
		m_Texts[i].setCharacterSize(40);
		m_Texts[i].setPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2+i*50);
	}
}

void MainMenu::handleInput()
{
	Vector2i _mousePos = Mouse::getPosition();
	
	for (int i = 0; i <m_Texts.size(); i++) {
		if (m_Texts[i].getGlobalBounds().left<=_mousePos.x 
			&& m_Texts[i].getGlobalBounds().left +m_Texts[i].getGlobalBounds().width>=_mousePos.x
			&& m_Texts[i].getGlobalBounds().top<=_mousePos.y-10
			&& m_Texts[i].getGlobalBounds().top+ m_Texts[i].getGlobalBounds().height>=_mousePos.y-30) {
			m_Texts[i].setFillColor(sf::Color::Green);
			if (Mouse::isButtonPressed(Mouse::Left)) {
				m_CurrentOption = i;
				
				m_Texts[i].setFillColor(sf::Color::Red);
			}
		}
		else m_Texts[i].setFillColor(Color::White);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		m_CurrentOption = GAME_ENUMS::GAMESTATE::PAUSED;
	}
	




	m_GameManager.setGameState(m_CurrentOption);

	
}

void MainMenu::render()
{
	for (auto& text : m_Texts) {
		m_GameManager.getWindow()->draw(text);
	}
}
