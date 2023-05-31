#include "Ambient.h"

void Ambient::loadTextures()
{
	//Floor tiles
	addTextures(new Textures("FloorBush", imagePath + "objects.png", { 256,180,32,44 }));
	addTextures(new Textures("FloorRock", imagePath + "objects.png", { 144,183,32,41 }));
	addTextures(new Textures("FloorRockSmall", imagePath + "objects.png", { 480,186,16,22 }));
	addTextures(new Textures("FloorRockGrass", imagePath + "objects.png", { 144,105,32,55 }));
	addTextures(new Textures("FloorRockBush", imagePath + "objects.png", { 432,166,32,40 }));
	addTextures(new Textures("FloorMoss", imagePath + "objects.png", { 464,243,32,45 }));
	//ambients
	addTextures(new Textures("Tree", imagePath + "objects.png", { 191,45,123,115 }));
	addTextures(new Textures("FenceLeft", imagePath + "objects.png", { 584,188,41,30 }));
	addTextures(new Textures("FenceMiddle", imagePath + "objects.png", { 640,188,32,31 }));
	addTextures(new Textures("FenceRight", imagePath + "objects.png", { 688,188,41,30 }));
	//Background
	addTextures(new Textures("FloorBlack", imagePath + "objects.png", { 875,78,40,40 }));

}

Ambient::Ambient(GameManager*, string, Vector2f, Vector2f)
{
}
