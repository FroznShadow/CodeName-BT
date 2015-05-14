#include "Explosion.h"

Explosion::Explosion()
{
}

Explosion::Explosion(const sf::Texture& texture)
	:P_sprite(texture)
{
	M_update_Origin();
}
Explosion::~Explosion()
{
}

void Explosion::M_draw(sf::RenderWindow& window)
{
	window.draw(P_sprite);
}

void Explosion::M_set_Position(const sf::Vector2f& value)
{
	P_sprite.setPosition(value - P_origin);
}
void Explosion::M_set_Texture(const sf::Texture& value)
{
	P_sprite.setTexture(value);
}
void Explosion::M_set_Texture_Rectangle(const sf::IntRect& value)
{
	P_sprite.setTextureRect(value);
	P_origin.x = 0.5f * value.width;
	P_origin.y = 0.5f * value.height;
	P_sprite.setOrigin(P_origin);
}

void Explosion::M_update_Origin()
{
	P_origin.x = 0.5f * P_sprite.getTexture()->getSize().x;
	P_origin.y = 0.5f * P_sprite.getTexture()->getSize().y;
}
void Explosion::M_Destroy()
{
	delete this;
}