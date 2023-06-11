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

	void viewupdate();
	void jumpControl(float);
	void movement(float);

	float getHP() {
		return m_HP;
	}

	void update(float, sf::RenderTarget*);
	void HealthBarManager();

private:

	void collider();
	void experienceUpdate();
	vector<HealthBar*> m_HealthPoints;
	vector<PlatRects*> platforms;
	void loadAnimations();
	Transform transform;

	bool bounced = false;
	bool m_IsJumping = false;

	float playerSpeed;

	unsigned int m_Exp;
	int m_CollisionTime = 10;
	friend class UpgradeMenu;
};

