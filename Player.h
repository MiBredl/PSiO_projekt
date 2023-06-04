#pragma once
#include"libraries.h"
#include"NPC.h"
#include "Platform.h"
#include "Healthbar.h"
class Player : public NPC
{
public:
	Player(GameManager*);
	
	void viewupdate();
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
	
	bool m_IsJumping = false;
	
	float playerSpeed;
	
	
};

