#include "Platform.h"



Platform::Platform(GameManager*_gameMeneger,string _textname,Vector2f startingpos, Vector2f scale)
{
	m_GameManager = _gameMeneger;
	sprite = new Sprite;
	
	loadTextures();
	setTextures(_textname);
	
	
	sprite->setScale(scale);
	sprite->setPosition(startingpos);
}

void Platform::loadTextures()
{

	addTextures(new Textures("Grass", imagePath +  "sea.png", { 192,186,40,40 }));
	addTextures(new Textures("PlatL", imagePath + "objects.png", { 325,44,59,96 }));
	addTextures(new Textures("PlatM", imagePath + "objects.png", { 400,44,16,95 }));
	addTextures(new Textures("PlatR", imagePath + "objects.png", { 432,44,59,96 }));
	addTextures(new Textures("PlatSmall", imagePath + "objects.png", { 54,121,40,39 }));
	addTextures(new Textures("PlatBig", imagePath + "objects.png", { 41,24,98,76 }));
	addTextures(new Textures("PlatRockBig", imagePath + "objects.png", { 601,56,48,32 }));
	addTextures(new Textures("PlatRockSmall", imagePath + "objects.png", { 537,56,32,32 }));
}
