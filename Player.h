#pragma once
#include"libraries.h"
#include"NPC.h"

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
	
private:
	
	
	void loadAnimations();
	//enum action { RUN, JUMP, IDLE };
	//int currentAction=2;
	bool m_IsFalling=false;
	bool m_IsJumping = false;
	float m_JumpVelocity=1;
	float playerSpeed;
	const float GRAVITY = 300.f;
	const float JUMP_VELOCITY=-300;
};

