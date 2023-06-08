#include "GameManager.h"



GameManager::GameManager():m_CurrentState(GAME_ENUMS::GAMESTATE::PLAYING)
{

	m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"SUS SOULS");
	m_Window->setFramerateLimit(60);
	view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	

	
	//loadWorld1();
	loadWorld2();
	InitializeGame();
	m_UpgradeMenu = new UpgradeMenu(*this);
	m_MainMenu = new MainMenu(*this);
	update();
}

void GameManager::update()
{

	
	while (m_Window->isOpen()) {
		eventManager();
		view.setCenter(m_Player->getSprite()->getPosition().x, WINDOW_HEIGHT / 2);
		m_Window->clear();
		//cout <<"CURRENT STATE: " << m_CurrentState << endl;
		
		if (m_MainMenu != nullptr ) {
			m_MainMenu->handleInput();
			if (m_CurrentState == GAME_ENUMS::GAMESTATE::PAUSED) { 
				m_MainMenu->render(); 
			}
			 
		}
		
		if (m_CurrentState== GAME_ENUMS::GAMESTATE::RESTART) {
			//cout << "RESTART\n";
			RestartGame();
			InitializeGame();
			m_MainMenu->overrideChosen(GAME_ENUMS::GAMESTATE::PLAYING);
		}
		
		if (m_CurrentState == GAME_ENUMS::GAMESTATE::PLAYING) {
			
			m_Window->setView(view);
			view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
			
			float deltaTime = getElapsedTime().asSeconds();
			for (Ambient* ambient : far_background)
			{
				ambient->renderPlat(m_Window);
				ambient->updateParalax();
			}
			for (const auto& bground : close_background)
			{
				bground->renderPlat(m_Window);
			}
			for (const auto& back_amb : b_ambients)
			{
				back_amb->renderPlat(m_Window);
			}
			for (const auto& platform : platforms) {
				platform->renderPlat(m_Window);
			}
			
			
			if (m_Player != nullptr) m_Player->render(m_Window, deltaTime);
			//if (m_Enemy != nullptr) m_Enemy->render(m_Window, deltaTime);
			for (const auto& enemy_ : enemies)
			{
				enemy_->render(m_Window, deltaTime);
			}
			if (enemies.size() != 0)
			{
				for (const auto& _enem : enemies) {
					_enem->update(deltaTime, m_Window);
				}
			}
			for (const auto& front_amb : f_ambients)
			{
				front_amb->renderPlat(m_Window);
			}
			 UpdateMobs(deltaTime);
			 if (m_UpgradeMenu != nullptr) m_UpgradeMenu->render();
		}
		if (m_CurrentState == GAME_ENUMS::GAMESTATE::DEAD) {
			//cout << "dziala\n";
			m_DeathMenu->render();
			
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
void GameManager::UpdateMobs(float deltaTime)
{
		if (m_Player != nullptr) {
			m_Player->update(deltaTime, m_Window);

		}
		for (const auto& enemy_ : enemies)
		{
			enemy_->update(deltaTime, m_Window);
		}
}
void GameManager::InitializeGame()
{
	m_Clock = new sf::Clock;
	m_Player = new Player(this);
	//worldGenE(0, enemies, world1);
	worldGenE(0, enemies, world2);
	m_DeathMenu = new DeathMenu(*this);

	
}
void GameManager::RestartGame()
{

	
	
	//ni¿ej do zmiany poziomu 
	/*for (auto& background : close_background) {
		delete background;
	}
	for (auto& background : far_background) {
		delete background;
	}
	for (auto& platform : platforms) {
		delete platform;
	}
	for (auto& ambient : f_ambients) {
		delete ambient;
	}
	for (auto& ambient : b_ambients) {
		delete ambient;
	}*/
	/*far_background.clear();
	close_background.clear();
	b_ambients.clear();
	f_ambients.clear();
	
	*/

	for (auto enemy : enemies) {
		delete enemy;
	}
	
	
	enemies.clear();
	delete m_Clock;
	delete m_Player;
	delete m_Enemy;
	delete m_DeathMenu;
	
}
void GameManager::loadWorld1()
{

	tie(platforms, f_ambients, b_ambients, close_background, platRects) = worldGen(0, platforms, f_ambients, b_ambients, close_background, platRects, world1);

	far_background.push_back(new Ambient(this, "Sky", { 0,440 }, { 10,5.25 }, 4,1));
	far_background.push_back(new Ambient(this, "MoutainsFar", { 0,440 }, { 6,5.25 },4, 0.9));
	far_background.push_back(new Ambient(this, "MoutainsClose", { 0,440 }, { 6,5.25 },4 ,0.8));
	far_background.push_back(new Ambient(this, "cloudsMidde", { 0,440 }, { 6,5.25 },4 ,0.7));
	far_background.push_back(new Ambient(this, "Hill", { 0,440 }, { 6,5.25 },4 ,0.6));
	far_background.push_back(new Ambient(this, "cloudsFront", { 0,440 }, { 6,5.25 },4 ,0.5));
}
void GameManager::loadWorld2()
{
	Color color(220, 80,20);
	tie(platforms, f_ambients, b_ambients, close_background, platRects) = worldGen(0, platforms, f_ambients, b_ambients, close_background, platRects, world2);

	far_background.push_back(new Ambient(this, "Sky2",	{ 0,0 }, { 1.2,1 },2 ,1));
	far_background.push_back(new Ambient(this, "Tree1", { 0,0 }, { 1.5,1 },2, 0.95));
	far_background.push_back(new Ambient(this, "Tree2", { 0,0 }, { 1.5,1 },2, 0.9));
	far_background.push_back(new Ambient(this, "Tree3", { 0,0 }, { 1.5,1 },2 ,0.85));
	far_background.push_back(new Ambient(this, "Fog6",	{ 0,0 }, { 1.6,1 },2 ,0.8));	
	far_background.push_back(new Ambient(this, "Trees", { 0,0 }, { 1,1 },2 ,0.65));
	far_background.push_back(new Ambient(this, "Grasy", { 0,0 }, { 3,1 },2 ,0.65));

	for (auto& plat : platforms)
	{
		plat->setColor(color);
	}
	for (auto& amb : b_ambients)
	{
		amb->setColor(color);
	}
	for (auto& back : close_background)
	{
		back->setColor(color);
	}

		
}
tuple<vector<Platform*>, vector<Ambient*>, vector<Ambient*>, vector<Ambient*>, vector<PlatRects*>> GameManager::worldGen(int starting_pos, vector<Platform*>& pvec, vector<Ambient*>& favec, vector<Ambient*>& bavec, vector<Ambient*>& bvec, vector<PlatRects*> rect, vector<vector<vector<int>>>& in_vec)
{
	Vector2f scale1 = { 2,2 };
	Vector2f scale = { 2,2 }, scale2 = { 3,2 };
	int current_s_pos=0;
	Vector2f platsize = { 0,0 };
	for (int i = 0; i < in_vec.size(); i++)
	{
		float f_starting_pos = starting_pos;
		for (int j = 0; j < in_vec[i].size(); j++)
		{
			float y = 80;
			int h;
	
			switch (in_vec[i][j][0])
			{
			case 0:
				break;
			case 1:
				pvec.push_back(new Platform(this, "Grass", { f_starting_pos ,y * i }, scale1));
				platsize.x = platsize.x + 80;
				break;
			case 2:
			{
				platsize.x = 0;
				pvec.push_back(new Platform(this, "CliffRight", { f_starting_pos ,y * i }, scale1));
				current_s_pos = f_starting_pos;
				//cout << current_s_pos <<" "<<y*i << endl;
				platsize.x = platsize.x + 80;
				break;
			}
			case 3:
				pvec.push_back(new Platform(this, "CliffRockRight", { f_starting_pos,y * i }, scale1));
				break;
			case 4:
				pvec.push_back(new Platform(this, "CliffLeft", { f_starting_pos - 2, y * i }, scale1));
				platsize.x = platsize.x + 80;
				rect.push_back(new PlatRects(IntRect(current_s_pos, y * i, platsize.x, 60)));
				platsize.x = 0;
				
				break;
			case 5:
				pvec.push_back(new Platform(this, "CliffRockLeft", { f_starting_pos - 2,y * i }, scale1));
				break;
			case 6:
				pvec.push_back(new Platform(this, "PlatSmall", { f_starting_pos - 1,y * i }, scale1));
				rect.push_back(new PlatRects(IntRect(f_starting_pos - 1, y * i, 40 * scale1.x, 39 * scale1.y)));
				break;
			case 7:
				pvec.push_back(new Platform(this, "PlatBig", { f_starting_pos - 10,y * i }, scale1));
				rect.push_back(new PlatRects(IntRect(f_starting_pos - 1, y * i, 98 * scale1.x, 76 * scale1.y)));
				break;
			case 8:
				pvec.push_back(new Platform(this, "PlatL", { f_starting_pos - 1,y * i - 30 }, { 2,1 }));
				current_s_pos = f_starting_pos;
				platsize.x += 59 * scale.x;
				break;
			case 9:
				for (int k = 0; k < 4; k++)
				{
					pvec.push_back(new Platform(this, "PlatM", { f_starting_pos + k * 16 - 1,y * i - 30 }, { 2,1 }));
					platsize.x += 16 * 4 * scale1.x;
				}

				break;
			case 10:
				pvec.push_back(new Platform(this, "PlatR", { f_starting_pos - 2,y * i - 30 }, { 2,1 }));
				platsize.x += 59 * scale1.x;
				rect.push_back(new PlatRects(IntRect(current_s_pos, y * i - 30, platsize.x, 60)));
				break;
			case 11:
				pvec.push_back(new Platform(this, "PlatRockBig", { f_starting_pos,y * i - 20 }, scale1));
				rect.push_back(new PlatRects(IntRect(f_starting_pos, y * i - 20, 48 * scale1.x, 32 * scale1.y)));
				break;
			case 12:
				pvec.push_back(new Platform(this, "PlatRockSmall", { f_starting_pos,y * i - 20 }, scale1));
				rect.push_back(new PlatRects(IntRect(f_starting_pos, y * i - 20, 32 * scale1.x, 32 * scale1.y)));
				break;
			}

			switch (in_vec[i][j][1])
			{
			case 0:
				break;
			case 1:
				favec.push_back(new Ambient(this, "FloorBush", { f_starting_pos,y * i - 12 }, scale2));
				break;
			case 2:
				favec.push_back(new Ambient(this, "FloorRock", { f_starting_pos,y * i - 8 }, scale2));
				break;
			case 3:
				favec.push_back(new Ambient(this, "FloorRockGrass", { f_starting_pos,y * i - 35 }, scale2));
				break;
			case 4:
				favec.push_back(new Ambient(this, "FloorRockBush", { f_starting_pos,y * i - 40 }, scale2));
				break;
			case 5:
				favec.push_back(new Ambient(this, "FloorRockGrass", { f_starting_pos,y * i - 20 }, scale2));
				break;
			case 6:
				favec.push_back(new Ambient(this, "FloorRockMoss", { f_starting_pos,y * i - 20 }, scale2));
				break;
			case 7:
				if (j % 2 == 0)
				{
					favec.push_back(new Ambient(this, "Tree", { f_starting_pos - 60,y * i - 100 }, { 2,2 }));
					favec.push_back(new Ambient(this, "Grass", { f_starting_pos,y * i + 80 }, scale2));
				}
				else
					bavec.push_back(new Ambient(this, "Tree", { f_starting_pos - 60,y * i - 100 }, { 2,2 }));
				break;
			case 8:
				bavec.push_back(new Ambient(this, "FenceLeft", { f_starting_pos,y * i + 25 }, scale1));
				break;
			case 9:
				bavec.push_back(new Ambient(this, "FenceMiddle", { f_starting_pos - 1,y * i + 25 }, scale1));
				break;
			case 10:
				bavec.push_back(new Ambient(this, "FenceRight", { f_starting_pos - 17,y * i + 25 }, scale1));
				break;
			}

			switch (in_vec[i][j][2])
			{
			case 0:
				break;
			case 1:
				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
				break;
			case 2:
				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
				bvec.push_back(new Ambient(this, "BackBush", { f_starting_pos - 1,y * i - 5 }, scale1));
				break;
			case 3:
				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
				bvec.push_back(new Ambient(this, "BackRock", { f_starting_pos - 1,y * i - 5 }, scale1));
				break;
			case 4:
				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
				bvec.push_back(new Ambient(this, "BackRockW", { f_starting_pos - 1,y * i - 5 }, scale1));
				break;
			}

			f_starting_pos += 40 * scale1.x;
		}
	}

	return std::make_tuple(pvec, favec, bavec, bvec, rect);
}
//vector<Platform*> GameManager::worldGenP(int starting_pos, vector<Platform*>& pvec, vector<vector<vector<int>>>& in_vec)
//{
//	Vector2f scale1 = { 2,2 };
//	for (int i = 0; i < in_vec.size(); i++)
//	{
//		float f_starting_pos = starting_pos;
//		for (int j = 0; j < in_vec[i].size(); j++)
//		{
//			float y = 80;
//			float ni = static_cast<float>(i);
//			float nj = static_cast<float>(j);
//
//			switch (in_vec[i][j][0])
//			{
//			case 0:
//				break;
//			case 1:
//				pvec.push_back(new Platform(this, "Grass", { f_starting_pos - 1,y * i }, scale1));
//				break;
//			case 2:
//				pvec.push_back(new Platform(this, "CliffRight", { f_starting_pos ,y * i }, scale1));
//				break;
//			case 3:
//				pvec.push_back(new Platform(this, "CliffRockRight", { f_starting_pos,y * i }, scale1));
//				break;
//			case 4:
//				pvec.push_back(new Platform(this, "CliffLeft", { f_starting_pos - 2,y * i }, scale1));
//				break;
//			case 5:
//				pvec.push_back(new Platform(this, "CliffRockLeft", { f_starting_pos - 2,y * i }, scale1));
//				break;
//			case 6:
//				pvec.push_back(new Platform(this, "PlatSmall", { f_starting_pos - 1,y * i }, scale1));
//				break;
//			case 7:
//				pvec.push_back(new Platform(this, "PlatBig", { f_starting_pos - 10,y * i }, scale1));
//				break;
//			case 8:
//				pvec.push_back(new Platform(this, "PlatL", { f_starting_pos - 1,y * i - 30 }, { 2,1 }));
//				break;
//			case 9:
//				for (int k = 0; k < 4; k++)
//					pvec.push_back(new Platform(this, "PlatM", { f_starting_pos + k * 16 - 1,y * i - 30 }, { 2,1 }));
//				break;
//			case 10:
//				pvec.push_back(new Platform(this, "PlatR", { f_starting_pos - 2,y * i - 30 }, { 2,1 }));
//				break;
//			case 11:
//				pvec.push_back(new Platform(this, "PlatRockBig", { f_starting_pos,y * i - 20 }, scale1));
//				break;
//			case 12:
//				pvec.push_back(new Platform(this, "PlatRockSmall", { f_starting_pos,y * i - 20 }, scale1));
//				break;
//
//			}
//			f_starting_pos += 40 * scale1.x;
//		}
//	}
//	return pvec;
//}
//vector<Ambient*> GameManager::worldGenA(int starting_pos, vector<Ambient*>& favec, vector<Ambient*>& bavec, vector<Ambient*>& bvec, vector<vector<vector<int>>>& in_vec)
//{
//	Vector2f scale1 = { 2,2 }, scale2 = { 3,2 };
//	for (int i = 0; i < in_vec.size(); i++)
//	{
//		float f_starting_pos = starting_pos;
//		for (int j = 0; j < in_vec[i].size(); j++)
//		{
//			float y = 80;
//			float ni = static_cast<float>(i);
//			float nj = static_cast<float>(j);
//
//			switch (in_vec[i][j][2])
//			{
//			case 0:
//				break;
//			case 1:
//				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
//				break;
//			case 2:
//
//				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
//				bvec.push_back(new Ambient(this, "BackBush", { f_starting_pos - 1,y * i - 5 }, scale1));
//				break;
//			case 3:
//				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
//				bvec.push_back(new Ambient(this, "BackRock", { f_starting_pos - 1,y * i - 5 }, scale1));
//
//				break;
//			case 4:
//				bvec.push_back(new Ambient(this, "BackBlack", { f_starting_pos - 1,y * i - 5 }, scale1));
//				bvec.push_back(new Ambient(this, "BackRockW", { f_starting_pos - 1,y * i - 5 }, scale1));
//				break;
//			}
//
//			switch (in_vec[i][j][1])
//			{
//			case 0:
//				break;
//			case 1:
//				favec.push_back(new Ambient(this, "FloorBush", { f_starting_pos,y * i - 12 }, scale2));
//				break;
//			case 2:
//				favec.push_back(new Ambient(this, "FloorRock", { f_starting_pos,y * i - 8 }, scale2));
//				break;
//			case 3:
//				favec.push_back(new Ambient(this, "FloorRockGrass", { f_starting_pos,y * i - 35 }, scale2));
//				break;
//			case 4:
//				favec.push_back(new Ambient(this, "FloorRockBush", { f_starting_pos,y * i - 40 }, scale2));
//				break;
//			case 5:
//				favec.push_back(new Ambient(this, "FloorRockGrass", { f_starting_pos,y * i - 20 }, scale2));
//				break;
//			case 6:
//				favec.push_back(new Ambient(this, "FloorRockMoss", { f_starting_pos,y * i - 20 }, scale2));
//				break;
//			case 7:
//				if (j % 2 == 0)
//				{
//					favec.push_back(new Ambient(this, "Tree", { f_starting_pos - 60,y * i - 100 }, { 2,2 }));
//					favec.push_back(new Ambient(this, "Grass", { f_starting_pos,y * i + 80 }, scale2));
//				}
//				else
//					bavec.push_back(new Ambient(this, "Tree", { f_starting_pos - 60,y * i - 100 }, { 2,2 }));
//				break;
//			case 8:
//				bavec.push_back(new Ambient(this, "FenceLeft", { f_starting_pos,y * i + 25 }, scale1));
//				break;
//			case 9:
//				bavec.push_back(new Ambient(this, "FenceMiddle", { f_starting_pos - 1,y * i + 25 }, scale1));
//				break;
//			case 10:
//				bavec.push_back(new Ambient(this, "FenceRight", { f_starting_pos - 17,y * i + 25 }, scale1));
//				break;
//			}
//
//			f_starting_pos += 40 * scale1.x;
//		}
//	}
//	return favec, bavec, bvec;
//}
vector<Enemy*> GameManager::worldGenE(int starting_pos, vector<Enemy*>& evec, vector<vector<vector<int>>>& in_vec)
{
	for (int i = 0; i < in_vec.size(); i++)
	{
		float f_starting_pos = starting_pos;
		for (int j = 0; j < in_vec[i].size(); j++)
		{
			float y = 80;
			switch (in_vec[i][j][3])
			{
			case 1:
				evec.push_back(new Enemy(1, this, { f_starting_pos,y * i - 60 }));
				break;
			case 2:
				evec.push_back(new Enemy(2, this, { f_starting_pos,y * i - 60 }));
				break;
			case 3:
				evec.push_back(new Enemy(3, this, { f_starting_pos,y * i - 60 }));
				break;

			case 4:
				//evec.push_back(new Enemy(4,this, { f_starting_pos,y * i }));
				break;
			}


			f_starting_pos += 80;
		}
	}
	return evec;
}