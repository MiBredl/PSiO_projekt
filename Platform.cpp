#include "Platform.h"
#include "GameManager.h"


Platform::Platform(GameManager*_gameMeneger,string _textname,Vector2f startingpos, Vector2f scale)
{
	m_GameManager = _gameMeneger;
	sprite = new Sprite;
	
	loadTextures();
	setTextures(_textname);
	
	
	sprite->setScale(scale);
	sprite->setPosition(startingpos);
}

Platform::Platform(GameManager* _gameMeneger, string _textname, Vector2f startingpos, Vector2f scale,bool is_moving,bool is_dissapear)
{
	m_GameManager = _gameMeneger;
	sprite = new Sprite;

	loadTextures();
	setTextures(_textname);
	startingPos = startingpos.x;
	isMoving = is_moving;
	isDissapear = is_dissapear;
	sprite->setScale(scale);
	sprite->setPosition(startingpos);


}

void Platform::platformUpdate()
{
	if (this != nullptr)
	{
		if (isMoving)
		{
			if (movingR)
			{
				sprite->move(speed, 0);
			}
			if (!movingR)
			{
				sprite->move(-speed, 0);
			}

		if (sprite->getPosition().x >= startingPos + distance && movingR)
			movingR = false;
		if (sprite->getPosition().x <= startingPos && !movingR)
			movingR = true;
		}
	
	
		if (isDissapear)
		{
			if (m_GameManager->getPlayer()->getSprite()->getGlobalBounds().intersects(sprite->getGlobalBounds()))
				disapearing = true;

			if (disapearing)
			{
			
			
				if (countdown > 0)
				{
					countdown--;
					if(alpha>=50) alpha--;
					sprite->setColor(Color(110, 75, 20, alpha));
				}
				if (countdown == 0)
				{
					isDead = true;
				}
			}
		}
	}
}

bool Platform::isDeadPlat()
{
	if (isDissapear && isDead)
	{
		return true;
	}
	else
		return false;
}

void Platform::loadTextures()
{

	addTextures(new Textures("Grass", imagePath + "objects.png", { 192,186,40,40 }));
	addTextures(new Textures("PlatL", imagePath + "objects.png", { 325,44,59,96 }));
	addTextures(new Textures("PlatM", imagePath + "objects.png", { 400,44,16,95 }));
	addTextures(new Textures("PlatR", imagePath + "objects.png", { 432,44,59,96 }));
	addTextures(new Textures("PlatSmall", imagePath + "objects.png", { 54,121,40,39 }));
	addTextures(new Textures("PlatBig", imagePath + "objects.png", { 41,24,98,76 }));
	addTextures(new Textures("PlatRockBig", imagePath + "objects.png", { 601,56,48,32 }));
	addTextures(new Textures("PlatRockSmall", imagePath + "objects.png", { 537,56,32,32 }));
	addTextures(new Textures("CliffRight", imagePath + "objects.png", {  36,186,40,40  }));
	addTextures(new Textures("CliffRockRight", imagePath + "objects.png", { 36,226,40,40 }));
	addTextures(new Textures("CliffLeft", imagePath + "objects.png", { 517,186,40,40 }));
	addTextures(new Textures("CliffRockLeft", imagePath + "objects.png", { 517,225,40,40 }));
}
