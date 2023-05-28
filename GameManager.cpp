#include "GameManager.h"

GameManager::GameManager()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"SUS SOULS");
	m_Clock = new sf::Clock;
	m_Player = new Player(this);
	m_Enemy = new Enemy(1,this);
	update();
}

void GameManager::update()
{
	while (m_Window->isOpen()) {
		eventManager();
		m_Window->clear();
		float deltaTime = getElapsedTime().asSeconds();
		if (m_Player != nullptr) {
			m_Player->update(deltaTime, m_Window);
		}
		if (m_Enemy != nullptr) {
			m_Enemy->update(deltaTime, m_Window);
		}
		m_Window->display();
	}
}

void GameManager::eventManager()
{
	while (m_Window->pollEvent(m_Event))
	{
		switch (m_Event.type) {
		case sf::Event::Closed: 
			m_Window->close();
			break;
		}
	}
}
