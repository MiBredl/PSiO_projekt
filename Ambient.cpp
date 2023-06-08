#include "Ambient.h"
#include "GameManager.h"
void Ambient::loadTextures()
{
	//Floor tiles
	addTextures(new Textures("FloorBush", imagePath + "objects.png", { 256,180,32,44 }));
	addTextures(new Textures("FloorRock", imagePath + "objects.png", { 144,183,32,41 }));
	addTextures(new Textures("FloorRockSmall", imagePath + "objects.png", { 480,186,16,22 }));
	addTextures(new Textures("FloorRockGrass", imagePath + "objects.png", { 144,105,32,55 }));
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

	addTextures(new Textures("cloudsFront", imagePath + "background1/clouds_front.png", { 0,0,1920,216 }));
	addTextures(new Textures("cloudsMidde", imagePath + "background1/clouds_mid.png", { 0,0,1920,216 }));
	addTextures(new Textures("MoutainsFar", imagePath + "background1/far_mountains.png", { 0,0,1920,216 }));
	addTextures(new Textures("MoutainsClose", imagePath + "background1/grassy_mountains.png", { 0,0,1920,216 }));
	addTextures(new Textures("Hill", imagePath + "background1/hill.png", { 0,0,1920,216 }));
	addTextures(new Textures("Sky", imagePath + "background1/sky.png", { 0,0,1920,216 }));

	//addTextures(new Textures("Sky2", imagePath + "background2/1.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Sky2", imagePath + "background2/2.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Tree1", imagePath + "background2/3.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Tree2", imagePath + "background2/4.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Tree3", imagePath + "background2/5.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Fog6", imagePath + "background2/6.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Grasy", imagePath + "background2/7.png", { 0,0,1920,1080 }));
	//addTextures(new Textures("Trees", imagePath + "background2/8.png", { 0,0,1920,1080 }));

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

Ambient::Ambient(GameManager* _gameManager, string _textname, Vector2f start_pos, Vector2f scale, int przesuniecie, float _speed)
{
	m_GameManager = _gameManager;
	sprite = new Sprite;
	speed = _speed;
	posY = start_pos.y;
	//posX = start_pos.x;
	loadTextures();
	setTextures(_textname);

	sprite->setScale(scale);
	sprite->setPosition(start_pos);
	sprite->setOrigin(sprite->getLocalBounds().width / przesuniecie, sprite->getLocalBounds().height / 2);

}

void Ambient::updateParalax()
{
	float posX = m_GameManager->getPlayer()->getSprite()->getPosition().x;

	sprite->setPosition(posX * speed, posY + sprite->getLocalBounds().height / 2);
}

void Ambient::updateAmbients()
{
}
