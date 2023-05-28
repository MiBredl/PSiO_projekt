
#include "Player.h"
#include "GameManager.h"
#include<iostream>


Player::Player(GameManager* _gameManager) :playerSpeed(.1f)
{
	//addAnimation("IDLE", new Animation("textures/player/Colour1/NoOutline/120x80_PNGSheets/_Idle.png", {120,80},10));
	//
	m_GameManager = _gameManager;
	sprite = new sf::Sprite;

	
	loadAnimations();
	setAnimation("IDLE");


	sprite->setScale(2, 2);
	
	sprite->setPosition(300, 400);

}



void Player::jumpControl(float deltaTime)
{

	float _displacement = m_JumpVelocity*deltaTime+0.5f*GRAVITY*deltaTime*deltaTime;
	bool _isOnGround = false;

	if (m_IsJumping || m_IsFalling) {
		if (_displacement > 0) m_IsFalling = true;
		m_JumpVelocity += GRAVITY * deltaTime;
		//std::cout << _displacement << std::endl;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		if (!m_IsJumping && !m_IsFalling) {
			m_IsJumping = true;
			m_JumpVelocity = JUMP_VELOCITY;
		}

	}
	
}


void Player::movement()
{
	direction = { 0,0 };

	
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
	//	direction.y = -1;
	//	//setAnimation("JUMP");
	//}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direction.y = 1;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction.x = -1;
		sprite->setOrigin(sprite->getGlobalBounds().width/2,0.f);
		sprite->setScale(-2,2);
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

	
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!m_IsFalling&&!m_IsJumping) {
		setAnimation("ATTACK");
		AttackAnimation* attackAnimation= dynamic_cast<AttackAnimation*>(getAnimation());
		
		for(const int frame : attackAnimation->getHitboxes()){
			if (frame == attackAnimation->getCurrentFrame()) {
				/*std::cout << "HIIIIIIIIIIIIIT" << std::endl;
				std::cout <<"frame "<<frame << std::endl;*/

				break;
			}
		}
	}
	if (m_IsFalling) {
		setAnimation("FALL");
	}
	else if (m_IsJumping ) {
		setAnimation("JUMP");
	}
	 
}

void Player::loadAnimations()
{
	addAnimation( new Animation("RUN","textures/player/Colour1/NoOutline/120x80_PNGSheets/Run3.png", { 32,38 }, 10));
	addAnimation( new Animation("DEATH","textures/player/Colour1/NoOutline/120x80_PNGSheets/_Death.png", { 120,37 }, 10));
	addAnimation( new Animation("IDLE","textures/player/Colour1/NoOutline/120x80_PNGSheets/Idle3.png", { 19,37 }, 10));
	addAnimation( new Animation("JUMP","textures/player/Colour1/NoOutline/120x80_PNGSheets/Jump3.png", { 23,37 }, 3));
	addAnimation( new Animation("FALL","textures/player/Colour1/NoOutline/120x80_PNGSheets/Fall3.png", { 27,37 }, 3));
	addAnimation( (new AttackAnimation("ATTACK","textures/player/Colour1/NoOutline/120x80_PNGSheets/_AttackCombo.png", { 120,37 }, 10))->addHitbox({ 1,2,6,7 }));
}



void Player::update(float deltaTime, sf::RenderTarget* window)
{

	jumpControl(deltaTime);
	movement();
	render(window, deltaTime);
}
