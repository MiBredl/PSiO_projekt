#include "NPC.h"
#include <iostream>




void NPC::render(sf::RenderTarget* window,float deltaTime)
{


	m_CurrentAnimation->render(deltaTime);
	this->sprite->setTextureRect(m_CurrentAnimation->getFrame());
	
	window->draw(*sprite);
}



void NPC::setAnimation(std::string _mapKey)
{

	if (this->m_Animations.find(_mapKey) == this->m_Animations.end()) return;
	if (this->m_CurrentAnimation != nullptr)
	if (this->m_CurrentAnimation->getName() ==_mapKey) return;
	
	this->m_CurrentAnimation = this->m_Animations[_mapKey];
	this->m_CurrentAnimation->reload();
	this->sprite->setTexture(*this->m_CurrentAnimation->getTexture());
	

}

void NPC::addAnimation( Animation* _animation)
{
	if (this->m_Animations.find(_animation->getName()) != this->m_Animations.end()) return;

	this->m_Animations.insert(std::pair<std::string, Animation*>(_animation->getName(), _animation));


}

