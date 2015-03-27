#ifndef WORLD_H
#define WORLD_H
#include "sfml.h"

class World : public sf::Drawable, public sf::Transformable
{
public:
	bool m_load(const std::string tileset = "lol", sf::Vector2u tileSize = {0,0}, const int* tiles = new int(4), unsigned int width = 3, unsigned int height = 3);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;
};

#endif // !WORLD_H
