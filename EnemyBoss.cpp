#include "EnemyBoss.h"
#include "GameManager.h"



EnemyBoss::EnemyBoss(int type, GameManager* _gameManager, Vector2f _position)
	:Enemy(GAME_ENUMS::ENEMY_TYPE::BOSS, _gameManager, _position)
	, m_AttackTime(30)
	, m_BossPhase(STANDARD)
	, m_ShotCooldown(50)
	, m_StationaryShotCooldown(5)
	, invincibilityTimer(200)
{
	m_HP = 5;
	sprite = new Sprite;
	isInvincible = false;
	m_Bar = new EnemyBar({ WINDOW_WIDTH / 2,10 }, {400.f,20.f});
	sprite->setPosition(_position);
	sprite->setScale(2.5,2.5);
	loadAnimations();
	setAnimation("IDLE");
}

void EnemyBoss::loadAnimations()
{
	Enemy::loadAnimations();
	switch (type)
	{
	case GAME_ENUMS::ENEMY_TYPE::BOSS:
		addAnimation(new Animation("IDLE", "textures/Monsters_Creatures_Fantasy/Boss/Idle3.png", { 35,58 }, 8));
		addAnimation(new Animation("DEATH", "textures/Monsters_Creatures_Fantasy/Boss/Death3.png", { 52,58 }, 5));
	}
}

void EnemyBoss::update(float deltaTime)
{
	
	PhaseUpdate();
	fallControll(deltaTime);
	fightControl();
	updateHPBar();
	m_Bar->render(m_GameManager->getWindow());
	
	for (auto& projecitle : m_Projectiles) {
		projecitle->render(m_GameManager->getWindow());
		projecitle->update();
	}
	
}

void EnemyBoss::movement()
{
	m_direction.y = 0;
	Player* _player = m_GameManager->getPlayer();
	Sprite* _playerSprite = _player->getSprite();
	if (!onActive) {
		if (m_AttackTime == 0 && !_player->getIsAirborne()) {
			m_AttackTime = 180;
			
			sprite->setPosition(_playerSprite->getPosition());
		}
		if (m_AttackTime > 0) m_AttackTime--;
		
		//else sprite->setColor(Color::White);
	}
	else {
		Vector2f _playerPos = _playerSprite->getPosition();
		if (_playerPos.x >= sprite->getPosition().x) m_direction.x = 1;
		else m_direction.x = -1;
	}
}
void EnemyBoss::invincibilityControll()
{
	if (m_BossPhase == PHASES::STATIONARY) {
		if (invincibilityTimer<=100 ) {
			isInvincible = false;
		}
		else {
			isInvincible = true;
			
		}
		if (isHit) { 
			
			isInvincible = true;
			invincibilityTimer = 500;
		}
		if (!invincibilityTimer) invincibilityTimer = 500;
		invincibilityTimer--;
	}

}
void EnemyBoss::updateHPBar()
{
	Vector2i pixelPos = { WINDOW_WIDTH / 2 -static_cast<int>(m_Bar->getGlobalBound().width/2),20 };
	Vector2f worldPos = m_GameManager->getWindow()->mapPixelToCoords(pixelPos);
	float _ratio = m_HP / 5;
	m_Bar->update(worldPos, _ratio);
}
void EnemyBoss::hitMovement()
{
	vector<PlatRects*> platforms = m_GameManager->getPlatRects();
	if (m_BossPhase == PHASES::STATIONARY) {
		if (isHit) {
			isHit = false;
			for (PlatRects* platform : platforms) {
				if (!platform->isActive) {
					sprite->setPosition(platform->getRect().left, platform->getRect().top - sprite->getGlobalBounds().height);
					break;
				}
			}
		}
	}
}
void EnemyBoss::PhaseUpdate()
{
	if (m_HP <= 3) { 
		m_BossPhase = STATIONARY; }
}

void EnemyBoss::fightControl()
{
	Player* _player = m_GameManager->getPlayer();
	if (!_player->isDead) {
		if (!isDead) {
			switch (m_BossPhase)
			{
			case PHASES::STANDARD:
				movement();
				fireballControll();
				break;

			case PHASES::STATIONARY:
				stationaryFireballControll();
				invincibilityControll();
				hitMovement();
				break;
			}
		}
		else {
			if (m_CurrentAnimation->getCurrentFrame() == m_CurrentAnimation->getFrameCount() - 1) {
				
				m_CurrentAnimation->pause();
			}
			else setAnimation("DEATH");
			m_GameManager->setGameState(GAME_ENUMS::GAMESTATE::VICTORY);
		}
	}
}

void EnemyBoss::fireballControll()
{
	Player* _player = m_GameManager->getPlayer();
	vector<Projectile*> toDelete;

	if (onActive) {

		if (!m_ShotCooldown) {
			m_ShotCooldown = 30;
			Vector2f spritePos = { sprite->getGlobalBounds().left + sprite->getGlobalBounds().width / 2,sprite->getGlobalBounds().top + sprite->getGlobalBounds().height / 2 };
			m_Projectiles.push_back(new Projectile(spritePos, m_direction));
			
		}
		else m_ShotCooldown--;
	}
	

	for (auto& projectile : m_Projectiles) {
		if (projectile->getBounds().intersects(_player->getSprite()->getGlobalBounds())) _player->damageManager(1);
		if (projectile->getBounds().intersects(_player->getSprite()->getGlobalBounds())
			|| projectile->getBounds().left < projectile->getStartingPos() - 400
			|| projectile->getBounds().left + projectile->getBounds().width > projectile->getStartingPos() + 400) {
			toDelete.push_back(projectile);
			
		}
	}

	for (auto projectile : toDelete) {
		delete projectile;
		m_Projectiles.erase(std::remove(m_Projectiles.begin(), m_Projectiles.end(), projectile), m_Projectiles.end());
	}
	//cout<<"PROJECTILES: "<<m_Projectiles.size()<<endl;
}

void EnemyBoss::stationaryFireballControll()
{
	Player* _player = m_GameManager->getPlayer();
	vector<PlatRects*> platforms = m_GameManager->getPlatRects();
	std::random_device rd;
	std::mt19937 gen(rd());
	m_direction = { 0,1 };
	int YPOS_MAX =  - 100;
	int YPOS_MIN =  - 20;
	int XPOS_MIN = 0;
	int XPOS_MAX = WINDOW_WIDTH;

	std::uniform_int_distribution<int> dist1(YPOS_MAX, YPOS_MIN);
	int YPOS = dist1(gen);

	std::uniform_int_distribution<int> dist2(XPOS_MIN, XPOS_MAX);
	int XPOS = dist2(gen);
	vector<Projectile*> projectilesToDelete;
	if (!m_StationaryShotCooldown) {
		m_StationaryShotCooldown = 15;
		m_Projectiles.push_back(new Projectile({ XPOS * 1.f,YPOS * 1.f }, m_direction));
		Sprite* lastProjectile = m_Projectiles.back()->getSprite();
		lastProjectile->setOrigin(lastProjectile->getLocalBounds().width/2,lastProjectile->getLocalBounds().height/2);
		lastProjectile->rotate(90);
	}
	else m_StationaryShotCooldown--;
	for (auto& projectile : m_Projectiles) {
		bool collidedWithPlatform = false;
		if (projectile->getBounds().intersects(_player->getSprite()->getGlobalBounds())) _player->damageManager(1);
		if (projectile->getBounds().intersects(_player->getSprite()->getGlobalBounds())
			|| projectile->getBounds().top > WINDOW_HEIGHT) {
			projectilesToDelete.push_back(projectile);
			continue;
		}

		for (auto& platform : platforms) {
			if (projectile->getBounds().intersects(platform->getRect())) {
				collidedWithPlatform = true;
				projectilesToDelete.push_back(projectile);
				break;
			}
		}

		if (collidedWithPlatform)
			continue;

		
	}

	for (auto projectile : projectilesToDelete) {
		m_Projectiles.erase(std::remove(m_Projectiles.begin(), m_Projectiles.end(), projectile), m_Projectiles.end());
		delete projectile;
	}

	
}
