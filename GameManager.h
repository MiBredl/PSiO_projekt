#pragma once
#include"libraries.h"
#include"Player.h"
#include"Enemy.h"
#include "MainMenu.h"
#include"Ambient.h"
#include"Platform.h"
#include"DeathMenu.h"
class Menu;
class GameManager
{
public:
	GameManager();
	void update();
	void eventManager();
	void UpdateMobs(float);
	void InitializeGame();
	void RestartGame();
	vector<Platform*> worldGenP(int starting_pos, vector<Platform*>& pvec, vector<vector<vector<int>>>& in_vec);
	vector<Ambient*> worldGenA(int starting_pos, vector<Ambient*>& favec, vector<Ambient*>& bavec, vector<Ambient*>& bvec, vector<vector<vector<int>>>& in_vec);
	

	Player* getPlayer() {
		return m_Player;
	}
	sf::Time getElapsedTime() {
		return m_Clock->restart();
	}
	Enemy* getEnemy() {
		return m_Enemy;
	}
	Platform* getPlatform() {
		return m_Platform;
	}
	vector<Platform*> getPlatforms() {
		return platforms;
	}
	sf:: RenderWindow* getWindow() {
	return m_Window;
	}
	void setGameState(int _State) {
		m_CurrentState = _State;
	}
	int GetGameState() {
		return m_CurrentState;
	}
	MainMenu* getMainMenu(){
		return m_MainMenu;
	}
private:
	bool repeated=false; 
	int m_CurrentState= GAME_ENUMS::GAMESTATE::PAUSED;
	sf::Clock* m_Clock;
	sf::RenderWindow* m_Window;
	sf::Event m_Event;
	Player* m_Player;
	Enemy* m_Enemy;
	DeathMenu* m_DeathMenu;
	MainMenu* m_MainMenu;
	Platform* m_Platform;
	

	vector<Platform*> platforms;
	vector<Ambient*> f_ambients;
	vector<Ambient*> b_ambients;
	vector<Ambient*> background;








	vector<vector<vector<int>>> world1 = {
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{8,0,0},{9,0,0},{9,0,0},{10,0,0},{0,0,0},{0,0,0},{0,0,0},{7,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{12,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{11,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{8,0,0},{9,0,0},{10,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{6,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{6,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,8,0},{0,9,0},{0,10,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{2,0,0},{1,1,0},{1,0,0},{1,2,0},{4,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{7,0,0},{0,0,0},{0,0,0},{3,0,0},{0,0,1},{0,0,1},{0,0,1},{5,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{2,0,0},{1,3,0},{1,1,0},{1,2,0},{4,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0},{0,0,1},{0,0,1},{0,0,1},{5,0,0},{0,0,0},{0,0,0},{0,0,0}},
	{{0,0,0},{3,0,0},{0,0,1},{0,0,1},{0,0,1},{5,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{3,0,0},{0,0,1},{0,0,1},{0,0,1},{5,0,0},{0,0,0},{0,7,0},{0,0,0}}
	};
};

