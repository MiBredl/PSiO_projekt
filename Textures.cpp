#include "Textures.h"
#include <iostream>
Textures::Textures(string _name,string directory, IntRect rect):
	name(_name),
	TexureRect(rect)
{

	texture = new Texture;
	
	if (!texture->loadFromFile(directory));
	cout << "xD\n";

}
