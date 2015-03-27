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
	void M_draw(sf::RenderWindow& window);


	//------------//
	// Set Values //
	//------------//
	void M_set_Position(const sf::Vector2f& value);
	void M_set_Texture(const sf::Texture& value);
	void M_set_Texture_Rectangle(const sf::IntRect& value);
	void M_set_Rotation(float value);

	//------------//
	// Get Values //
	//------------//
	sf::Vector2f M_get_position() const;
	float M_get_Rotation() const;
	sf::FloatRect M_get_Bounding_Box() const;

	//  //
	void M_Rotation(float value);

protected:

	sf::Sprite P_sprite;
	sf::Vector2f P_origin;
	void M_update_Origin();

};


#endif // !GAMEOBJECT
