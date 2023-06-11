
#include "Player.h"

#include "GameManager.h"


Player::Player(GameManager* _gameManager) : playerSpeed(5)
{


	iFrameTime = 0;
	m_AnimationTime = 0;
	m_GameManager = _gameManager;
	m_outputDamage = 1;
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
	platforms = m_GameManager->getPlatRects();
	float _displacement = m_JumpVelocity * deltaTime + 0.5f * GRAVITY * deltaTime * deltaTime;
	m_isOnGround = false;
	if (m_SideCollision) m_CollisionTime--;
	FloatRect _PlayerHitbox = this->sprite->getGlobalBounds();
	FloatRect _nextBounds = _PlayerHitbox;
	_nextBounds.left += playerSpeed * direction.x;
	_nextBounds.top += _displacement;




	if (m_SideCollision && !bounced) {
		bounced = true;
		direction.x = -direction.x;
	}
	if (m_IsJumping || m_IsFalling) {
		m_isOnPlatform = false;
		if (_displacement > 0) m_IsFalling = true;
		m_JumpVelocity += GRAVITY * deltaTime;
		//std::cout << _displacement << std::endl;

		sprite->move(0.f, _displacement);

		if (_displacement < 0.f && (m_isOnGround || m_isOnPlatform)) m_JumpVelocity = 0.f;

	}
	if (m_IsFalling) {
		if (sprite->getPosition().y >= WINDOW_HEIGHT - sprite->getGlobalBounds().height) {
			m_JumpVelocity = 0.f;
			m_IsFalling = false;
			m_IsJumping = false;
			m_isOnGround = true;
			m_HP = 0;
			isDead = true;
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
		FloatRect _PlatformHitbox = platform->getRect();


		if (_nextBounds.intersects(_PlatformHitbox)) {



			if (_nextBounds.top + _nextBounds.height >= _PlatformHitbox.top
				&& _nextBounds.top + _nextBounds.height <= _PlatformHitbox.top + 18
				&& _nextBounds.left + _nextBounds.width >= _PlatformHitbox.left
				&& _nextBounds.left <= _PlatformHitbox.left + _PlatformHitbox.width) {
				platform->isActive = true;
				sprite->setPosition(sprite->getPosition().x, platform->getRect().top - _PlayerHitbox.height);
				m_isOnPlatform = true;
				m_IsFalling = false;
				m_IsJumping = false;
				//cout << "top" << endl;
				m_JumpVelocity = 0.f;
				if (platform->getIsMoving()) this->sprite->setPosition(sprite->getPosition().x + platform->getCurrentSpeed(), sprite->getPosition().y);

			}
			else if (_nextBounds.top <= _PlatformHitbox.top + _PlatformHitbox.height
				&& _nextBounds.top >= _PlatformHitbox.top + _PlatformHitbox.height - 10) {

				//cout << "bottom" << endl;
				m_IsFalling = true;
				m_JumpVelocity = -JUMP_VELOCITY / 7;

			}
			else if ((_nextBounds.left < _PlatformHitbox.left
				&& _nextBounds.left + _nextBounds.width <= _PlatformHitbox.left + _PlatformHitbox.width)
				&& (_nextBounds.top< _PlatformHitbox.top + _PlatformHitbox.height
					&& _nextBounds.top + _nextBounds.height>_PlatformHitbox.top)) {


				sprite->setPosition(_PlatformHitbox.left - _PlayerHitbox.width, _PlayerHitbox.top + _displacement);

				//m_SideCollision = true;
				m_CollisionTime = 45;
			}
			else if ((_nextBounds.left > _PlatformHitbox.left
				&& _nextBounds.left + _nextBounds.width >= _PlatformHitbox.left + _PlatformHitbox.width)
				&& (_nextBounds.top< _PlatformHitbox.top + _PlatformHitbox.height
					&& _nextBounds.top + _nextBounds.height>_PlatformHitbox.top)) {

				sprite->setPosition(_PlatformHitbox.left + _PlatformHitbox.width + _PlayerHitbox.width / 2, _PlayerHitbox.top + _displacement);
				//m_SideCollision = true;
				m_CollisionTime = 45;

			}

		}
		else platform->isActive = false;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !isDead && (!m_IsFalling || !m_IsJumping)) {
		if (!m_IsJumping && !m_IsFalling) {
			m_IsJumping = true;
			m_JumpVelocity = JUMP_VELOCITY;
		}

	}
	//if (m_CollisionTime <= 0) m_SideCollision = false;

	//cout << direction.x << endl;
	//cout << m_SideCollision << endl;
	//std::cout <<"jv: " << m_JumpVelocity<< std::endl;
	//std::cout <<"fall: " << m_IsFalling<< std::endl;
//	m_SideCollision = false;
}


void Player::movement(float _deltaTime)
{
	direction = { 0,0 };


	if (!isDead) {



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			direction.x = -1;
			sprite->setOrigin(sprite->getLocalBounds().width / 2, 0);
			sprite->setScale(-2.5, 2.5);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			direction.x = 1;
			sprite->setOrigin(0.f, 0.f);
			sprite->setScale(2.5, 2.5);

		}

		if (direction == sf::Vector2i(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setAnimation("IDLE");
		}
		else if (direction != sf::Vector2i(0, 0) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setAnimation("RUN");
			sprite->move(direction.x * playerSpeed, 0);
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isOnPlatform) {
			if (!m_AnimationTime) {
				m_AnimationTime = _deltaTime;
				setAnimation("ATTACK");
				for (auto& enemy : m_GameManager->getEnemies()) {
					if (sprite->getGlobalBounds().intersects(enemy->getSprite()->getGlobalBounds())) {

						AttackAnimation* attackAnimation = dynamic_cast<AttackAnimation*>(getAnimation());
						if (attackAnimation != nullptr) {
							//std::cout << attackAnimation->getHitboxes().size() << std::endl;
							for (int frame : attackAnimation->getHitboxes()) {
								//std::cout << frame << " " << attackAnimation->getCurrentFrame() << std::endl;
								if (frame == attackAnimation->getCurrentFrame()) {
									enemy->damageManager(m_outputDamage);
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
		if (m_CurrentAnimation->getCurrentFrame() != m_CurrentAnimation->getFrameCount() - 1) {
			setAnimation("DEATH");
		}
		else m_CurrentAnimation->pause();
	}
	//cout <<"animTime" << m_AnimationTime << endl;
}





void Player::experienceUpdate()
{
	vector<Enemy*> _enemies = m_GameManager->getEnemies();
	for (auto& enemy : _enemies) {
		if (enemy->isDead && !enemy->gaveExp) {
			m_Exp++;
			enemy->gaveExp = true;
		}
	}
	//cout << "EXP: " << m_Exp << endl;
}

void Player::loadAnimations()
{
	addAnimation(new Animation("RUN", "textures/player/Colour1/NoOutline/120x80_PNGSheets/Run3.png", { 32,38 }, 10));
	addAnimation(new Animation("DEATH", "textures/player/Colour1/NoOutline/120x80_PNGSheets/Death3.png", { 120,39 }, 10));
	addAnimation(new Animation("IDLE", "textures/player/Colour1/NoOutline/120x80_PNGSheets/Idle3.png", { 19,38 }, 10));
	addAnimation(new Animation("JUMP", "textures/player/Colour1/NoOutline/120x80_PNGSheets/Jump3.png", { 23,37 }, 3));
	addAnimation(new Animation("FALL", "textures/player/Colour1/NoOutline/120x80_PNGSheets/Fall3.png", { 27,37 }, 3));
	addAnimation((new AttackAnimation("ATTACK", "textures/player/Colour1/NoOutline/120x80_PNGSheets/Attack3.png", { 71,38 }, 4))->addHitbox({ 1,2 }));
}





void Player::update(float deltaTime, sf::RenderTarget* window)
{
	//PlatformDetection();
	experienceUpdate();
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


