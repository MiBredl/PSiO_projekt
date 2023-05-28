#include "Enemy.h"
#include "GameManager.h"

#include<iostream>



Enemy::Enemy(int type, GameManager* _gameManager)
{
	m_GameManager = _gameManager;
	sprite = new sf::Sprite;
	addAnimation( new Animation("ATTACK", m_Path+m_EnemyType[type]+"/Attack.png", {150,150}, 8 ));
	addAnimation(new Animation("MOVE", m_Path+m_EnemyType[type]+"/Run.png", {150,150}, 4 ));
	addAnimation(new Animation("IDLE", m_Path+m_EnemyType[type]+"/Idle.png", {150,150}, 4 ));
	

	setAnimation("MOVE");

	sprite->setScale(1.5, 1.5);
	sprite->setPosition(820, 850);
	
}

void Enemy::movement()
{
	sf::Sprite* _PlayerSprite=m_GameManager->getPlayer()->getSprite();
	
	if (_PlayerSprite->getGlobalBounds().top>=this->sprite->getGlobalBounds().top && _PlayerSprite->getGlobalBounds().top<=this->sprite->getGlobalBounds().top+ this->sprite->getGlobalBounds().height) {
		
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
		if (sprite->getGlobalBounds().intersects(_PlayerSprite->getGlobalBounds())) {

			setAnimation("ATTACK");
			direction.x = 0.f;
		}
		else if(direction.x!= 0) setAnimation("MOVE");
	}
	else {
		direction.x = 0;
		setAnimation("IDLE");
	}
	this->sprite->move(direction.x * .07f, 0);
}

void Enemy::update(float deltaTime, sf::RenderTarget* window)
{
	movement();
	render(window,deltaTime);

}




