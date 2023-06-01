
#include "Player.h"
#include "GameManager.h"
#include<iostream>

Player::Player(GameManager* _gameManager) : playerSpeed(.1f){

	
	iFrameTime = 0;
	m_AnimationTime = 0;
	m_GameManager = _gameManager;
	sprite = new sf::Sprite;
	this->m_HP = 3;
	m_TotalTime = 0.4;
	loadAnimations();
	setAnimation("IDLE");


	sprite->setScale(2, 2);
	
	sprite->setPosition(300, 450);

}



void Player::jumpControl(float deltaTime)
{

	float _displacement = m_JumpVelocity*deltaTime+0.5f*GRAVITY*deltaTime*deltaTime;
	bool _isOnGround = false;

	if (m_IsJumping || m_IsFalling) {
		if (_displacement > 0) m_IsFalling = true;
		m_JumpVelocity += GRAVITY * deltaTime;
		std::cout << _displacement << std::endl;

		sprite->move(0.f,_displacement);

		if (_displacement < 0.f && _isOnGround) m_JumpVelocity = 0.f;

	}
	if (m_IsFalling) {
		if (sprite->getPosition().y >= WINDOW_HEIGHT-sprite->getGlobalBounds().height) {
			m_JumpVelocity = 0.f;
			m_IsFalling = false;
			m_IsJumping = false;
			_isOnGround = true;
		}

	}
	else if (!m_IsJumping && !m_IsFalling) {
		if (sprite->getPosition().y >= WINDOW_HEIGHT - sprite->getGlobalBounds().height) {
			_isOnGround = true;
		}
	}
	if (!_isOnGround && _displacement > 0.f) {
		m_IsFalling = true;
	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)&&!isDead) {
		if (!m_IsJumping && !m_IsFalling) {
			m_IsJumping = true;
			m_JumpVelocity = JUMP_VELOCITY;
		}

	}
	
}


void Player::movement(float _deltaTime)
{
	direction = { 0,0 };
	auto _enemyBounds = m_GameManager->getEnemy()->getSprite()->getGlobalBounds();
	Enemy* _enemy = m_GameManager->getEnemy();
	if (!isDead) {
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			direction.y = 1;

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction.x = -1;
			sprite->setOrigin(sprite->getGlobalBounds().width / 2, 0.f);
			sprite->setScale(-2, 2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction.x = 1;
			sprite->setOrigin(0.f, 0.f);
			sprite->setScale(2, 2);
		}
		if (direction == sf::Vector2i(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setAnimation("IDLE");
		}
		else if (direction != sf::Vector2i(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setAnimation("RUN");
			sprite->move(direction.x * playerSpeed, direction.y * playerSpeed);
		}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_IsFalling && !m_IsJumping) {
				if (!m_AnimationTime) {
					m_AnimationTime = _deltaTime *1150;
					setAnimation("ATTACK");
					if (sprite->getGlobalBounds().intersects(_enemyBounds)) {

						AttackAnimation* attackAnimation = dynamic_cast<AttackAnimation*>(getAnimation());
						if (attackAnimation != nullptr) {
							std::cout <<  attackAnimation->getHitboxes().size() << std::endl;
							for (int frame : attackAnimation->getHitboxes()) {
								std::cout << frame << " " << attackAnimation->getCurrentFrame() << std::endl;
								if (frame == attackAnimation->getCurrentFrame()) {
									_enemy->damageManager(1);
									
									break;
								}

							}
						}
					}
				}
			}
		
		if (m_IsFalling) {
			setAnimation("FALL");
		}
		else if (m_IsJumping) {
			setAnimation("JUMP");
		}
	}
	else {
		if (m_CurrentAnimation->getCurrentFrame() != m_CurrentAnimation->getFrameCount()-1) {
			setAnimation("DEATH");
		}
		else m_CurrentAnimation->pause();
	}
}



void Player::loadAnimations()
{
	addAnimation( new Animation("RUN","textures/player/Colour1/NoOutline/120x80_PNGSheets/Run3.png", { 32,38 }, 10));
	addAnimation( new Animation("DEATH","textures/player/Colour1/NoOutline/120x80_PNGSheets/Death3.png", { 120,39 }, 10));
	addAnimation( new Animation("IDLE","textures/player/Colour1/NoOutline/120x80_PNGSheets/Idle3.png", { 19,37 }, 10));
	addAnimation( new Animation("JUMP","textures/player/Colour1/NoOutline/120x80_PNGSheets/Jump3.png", { 23,37 }, 3));
	addAnimation( new Animation("FALL","textures/player/Colour1/NoOutline/120x80_PNGSheets/Fall3.png", { 27,37 }, 3));
	addAnimation( (new AttackAnimation("ATTACK","textures/player/Colour1/NoOutline/120x80_PNGSheets/Attack3.png", { 71,42 }, 4))->addHitbox({ 1,2 }));
}



void Player::update(float deltaTime, sf::RenderTarget* window)
{
	render(window, deltaTime);
	jumpControl(deltaTime);
	movement(deltaTime);
	
}
