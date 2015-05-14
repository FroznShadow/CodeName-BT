#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "sfml.h"
#include <string>
#include <map>

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager(){}

	void loadTexture(const std::string& name, const std::string &filename);

	sf::Texture& getRef(const std::string& texture);
private:
	std::map<std::string, sf::Texture>textures;
};


#endif // !TEXTUREMANAGER.H
