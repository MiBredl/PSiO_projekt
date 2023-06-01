#include "GameManager.h"
#include<iostream>

GameManager::GameManager()
{
	View view();
	m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"SUS SOULS");
	m_Clock = new sf::Clock;
	m_Player = new Player(this);
	m_Enemy = new Enemy(1,this);
	m_Menu = new Menu();

	worldGenP(0, platforms, world1);
	worldGenA(0, f_ambients, b_ambients, background, world1);
	update();
}

void GameManager::update()
{
	while (m_Window->isOpen()) {
		eventManager();
		m_Window->clear();
		float deltaTime = getElapsedTime().asSeconds();
		for (const auto& bground : background)
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
		if (m_Player != nullptr) {
			m_Player->update(deltaTime, m_Window);
		}
		if (m_Enemy != nullptr) {
			m_Enemy->update(deltaTime, m_Window);
		}

		//Jako ostatnie do renderu
		for (const auto& front_amb : f_ambients)
		{
			front_amb->renderPlat(m_Window);
		}
		if (m_Menu != nullptr) {		
			m_Menu->update(m_Window);
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
vector<Platform*> GameManager::worldGenP(int starting_pos, vector<Platform*>& pvec, vector<vector<vector<int>>>& in_vec)
{
	Vector2f scale1 = { 2,2 };
	for (int i = 0; i < in_vec.size(); i++)
	{
		float f_starting_pos = starting_pos;
		for (int j = 0; j < in_vec[i].size(); j++)
		{
			float y = 80;
			float ni = static_cast<float>(i);
			float nj = static_cast<float>(j);

			switch (in_vec[i][j][0])
			{
			case 0:
				break;
			case 1:
				pvec.push_back(new Platform(this, "Grass", { f_starting_pos,y * i }, scale1));
				break;
			case 2:
				pvec.push_back(new Platform(this, "CliffRight", { f_starting_pos,y * i }, scale1));
				break;
			case 3:
				pvec.push_back(new Platform(this, "CliffRockRight", { f_starting_pos,y * i }, scale1));
				break;
			case 4:
				pvec.push_back(new Platform(this, "CliffLeft", { f_starting_pos,y * i }, scale1));
				break;
			case 5:
				pvec.push_back(new Platform(this, "CliffRockLeft", { f_starting_pos,y * i }, scale1));
				break;
			case 6:
				pvec.push_back(new Platform(this, "PlatSmall", { f_starting_pos,y * i }, scale1));
				break;
			case 7:
				pvec.push_back(new Platform(this, "PlatBig", { f_starting_pos - 10,y * i }, scale1));
				break;
			case 8:
				pvec.push_back(new Platform(this, "PlatL", { f_starting_pos,y * i - 20 }, { 2,1 }));
				break;
			case 9:
				for (int k = 0; k < 4; k++)
					pvec.push_back(new Platform(this, "PlatM", { f_starting_pos + k * 16,y * i - 20 }, { 2,1 }));
				break;
			case 10:
				pvec.push_back(new Platform(this, "PlatR", { f_starting_pos,y * i - 20 }, { 2,1 }));
				break;
			case 11:
				pvec.push_back(new Platform(this, "PlatRockBig", { f_starting_pos,y * i - 20 }, scale1));
				break;
			case 12:
				pvec.push_back(new Platform(this, "PlatRockSmall", { f_starting_pos,y * i - 20 }, scale1));
				break;

			}
			f_starting_pos += 40 * scale1.x;
		}
	}
	return pvec;
}

vector<Ambient*> GameManager::worldGenA(int starting_pos, vector<Ambient*>& favec, vector<Ambient*>& bavec, vector<Ambient*>& bvec, vector<vector<vector<int>>>& in_vec)
{
	Vector2f scale1 = { 2,2 }, scale2 = { 3,2 };
	for (int i = 0; i < in_vec.size(); i++)
	{
		float f_starting_pos = starting_pos;
		for (int j = 0; j < in_vec[i].size(); j++)
		{
			float y = 80;
			float ni = static_cast<float>(i);
			float nj = static_cast<float>(j);

			switch (in_vec[i][j][2])
			{
			case 0:
				break;
			case 1:
				bvec.push_back(new Ambient(this, "FloorBlack", { f_starting_pos,y * i - 5 }, scale1));
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
					favec.push_back(new Ambient(this, "Tree", { f_starting_pos - 60,y * i - 85 }, { 1.5,1.5 }));
				else
					bavec.push_back(new Ambient(this, "Tree", { f_starting_pos - 60,y * i - 85 }, { 1.5,1.5 }));
				break;
			case 8:
				favec.push_back(new Ambient(this, "FenceLeft", { f_starting_pos,y * i }, scale1));
				break;
			case 9:
				favec.push_back(new Ambient(this, "FenceMiddle", { f_starting_pos,y * i }, scale1));
				break;
			case 10:
				favec.push_back(new Ambient(this, "FenceRight", { f_starting_pos,y * i }, scale1));
				break;
			}

			f_starting_pos += 40 * scale1.x;
		}
	}
	return favec, bavec, bvec;
}
