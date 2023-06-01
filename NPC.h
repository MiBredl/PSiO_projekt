#pragma once
#include"libraries.h"
#include"AttackAnimation.h"


class NPC
{
protected:
	class GameManager* m_GameManager;
	Animation* m_CurrentAnimation;
	sf::Sprite* sprite;
	std::map<std::string, Animation*> m_Animations;
	sf::Clock clock;
	sf::Vector2i direction = { 0,0 };	
	float m_HP;
	float m_TotalTime;
	bool isFirstAttack = true;
	bool isAttacking = false;
	
	int m_AnimationTime,iFrameTime;
public:

	

	bool isDead = false;
	virtual void movement(float) = 0;
	virtual void update(float, sf::RenderTarget*) = 0;


	void render(sf::RenderTarget* window,float);
	
	void setAnimation(std::string);
	void addAnimation( Animation*);
	

	GameManager* getGameManager() {
		return m_GameManager;
	}
	Animation* getAnimation(){
		return m_CurrentAnimation;
	}
	sf::Sprite* getSprite() {
		return sprite; 
	}
	void damageManager(float);


};

