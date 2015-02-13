#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include "sfml.h"

class GameObject
{
public:
	GameObject();
	explicit GameObject(const sf::Texture& texture);
	~GameObject();
	void draw(sf::RenderWindow& window);
	sf::Vector2f position() const;

	void setPosition(const sf::Vector2f& value);
	void setTexture(const sf::Texture& value);

	void setTextureRectangle(const sf::IntRect& value);
protected:

	sf::Sprite _sprite;
	sf::Vector2f _origin;
	void updateOrigin();

};


#endif // !GAMEOBJECT
