#include "GameObject.h"

GameObject::GameObject() {}
GameObject::GameObject(const sf::Texture& texture)
	:P_sprite(texture)
{	
	M_update_Origin();
}
GameObject::~GameObject()
{
}
void GameObject::M_draw(sf::RenderWindow& window)
{
	window.draw(P_sprite);
}

//------------//
// Set Values //
//------------//
void GameObject::M_set_Position(const sf::Vector2f& value)
{
	P_sprite.setPosition(value - P_origin);
}
void GameObject::M_set_Texture(const sf::Texture& value)
{
	P_sprite.setTexture(value);
	M_update_Origin();
}
void GameObject::M_set_Texture_Rectangle(const sf::IntRect& value)
{
	P_sprite.setTextureRect(value);
	P_origin.x = 0.5f * value.width;
	P_origin.y = 0.5f * value.height;
}
void GameObject::M_set_Rotation(float value)
{
	P_sprite.setRotation(value);
}

//------------//
// Get Values //
//------------//
sf::Vector2f GameObject::M_get_position() const
{
	return P_sprite.getPosition() + P_origin;
}
float GameObject::M_get_Rotation() const
{
	return P_sprite.getRotation();
}
sf::FloatRect GameObject::M_get_Bounding_Box() const
{
	return P_sprite.getGlobalBounds();
}

void GameObject::M_update_Origin()
{
	P_origin.x = 0.5f * P_sprite.getTexture()->getSize().x;
	P_origin.y = 0.5f * P_sprite.getTexture()->getSize().y;
}
void GameObject::M_Rotation(float value)
{
	P_sprite.rotate(value);
}

