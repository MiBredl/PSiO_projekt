#include "PlatRects.h"
#include "GameManager.h"
PlatRects::PlatRects(GameManager* _gameM,FloatRect _rect)
{
	m_GameManager = _gameM;
	fRect = _rect;

	
}

bool PlatRects::isAktiveP()
{
	if (m_GameManager->getPlayer()->getSprite()->getGlobalBounds().intersects(fRect))
	{
		isActive = true;
	}
	else
		isActive = false;

	if (isActive)
		return true;
	else
		return false;
}
