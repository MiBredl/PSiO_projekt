#pragma once
#include"libraries.h"
#include"NPC.h"
#include "Platform.h"
#include "Healthbar.h"
class Player : public NPC
{
public:
	Player(GameManager*);
	
	void jumpControl(float);
	void movement(float);
	
	float getHP(){
		return m_HP;
	}
	void update(float, sf::RenderTarget*);
	void HealthBarManager();
private:
	
	void collider();
	
	vector<HealthBar*> m_HealthPoints;
	vector<Platform*> platforms;
	void loadAnimations();
	bool m_isOnGround=false;
	bool m_isOnPlatform=false;
	bool m_SideCollision = false;
	bool hit = false;
	
	bool m_IsFalling=false;
	bool m_IsJumping = false;
	float m_JumpVelocity=1;
	float playerSpeed;
	const float GRAVITY = 300.f;
	const float JUMP_VELOCITY=-350;
};

