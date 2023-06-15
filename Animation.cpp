#include "Animation.h"

Animation::Animation(std::string _name,std::string _filename, sf::Vector2i _frameSize, int _frameCount = 1)
	:frameSize(_frameSize),
	m_iCurrentFrame(0),
	m_iFramesCount(_frameCount),
	m_iTotalTime(0),
	name(_name)
{
	texture = new sf::Texture;
	if(!texture->loadFromFile(_filename));
		
}

Animation::~Animation()
{
	delete texture;
}



void Animation::render(float deltaTime)
{
	m_iTotalTime += deltaTime;
	if (m_iTotalTime >= m_iswitchTime) {
		m_iCurrentFrame++;
		//std::cout << m_iCurrentFrame<< std::endl;
		m_iTotalTime = 0;
		if (m_iCurrentFrame >= m_iFramesCount) {
			m_iCurrentFrame = 0;
		}
	}
	//std::cout << m_iTotalTime << std::endl;
}

void Animation::reload()
{
	m_iCurrentFrame = 0;
}

void Animation::pause()
{
	m_iTotalTime = -1000;
	m_iCurrentFrame = m_iFramesCount - 1;
}


