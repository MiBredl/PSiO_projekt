#pragma once
#include"libraries.h"
#include"Animation.h"
class AttackAnimation :public Animation
{
public:
	AttackAnimation(std::string _name,std::string _filename, sf::Vector2i _frameSize, int _frameCount) :Animation(_name,_filename, _frameSize, _frameCount) {}
	AttackAnimation* addHitbox(std::vector<int>);
	std::vector<int> getHitboxes() {
		return m_HitboxFrames;
	}
private:
	std::vector<int> m_HitboxFrames;
};

