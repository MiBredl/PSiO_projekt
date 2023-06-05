#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
using namespace sf;
namespace GAME_ENUMS {
	enum GAMESTATE{ PLAYING, RESTART, PAUSED, DEAD };
	enum ENEMY_TYPE {x,SKELETON,MUSHROOM,GOBLIN};
}
const int WINDOW_WIDTH =1920;
const int WINDOW_HEIGHT = 1080;