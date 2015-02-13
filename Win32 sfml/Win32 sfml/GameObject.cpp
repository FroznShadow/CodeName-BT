#include "GameObject.h"

GameObject::GameObject() {}
GameObject::GameObject(const sf::Texture& texture)
	:_sprite(texture)
{
	
	updateOrigin();
}
//sf::CircleShape _shape(40.0f);
GameObject::~GameObject()
{
}
void GameObject::draw(sf::RenderWindow& window)
{

	window.draw(_sprite);
}
sf::Vector2f GameObject::position() const
{
	return _sprite.getPosition() + _origin;
}
void GameObject::setPosition(const sf::Vector2f& value)
{
	//_shape.setPosition(100.f, 100.f);
	_sprite.setPosition(value - _origin);
}

void GameObject::setTexture(const sf::Texture& value)
{
	_sprite.setTexture(value);
	updateOrigin();
}

void GameObject::setTextureRectangle(const sf::IntRect& value)
{
	_sprite.setTextureRect(value);
	_origin.x = 0.5f * value.width;
	_origin.y = 0.5f * value.height;
}
void GameObject::updateOrigin()
{
	_origin.x = 0.5f * _sprite.getTexture()->getSize().x;
	_origin.y = 0.5f * _sprite.getTexture()->getSize().y;
}