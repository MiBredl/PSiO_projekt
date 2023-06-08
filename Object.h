#pragma once
#include "libraries.h"
#include "Textures.h"

class Object
{
protected:
	class GameManager* m_GameManager;
	class WorldGenerator* m_WorldGenerator;
	Textures* current_Texture;
	Sprite* sprite;
	map<string, Textures*> m_Texture;
public:
	void renderPlat(RenderWindow* window);
	void setTextures(string);
	void addTextures(Textures*);
	void setColor(Color&);
	FloatRect getGlobalBounds() {
		return this->sprite->getGlobalBounds();
	}
	GameManager* getGameMeneger() {
		return m_GameManager;
	}
	Textures* getTextures() {
		return current_Texture;
	}

};

