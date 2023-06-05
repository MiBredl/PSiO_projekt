#include "Enemy.h"
#include "GameManager.h"


#include<iostream>



Enemy::Enemy(int type, GameManager* _gameManager, Vector2f _startpos):type(type), gaveExp(false)
{
	iFrameTime = 0;
	m_outputDamage = type;
	m_AnimationTime = 0;
	m_GameManager = _gameManager;
	m_TotalTime = 0.4;
	m_HP = 1;
	sprite = new sf::Sprite;
	loadAnimations();
	/*addAnimation((new AttackAnimation("ATTACK", m_Path + m_EnemyType[type] + "/Attack.png", { 150,150 }, 8))->addHitbox({6,7}));
	addAnimation(new Animation("MOVE", m_Path+m_EnemyType[type]+"/Run.png", {150,150}, 4 ));
	addAnimation(new Animation("IDLE", m_Path+m_EnemyType[type]+"/Idle.png", {150,150}, 4 ));
	addAnimation(new Animation("DEATH", m_Path+m_EnemyType[type]+"/Death.png", {150,150}, 4 ));*/
	

	setAnimation("MOVE");

	sprite->setScale(1.5, 1.5);
	sprite->setPosition(_startpos);
	platforms = m_GameManager->getPlatforms();
}

void Enemy::movement(float _deltaTime)
{
	



	////////////
	if (!isDead) {
		
		sf::Sprite* _PlayerSprite = m_GameManager->getPlayer()->getSprite();
		
		
		if (!m_GameManager->getPlayer()->isDead) {
			if (_PlayerSprite->getGlobalBounds().top+60 >= this->sprite->getGlobalBounds().top 
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
							m_AnimationTime = _deltaTime;
							setAnimation("ATTACK");
						}
					AttackAnimation* attackAnimation = dynamic_cast<AttackAnimation*>(getAnimation());
					if (attackAnimation != nullptr) 
					for (int frame : attackAnimation->getHitboxes()) 
						if (frame == attackAnimation->getCurrentFrame()) {
							m_GameManager->getPlayer()->damageManager(m_outputDamage);
							break;
						}
				}
				else { 
					if (direction.x != 0) setAnimation("MOVE");
					else setAnimation("IDLE");
				}
			}
			else direction.x = 0;
			if (m_CurrentAnimation->getName() != "ATTACK" && direction.x == 0.f) setAnimation("IDLE");
			
		}
		else setAnimation("IDLE");
		this->sprite->move(direction.x * .7f,0 );
	}
	else {
		if (m_CurrentAnimation->getCurrentFrame() != m_CurrentAnimation->getFrameCount()-1) {
			setAnimation("DEATH");
		}
		else m_CurrentAnimation->pause();
	}
	cout << direction.y << "ENEMY DIR" << endl;
}

void Enemy::update(float deltaTime, sf::RenderTarget* window)
{
	movement(deltaTime);
	fallControll(deltaTime);

}

void Enemy::fallControll(float _deltaTime)
{
	platforms = m_GameManager->getPlatforms();
	float _displacement = m_JumpVelocity * _deltaTime + 0.5f * GRAVITY * _deltaTime * _deltaTime;
	//m_isOnGround = false;
	FloatRect _EnemyBounds = sprite->getGlobalBounds();



	if (m_IsFalling) {
		m_isOnPlatform = false;
		if (_displacement > 0) m_IsFalling = true;
		m_JumpVelocity += GRAVITY * _deltaTime;
		//std::cout << _displacement << std::endl;

		sprite->move(0.f, _displacement);

		if (_displacement < 0.f && ( m_isOnPlatform)) m_JumpVelocity = 0.f;

	}

	
	
	if (!m_isOnPlatform  && _displacement > 0.f) {
		m_IsFalling = true;

	}
	for (auto& platform : platforms) {
		FloatRect _PlatformHitbox = platform->getGlobalBounds();

		if (_EnemyBounds.intersects(_PlatformHitbox)) {

			if (_EnemyBounds.top + _EnemyBounds.height >= _PlatformHitbox.top
				&& _EnemyBounds.top <= _PlatformHitbox.top + _PlatformHitbox.height) {
				m_isOnPlatform = true;
				m_IsFalling = false;

				//cout << "top" << endl;
				m_JumpVelocity = 0.f;

			}
			if (_EnemyBounds.top <= _PlatformHitbox.top + _PlatformHitbox.height) {
				if (!m_isOnPlatform) {
					//cout << "bottom" << endl;
					m_IsFalling = true;
					m_JumpVelocity = -JUMP_VELOCITY / 70;
				}
			}
		
		}
		else m_isOnPlatform = false;
	}

}

void Enemy::loadAnimations()
{
	

	switch (type)
	{

	case GAME_ENUMS::ENEMY_TYPE::SKELETON:
		addAnimation((new AttackAnimation("ATTACK", m_Path + m_EnemyType[type] + "/Attack3.png", { 95,57 }, 8))->addHitbox({ 6,7 }));
		addAnimation(new Animation("MOVE", m_Path + m_EnemyType[type] + "/Run3.png", { 45,58 }, 4));
		addAnimation(new Animation("IDLE", m_Path + m_EnemyType[type] + "/Idle3.png", { 45,58 }, 4));
		addAnimation(new Animation("DEATH", m_Path + m_EnemyType[type] + "/Death3.png", { 56,58 }, 4));
		break;
	
	case GAME_ENUMS::ENEMY_TYPE::MUSHROOM:
		addAnimation((new AttackAnimation("ATTACK", m_Path + m_EnemyType[type] + "/Attack3.png", { 64,45 }, 8))->addHitbox({ 6,7 }));
		addAnimation(new Animation("MOVE", m_Path + m_EnemyType[type] + "/Run3.png", { 26,39 }, 8));
		addAnimation(new Animation("IDLE", m_Path + m_EnemyType[type] + "/Idle3.png", { 23,37 }, 4));
		addAnimation(new Animation("DEATH", m_Path + m_EnemyType[type] + "/Death3.png", { 26,37 }, 4));
	case GAME_ENUMS::ENEMY_TYPE::GOBLIN:
		addAnimation((new AttackAnimation("ATTACK", m_Path + m_EnemyType[type] + "/Attack3.png", { 88,45 }, 8))->addHitbox({ 6,7 }));
		addAnimation(new Animation("MOVE", m_Path + m_EnemyType[type] + "/Run3.png", { 38,38 }, 8));
		addAnimation(new Animation("IDLE", m_Path + m_EnemyType[type] + "/Idle3.png", { 33,36 }, 4));
		addAnimation(new Animation("DEATH", m_Path + m_EnemyType[type] + "/Death3.png", { 52,37 }, 4));
	}
}




