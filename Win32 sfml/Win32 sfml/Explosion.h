#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "sfml.h"

class Explosion
{
public:
	Explosion();
	explicit Explosion(const sf::Texture& texture);
	~Explosion();


	void M_set_Position(const sf::Vector2f& value);
	void M_set_Texture(const sf::Texture& value);
	void M_set_Texture_Rectangle(const sf::IntRect& value);

	sf::Vector2f M_get_position() const;
	void M_draw(sf::RenderWindow& window);
	void M_update_Origin();
	void M_Destroy();
protected:
	sf::Sprite P_sprite;
	sf::Vector2f P_origin;
};

#endif





