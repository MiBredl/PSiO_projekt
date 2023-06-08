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
		//m_Texts[i].setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + i * 50);
	}
}

void MainMenu::handleInput()
{
	
	sf::Vector2i _mousePos = sf::Mouse::getPosition(*m_GameManager.getWindow());
	sf::Vector2f worldMousePos = m_GameManager.getWindow()->mapPixelToCoords(_mousePos);

	for (int i = 0; i <m_Texts.size(); i++) {
		if (m_Texts[i].getGlobalBounds().left<= worldMousePos.x
			&& m_Texts[i].getGlobalBounds().left +m_Texts[i].getGlobalBounds().width>= worldMousePos.x
			&& m_Texts[i].getGlobalBounds().top<= worldMousePos.y-10
			&& m_Texts[i].getGlobalBounds().top+ m_Texts[i].getGlobalBounds().height>= worldMousePos.y-30) {
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

void MainMenu::viewUpdate()
{
	for (int i = 0; i < m_Options.size(); i++) {
		sf::Vector2i pixelPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + i * 50);
		sf::Vector2f worldPos = m_GameManager.getWindow()->mapPixelToCoords(pixelPos);
		m_Texts[i].setPosition(worldPos);
	}
}
void MainMenu::render()
{
	viewUpdate();
	for (auto& text : m_Texts) {
		m_GameManager.getWindow()->draw(text);
	}
}
