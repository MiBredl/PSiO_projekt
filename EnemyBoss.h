#pragma once
#include"Enemy.h"
#include"Projectile.h"
#include"libraries.h"
class EnemyBar;
class EnemyBoss :public Enemy
{
private:
	enum PHASES{STANDARD,STATIONARY};
	int m_AttackTime;
	int m_ShotCooldown;
	int m_StationaryShotCooldown;
	int m_BossPhase;
	int invincibilityTimer;
	Vector2i m_direction;
	vector<Projectile*> m_Projectiles;
	
	bool stateChanged = false;
	
	void PhaseUpdate();
	void fightControl();
	void fireballControll();
	void stationaryFireballControll();
	
public:
	//bool ivincibilityReset = true;
	EnemyBoss(int,GameManager*, Vector2f);
	//~EnemyBoss();
	void loadAnimations();
	void update(float);
	void updateHPBar();
	void movement();
	void invincibilityControll();
	void hitMovement();
	FloatRect getGlobalBound() {
		return sprite->getGlobalBounds();
	}
	bool getIsInvincible() {
		return isInvincible;
	}
	void setIsInvincible(bool _status) {
		isInvincible = _status;
	}
};

