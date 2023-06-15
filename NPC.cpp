#include "NPC.h"


void NPC::render(sf::RenderTarget* window,float deltaTime)
{


	m_CurrentAnimation->render(deltaTime);
	this->sprite->setTextureRect(m_CurrentAnimation->getFrame());
	if (!iFrameTime) { sprite->setColor(Color(255, 255, 255, 255)); }
	else {
		sprite->setColor(Color(255, 0, 0, 255));
		iFrameTime--;
	}
	if (m_AnimationTime) {
		m_AnimationTime--;
	}
	if (isInvincible) sprite->setColor(Color::Green);
	window->draw(*sprite);
}



void NPC::setAnimation(std::string _mapKey)
{

	if (this->m_Animations.find(_mapKey) == this->m_Animations.end()) return;
	if (this->m_CurrentAnimation != nullptr)
	if (this->m_CurrentAnimation->getName() ==_mapKey) return;
	//std::cout << _mapKey << std::endl;
	this->m_CurrentAnimation = this->m_Animations[_mapKey];
	this->m_CurrentAnimation->reload();
	this->sprite->setTexture(*this->m_CurrentAnimation->getTexture());
	
	
}

void NPC::addAnimation( Animation* _animation)
{
	if (this->m_Animations.find(_animation->getName()) != this->m_Animations.end()) return;

	this->m_Animations.insert(std::pair<std::string, Animation*>(_animation->getName(), _animation));


}

void NPC::damageManager(float damage)
{
	isHit = false;
	
	if (!iFrameTime) {
		
		iFrameTime = 45;
		m_DamageTaken = damage;
		m_HP -= damage;
		if (m_HP < 0) m_HP = 0;
		
		isHit = true;
		if (m_HP <= 0) {
			isDead = true;
		}
	}

}

