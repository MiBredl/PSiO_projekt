#pragma once
#include"libraries.h"
#include"Player.h"
#include"Enemy.h"
#include"MainMenu.h"
#include"Ambient.h"
#include"Platform.h"
#include"DeathMenu.h"
#include"UpgradeMenu.h"
#include"PlatRects.h"

class GameManager
{
public:
	GameManager();
	void update();
	void eventManager();
	void UpdateMobs(float);
	void InitializeGame(int);
	void RestartGame();
	void loadWorld1();
	void loadWorld2();
	void loadBackground();
	/*vector<Platform*> worldGenP(int starting_pos, vector<Platform*>& pvec, vector<vector<vector<int>>>& in_vec);
	vector<Ambient*> worldGenA(int starting_pos, vector<Ambient*>& favec, vector<Ambient*>& bavec, vector<Ambient*>& bvec, vector<vector<vector<int>>>& in_vec);*/
	vector<Enemy*> worldGenE(int starting_pos, vector<Enemy*>& evec, vector<vector<vector<int>>>& in_vec);
	tuple<vector<Platform*>, vector<Ambient*>, vector<Ambient*>, vector<Ambient*>, vector<PlatRects*>> worldGen(int starting_pos, vector<Platform*>& pvec, vector<Ambient*>& favec, vector<Ambient*>& bavec, vector<Ambient*>& bvec, vector<PlatRects*> rect, vector<vector<vector<int>>>& in_vec);
	Player* getPlayer() {
		return m_Player;
	}
	sf::Time getElapsedTime() {
		return m_Clock->restart();
	}
	Enemy* getEnemy() {
		return m_Enemy;
	}
	vector<PlatRects*> getPlatRects() {
		return platRects;
	}
	vector<Platform*> getPlatforms() {
		return platforms;
	}
	vector<Enemy*> getEnemies() {
		return enemies;
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
	View getView() {
		return view;
	}
private:
	bool repeated=false; 
	int m_CurrentState= GAME_ENUMS::GAMESTATE::PAUSED;
	int m_CurrentWorld;
	sf::Clock* m_Clock;
	sf::RenderWindow* m_Window;
	sf::Event m_Event;
	View view;
	Player* m_Player;
	Enemy* m_Enemy;
	UpgradeMenu* m_UpgradeMenu;
	DeathMenu* m_DeathMenu;
	MainMenu* m_MainMenu;
	Platform* m_Platform;
	
	vector<Platform*> platforms;
	vector<Ambient*> f_ambients;
	vector<Ambient*> b_ambients;
	vector<Ambient*> close_background;
	vector<Ambient*> far_background;
	vector<Enemy*> enemies;
	vector<PlatRects*> platRects;
	vector<RectangleShape*> rectangles;







	vector<vector<vector<int>>> world1 =
	{
{{0 , 0 , 0 , 1 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 1 },{0 , 0 , 0 , 1 },{0 , 0 , 0 , 1 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{8 , 0 , 0 , 0 },{9 , 0 , 0 , 0 },{9 , 0 , 0 , 0 },{10, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{7 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{8 , 0 , 0 , 0 },{9 , 0 , 0 , 0 },{10, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{7 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{11, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{6 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{{0 , 0 , 0 , 0 },{0 , 8 , 0 , 0 },{0 , 9 , 0 , 0 },{0 ,10 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 1 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{6 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{2 , 0 , 0 , 0 },{1 ,11 , 0 , 0 },{4 , 0 , 0 , 0 }},
{{2 , 0 , 0 , 0 },{1 , 1 , 0 , 0 },{1 , 0 , 0 , 0 },{1 , 2 , 0 , 0 },{1 , 0 , 0 , 0 },{4 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{7 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 2 },{0 , 0 , 0 , 0 },{0 , 7 , 0 , 3 },{0 , 0 , 0 , 0 },{0 , 8 , 0 , 0 },{0 , 9 , 0 , 0 },{0 ,10 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{5 , 0 , 0 , 0 }},
{{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 2 , 0 },{5 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{2 , 0 , 0 , 0 },{1 , 3 , 0 , 0 },{1 , 0 , 0 , 0 },{1 , 0 , 0 , 0 },{1 , 2 , 0 , 0 },{1 , 0 , 0 , 0 },{4 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{5 , 0 , 0 , 0 }},
{{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 2 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{5 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{5 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{5 , 0 , 0 , 0 }},
	};
	vector<vector<vector<int>>> world2 = {
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 1 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{13, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{8 , 0 , 0 , 0 },{9 , 0 , 0 , 0 },{10, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{14, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{8 , 0 , 0 , 0 },{9 , 0 , 0 , 0 },{10, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {11, 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{11, 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{7 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{7 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 8 , 0 , 0 },{0 , 9 , 0 , 0 },{0 ,10 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 7 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{2 , 0 , 0 , 0 },{1 , 0 , 0 , 0 },{1 , 0 , 0 , 0 },{1 , 0 , 0 , 0 },{1 , 0 , 0 , 0 },{4 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
{ {0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{3 , 0 , 0 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 2 , 0 },{0 , 0 , 1 , 0 },{0 , 0 , 1 , 0 },{5 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 },{0 , 0 , 0 , 0 }},
	};
};

