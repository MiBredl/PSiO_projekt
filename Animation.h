#pragma once
#include"libraries.h"
class Animation
{
public:
	Animation(std::string,std::string,sf::Vector2i,int);
	virtual ~Animation() {};
	sf::Texture* getTexture() {
		return texture;
	}
	sf::IntRect getFrame() {
		return { 
			m_iCurrentFrame * frameSize.x,
			0,
			frameSize.x,
			frameSize.y 
		};
	}
	std::string getName() {
		return name;
	}

	void render(float);
	void reload();
	int getCurrentFrame() {
		return m_iCurrentFrame;
	}
private:
	const float m_iswitchTime = 0.045f;
	sf::Texture* texture;
	std::string name;
	float m_iTotalTime;
	int m_iFramesCount,
		m_iCurrentFrame
		;
	
	sf::Vector2i frameSize;
};

