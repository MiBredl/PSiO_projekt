#include "Ambient.h"
#include "GameManager.h"
void Ambient::loadTextures()
{
	addTextures(new Textures("Door", imagePath + "door.png", { 0,0,348,600 }));
	//Floor tiles
	addTextures(new Textures("FloorBush", imagePath + "objects.png", { 256,180,32,44 }));
	addTextures(new Textures("FloorRock", imagePath + "objects.png", { 144,183,32,41 }));
	addTextures(new Textures("FloorRockSmall", imagePath + "objects.png", { 480,186,16,22 }));
	addTextures(new Textures("FloorRockGrass", imagePath + "objects.png", { 144,105,32,55 }));
	addTextures(new Textures("FloorRockBush", imagePath + "objects.png", { 432,166,32,40 }));

	//ambients
	addTextures(new Textures("Tree", imagePath + "objects.png", { 191,45,123,115 }));
	addTextures(new Textures("FenceLeft", imagePath + "objects.png", { 584,188,41,30 }));
	addTextures(new Textures("FenceMiddle", imagePath + "objects.png", { 640,188,32,31 }));
	addTextures(new Textures("FenceRight", imagePath + "objects.png", { 688,188,41,30 }));
	//Background
	addTextures(new Textures("BackBlack", imagePath + "objects.png", { 866,215,40,40 }));
	addTextures(new Textures("BackBush", imagePath + "objects.png", { 144,240,32,32 }));
	addTextures(new Textures("BackRock", imagePath + "objects.png", { 240,240,64,32 }));
	addTextures(new Textures("BackRockW", imagePath + "objects.png", { 192,253,32,40 }));
}

void Ambient::loadBackgroundTextures()
{
	addTextures(new Textures("cloudsFront", imagePath + "background/clouds_front.png", { 0,0,1920,216 }));
	addTextures(new Textures("cloudsMidde", imagePath + "background/clouds_mid.png", { 0,0,1920,216 }));
	addTextures(new Textures("MoutainsFar", imagePath + "background/far_mountains.png", { 0,0,1920,216 }));
	addTextures(new Textures("MoutainsClose", imagePath + "background/grassy_mountains.png", { 0,0,1920,216 }));
	addTextures(new Textures("Hill", imagePath + "background/hill.png", { 0,0,1920,216 }));
	addTextures(new Textures("Sky", imagePath + "background/sky.png", { 0,0,1920,216 }));
}

Ambient::Ambient(GameManager* _gameMeneger, string _textname, Vector2f startingpos, Vector2f scale)
{
	m_GameManager = _gameMeneger;
	sprite = new Sprite;

	loadTextures();
	setTextures(_textname);


	sprite->setScale(scale);
	sprite->setPosition(startingpos);
}

Ambient::Ambient(GameManager* _gameManager, string _textname, Vector2f start_pos, Vector2f scale,int mult, float _speed)
{
	m_GameManager = _gameManager;
	sprite = new Sprite;
	speed = _speed;
	posY = start_pos.y;
	loadBackgroundTextures();
	setTextures(_textname);

	sprite->setScale(scale);
	sprite->setPosition(start_pos);
	sprite->setOrigin(sprite->getLocalBounds().width / mult, sprite->getLocalBounds().height / 2);

}

Ambient::Ambient(GameManager* _gameManager, string _textname , Vector2f start_pos,Vector2f scale, bool _isDoor)
{
	m_GameManager = _gameManager;
	sprite = new Sprite;
	loadTextures();
	setTextures(_textname);
	isDoor = _isDoor;

	sprite->setScale(scale);
	sprite->setPosition(start_pos);

}

Ambient::~Ambient()
{
	for (auto& texture : m_Texture) {
		delete texture.second;
	}
	m_Texture.clear();
}

void Ambient::updateParalax()
{
	float posX = m_GameManager->getPlayer()->getSprite()->getPosition().x;

	sprite->setPosition(posX * speed, posY + sprite->getLocalBounds().height / 2);
}

void Ambient::updateAmbients()
{
}

void Ambient::updateDoor()
{
	if (isDoor && sprite->getGlobalBounds().intersects(m_GameManager->getPlayer()->getSprite()->getGlobalBounds()))
	{
		//sprite->setColor(Color::Red);
		if(m_GameManager->getCurrentWorld()==1)
		{
			m_GameManager->setCurrentWorld(2);
			m_GameManager->setRoomChange(true);
			m_GameManager->getPlayer()->SetPos({ 800, 0 });
			
			m_GameManager->getMainMenu()->overrideChosen(GAME_ENUMS::GAMESTATE::RESTART);
			
		}
		
	}
	else if (isDoor)
	{
		//sprite->setColor(Color::Blue);
	}
	
}
