#include "AttackAnimation.h"


AttackAnimation* AttackAnimation::addHitbox(std::vector<int> _hitboxFrames)
{
	  m_HitboxFrames= _hitboxFrames;
	  return this;
}
