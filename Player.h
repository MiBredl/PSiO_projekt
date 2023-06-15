#pragma once
#include"libraries.h"
#include"NPC.h"
#include "Platform.h"
#include "Healthbar.h"
#include "UpgradeMenu.h"
#include "PlatRects.h"
class Player : public NPC
{
public:
	Player(GameManager*);
	~Player();
	void viewupdate();
	void jumpControl(float);
	void movement(float);
	
	float getHP(){
		return m_HP;
	}
	void SetPos(Vector2f _pos) {
		this->sprite->setPosition(_pos);
	}
	bool getIsAirborne() {
		return (m_IsJumping || m_IsFalling);
	}
	void update(float, sf::RenderTarget*);
	void HealthBarManager();
	void setSafety(bool _state){
		jumpSafe = _state;
	}
private:
	
	
	void experienceUpdate();
	vector<HealthBar*> m_HealthPoints;
	
	void loadAnimations();
	
	bool jumpSafe = false;
	bool bounced = false;
	bool m_IsJumping = false;
	
	float playerSpeed;

	unsigned int m_Exp;
	int m_CollisionTime = 10;
	friend class UpgradeMenu;
};

