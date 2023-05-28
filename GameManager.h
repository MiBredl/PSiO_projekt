#pragma once
#include"libraries.h"
#include"Player.h"
#include"Enemy.h"

class GameManager
{
public:
	GameManager();
	void update();
	void eventManager();
	Player* getPlayer() {
		return m_Player;
	}
	sf::Time getElapsedTime() {
		return m_Clock->restart();
	}
	Enemy* getEnemy() {
		return m_Enemy;
	}
private:
	sf::Clock* m_Clock;
	sf::RenderWindow* m_Window;
	sf::Event m_Event;
	Player* m_Player;
	Enemy* m_Enemy;
};

