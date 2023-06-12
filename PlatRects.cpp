#include "PlatRects.h"
#include "GameManager.h"
PlatRects::PlatRects(GameManager* _gameM,FloatRect _rect)
{
	m_GameManager = _gameM;
	fRect = _rect;
	
	
}

PlatRects::PlatRects(GameManager* _gameM, FloatRect _rect, bool _ismoving, bool _isdissapear)
{
	m_GameManager = _gameM;
	fRect = _rect;

	isMoving = _ismoving;
	isDissapear = _isdissapear;

	startingPos = _rect.left;
}

bool PlatRects::isAktiveP()
{
	if (isActive)
		return true;
	else
		return false;
}

bool PlatRects::isDeadPlatRects()
{
	if (isDissapear && isDead)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlatRects::updatePlatRects()
{
	if (isMoving)
	{
		if (movingR)
		{
			m_direction.x = 1;
		}
		else
		{
			m_direction.x = -1;
		}
		m_CurrentSpeed = m_direction.x * speed;
		fRect.left += m_CurrentSpeed;
		if (fRect.left >= startingPos + distance && movingR)
			movingR = false;
		if (fRect.left <= startingPos && !movingR)
			movingR = true;
	}

	if (isDissapear)
	{
		if (m_GameManager->getPlayer()->getSprite()->getGlobalBounds().intersects(fRect))
			disapearing = true;

		if (disapearing)
		{
			if (countdown > 0)
			{
				countdown--;
			}
			if (countdown == 0)
			{
				isDead = true;
			}
		}
	}
}
