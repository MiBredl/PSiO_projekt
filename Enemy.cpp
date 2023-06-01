#include "Enemy.h"
#include "GameManager.h"

#include<iostream>



Enemy::Enemy(int type, GameManager* _gameManager)
{
	iFrameTime = 0;
	m_AnimationTime = 0;
	m_GameManager = _gameManager;
	m_TotalTime = 0.4;
	m_HP = 1;
	sprite = new sf::Sprite;
	addAnimation((new AttackAnimation("ATTACK", m_Path + m_EnemyType[type] + "/Attack.png", { 150,150 }, 8))->addHitbox({6,7}));
	addAnimation(new Animation("MOVE", m_Path+m_EnemyType[type]+"/Run.png", {150,150}, 4 ));
	addAnimation(new Animation("IDLE", m_Path+m_EnemyType[type]+"/Idle.png", {150,150}, 4 ));
	addAnimation(new Animation("DEATH", m_Path+m_EnemyType[type]+"/Death.png", {150,150}, 4 ));
	

	setAnimation("MOVE");

	sprite->setScale(1.5, 1.5);
	sprite->setPosition(200, 450);
	
}

void Enemy::movement(float _deltaTime)
{
	if (!isDead) {
		sf::Sprite* _PlayerSprite = m_GameManager->getPlayer()->getSprite();
		if (!m_GameManager->getPlayer()->isDead) {
			if (_PlayerSprite->getGlobalBounds().top >= this->sprite->getGlobalBounds().top 
				&& _PlayerSprite->getGlobalBounds().top <= this->sprite->getGlobalBounds().top + this->sprite->getGlobalBounds().height) {

				if (_PlayerSprite->getGlobalBounds().left + _PlayerSprite->getGlobalBounds().width <= this->sprite->getGlobalBounds().left) {
					direction.x = -1;
					this->sprite->setOrigin(sprite->getGlobalBounds().width / 2, 0.f);
					this->sprite->setScale(-1.5, 1.5);
				}
				if (_PlayerSprite->getGlobalBounds().left >= this->sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width) {
					direction.x = 1;
					this->sprite->setOrigin(0.f, 0.f);
					this->sprite->setScale(1.5, 1.5);
				}
				
				if (sprite->getGlobalBounds().intersects(_PlayerSprite->getGlobalBounds())){
					
					direction.x = 0.f;
						if (!m_AnimationTime) {
							m_AnimationTime = _deltaTime*1000;
							setAnimation("ATTACK");
						}
					AttackAnimation* attackAnimation = dynamic_cast<AttackAnimation*>(getAnimation());
					if (attackAnimation != nullptr) 
					for (int frame : attackAnimation->getHitboxes()) 
						if (frame == attackAnimation->getCurrentFrame()) {
							m_GameManager->getPlayer()->damageManager(0.01);
							break;
						}
				}
				if (direction.x != 0) setAnimation("MOVE");
			}
			else direction = { 0,0 };
			if (m_CurrentAnimation->getName() != "ATTACK" && direction.x == 0.f) setAnimation("IDLE");
			this->sprite->move(direction.x * .07f, 0);
		}
		else setAnimation("IDLE");
	}
	else {
		if (m_CurrentAnimation->getCurrentFrame() != m_CurrentAnimation->getFrameCount()-1) {
			setAnimation("DEATH");
		}
		else m_CurrentAnimation->pause();
	}
}

void Enemy::update(float deltaTime, sf::RenderTarget* window)
{
	movement(deltaTime);
	render(window,deltaTime);

}




