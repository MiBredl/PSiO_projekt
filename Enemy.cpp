#include "Enemy.h"
#include "GameManager.h"





Enemy::Enemy(int type, GameManager* _gameManager, Vector2f _startpos):type(type), gaveExp(false)
{
	iFrameTime = 0;
	m_outputDamage = type;
	m_AnimationTime = 0;
	m_GameManager = _gameManager;
	m_TotalTime = 0.4;
	m_HP = type;
	sprite = new sf::Sprite;

	loadAnimations();
	//cout << "NEW ENEMY\n";
	cout << "Enemy\n";
	m_Bar = new EnemyBar(_startpos, {50.f,10.f});
	setAnimation("MOVE");

	sprite->setScale(1.5, 1.5);
	sprite->setPosition(_startpos);
	
}

Enemy::~Enemy()
{
	delete sprite;
	for (auto& pair : m_Animations) {
		delete pair.second;
	}
	m_Animations.clear();
	if(m_Bar!=nullptr) delete m_Bar;
}

void Enemy::movement(float _deltaTime)
{

	if (!isDead) {
		float HP_ratio = m_HP / type;
		m_Bar->update({ sprite->getGlobalBounds().left,sprite->getGlobalBounds().top-10 }, HP_ratio);
		sf::Sprite* _PlayerSprite = m_GameManager->getPlayer()->getSprite();
		
		
		if (!m_GameManager->getPlayer()->isDead) {

			
			if (onActive) {
				if (_PlayerSprite->getGlobalBounds().left + _PlayerSprite->getGlobalBounds().width <= this->sprite->getGlobalBounds().left) {
					direction.x = -1;
					this->sprite->setOrigin(sprite->getLocalBounds().width / 2, 0);
					this->sprite->setScale(-1.5, 1.5);
				}
				if (_PlayerSprite->getGlobalBounds().left >= this->sprite->getGlobalBounds().left + this->sprite->getGlobalBounds().width) {
					direction.x = 1;
					this->sprite->setOrigin(0.f, 0.f);
					this->sprite->setScale(1.5, 1.5);
				}

				if (sprite->getGlobalBounds().intersects(_PlayerSprite->getGlobalBounds())) {

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
			else {
				setAnimation("IDLE");
				direction.x = 0;
			}
			
			
		}
		else setAnimation("IDLE");
		this->sprite->move(direction.x * type,0 );
	}
	else {
		if (m_CurrentAnimation->getCurrentFrame() != m_CurrentAnimation->getFrameCount()-1) {
			setAnimation("DEATH");
			
		}
		else m_CurrentAnimation->pause();
	}
	//cout << direction.y << "ENEMY DIR" << endl;
}

void Enemy::update(float deltaTime, sf::RenderTarget* window)
{
	

	
	movement(deltaTime);
	fallControll(deltaTime);
	if(!isDead)m_Bar->render(window);
}

void Enemy::fallControll(float _deltaTime)
{
	vector<PlatRects*> platforms = m_GameManager->getPlatRects();
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
		FloatRect _PlatformHitbox = platform->getRect();
		
		if (_EnemyBounds.intersects(_PlatformHitbox)) {
			
			
			if (_EnemyBounds.top + _EnemyBounds.height >= _PlatformHitbox.top
				&& _EnemyBounds.top <= _PlatformHitbox.top + _PlatformHitbox.height-30) {
				m_isOnPlatform = true;
				sprite->setPosition(sprite->getPosition().x, platform->getRect().top - _EnemyBounds.height);
				m_IsFalling = false;
				if (platform->isActive) onActive = true;
				else onActive = false;
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




