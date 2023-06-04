
#include "Player.h"
#include "Healthbar.h"
#include "GameManager.h"


Player::Player(GameManager* _gameManager) : playerSpeed(5){

	
	iFrameTime = 0;
	m_AnimationTime = 0;
	m_GameManager = _gameManager;
	
	sprite = new sf::Sprite;
	this->m_HP = 3;
	m_TotalTime = 0.4;
	loadAnimations();
	setAnimation("IDLE");

	sprite->setScale(2.5, 2.5);
	
	sprite->setPosition(400, 0);


	for (int i = 0; i < m_HP; i++) {
		sf::Vector2i pixelPos(i * 25, 0);
		sf::Vector2f worldPos = m_GameManager->getWindow()->mapPixelToCoords(pixelPos);
		m_HealthPoints.push_back(new HealthBar(worldPos));
	}
	
}
void Player::viewupdate()
{
	m_HealthPoints.clear();

	for (int i = 0; i < m_HP; i++) {
		sf::Vector2i pixelPos(i * 25, 0);
		sf::Vector2f worldPos = m_GameManager->getWindow()->mapPixelToCoords(pixelPos);
		m_HealthPoints.push_back(new HealthBar(worldPos));
	}
}


void Player::jumpControl(float deltaTime)
{
	platforms = m_GameManager->getPlatforms();
	float _displacement = m_JumpVelocity*deltaTime+0.5f*GRAVITY*deltaTime*deltaTime;
	m_isOnGround = false;
	
	FloatRect _PlayerHitbox = this->sprite->getGlobalBounds();
	


	if (m_IsJumping || m_IsFalling) {
		m_isOnPlatform = false;
		if (_displacement > 0) m_IsFalling = true;
		m_JumpVelocity += GRAVITY * deltaTime;
		//std::cout << _displacement << std::endl;
		
		sprite->move(0.f,_displacement);

		if (_displacement < 0.f && (m_isOnGround || m_isOnPlatform)) m_JumpVelocity = 0.f;

	}
	if (m_IsFalling) {
		if (sprite->getPosition().y >= WINDOW_HEIGHT-sprite->getGlobalBounds().height) {
			m_JumpVelocity = 0.f;
			m_IsFalling = false;
			m_IsJumping = false;
			m_isOnGround = true;
		}
		

	}
	else if (!m_IsJumping && !m_IsFalling) {
		if (sprite->getPosition().y >= WINDOW_HEIGHT - sprite->getGlobalBounds().height) {
			m_isOnGround = true;
		}
	}
	if ((!m_isOnPlatform || !m_isOnGround) && _displacement > 0.f) {
		m_IsFalling = true;
	
	}
	for (auto& platform : platforms) {
		FloatRect _PlatformHitbox = platform->getGlobalBounds();

		if (_PlayerHitbox.intersects(_PlatformHitbox)) {

				 if (_PlayerHitbox.top + _PlayerHitbox.height >= _PlatformHitbox.top 
					&&_PlayerHitbox.top<=_PlatformHitbox.top+_PlatformHitbox.height-100) {
					m_isOnPlatform = true;
					m_IsFalling = false;
					m_IsJumping = false;
					//cout << "top" << endl;
					m_JumpVelocity = 0.f;
					
				}
				 if (_PlayerHitbox.top <= _PlatformHitbox.top + _PlatformHitbox.height) {
					if (!m_isOnPlatform) { 
						//cout << "bottom" << endl;
						m_IsFalling = true;
					m_JumpVelocity = -JUMP_VELOCITY/70;
					}
				 }
				 if ((_PlayerHitbox.left <= _PlatformHitbox.left + _PlatformHitbox.width + 20
						 && _PlayerHitbox.left + _PlayerHitbox.width >= _PlatformHitbox.left - 20)) {
					 cout << "side" << endl;
					 m_SideCollision = true;
				 }
		}
			
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)&&!isDead&&(!m_IsFalling||!m_IsJumping)) {
		if (!m_IsJumping && !m_IsFalling) {
			m_IsJumping = true;
			m_JumpVelocity = JUMP_VELOCITY;
		}

	}
	
	//std::cout <<"jv: " << m_JumpVelocity<< std::endl;
	//std::cout <<"fall: " << m_IsFalling<< std::endl;
	m_SideCollision = false;
}


void Player::movement(float _deltaTime)
{
	direction = { 0,0 };

	
	if (!isDead) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			direction.y = 1;

		}
		if (!m_SideCollision) {
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				direction.x = -1;
				sprite->setOrigin(sprite->getGlobalBounds().width / 2, 0.f);
				sprite->setScale(-2.5, 2.5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				direction.x = 1;
				sprite->setOrigin(0.f, 0.f);
				sprite->setScale(2.5, 2.5);
			}
		}
		if (direction == sf::Vector2i(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setAnimation("IDLE");
		}
		else if (direction != sf::Vector2i(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setAnimation("RUN");
			sprite->move(direction.x * playerSpeed, 0);
		}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_IsFalling && !m_IsJumping) {
				if (!m_AnimationTime) {
					m_AnimationTime = _deltaTime;
					setAnimation("ATTACK");
					for (auto& enemy : m_GameManager->getEnemies()) {
						if (sprite->getGlobalBounds().intersects(enemy->getSprite()->getGlobalBounds())) {

							AttackAnimation* attackAnimation = dynamic_cast<AttackAnimation*>(getAnimation());
							if (attackAnimation != nullptr) {
								std::cout << attackAnimation->getHitboxes().size() << std::endl;
								for (int frame : attackAnimation->getHitboxes()) {
									std::cout << frame << " " << attackAnimation->getCurrentFrame() << std::endl;
									if (frame == attackAnimation->getCurrentFrame()) {
										enemy->damageManager(1);

										break;
									}

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
		m_GameManager->setGameState(GAME_ENUMS::GAMESTATE::DEAD);
		if (m_CurrentAnimation->getCurrentFrame() != m_CurrentAnimation->getFrameCount()-1) {
			setAnimation("DEATH");
		}
		else m_CurrentAnimation->pause();
	}
	cout <<"animTime" << m_AnimationTime << endl;
}



void Player::collider()
{

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
	//PlatformDetection();
	viewupdate();
	HealthBarManager();
	jumpControl(deltaTime);
	movement(deltaTime);
	
}

void Player::HealthBarManager()
{
	if (m_HealthPoints.size() > 0) {
		if (isHit) {
			m_HealthPoints.pop_back();
		}
		for (auto& hp : m_HealthPoints) {
			hp->render(m_GameManager->getWindow());
		}
	}
}


