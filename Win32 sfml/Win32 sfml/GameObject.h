#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include "sfml.h"
#define _USE_MATH_DEFINES
#include <math.h>


class GameObject
{
public:
	GameObject();
	explicit GameObject(const sf::Texture& texture);
	~GameObject();
	void M_draw(sf::RenderWindow& window);
	void M_hit(float Damage);



	//------------//
	// Set Values //
	//------------//
	void M_set_Position(const sf::Vector2f& value);
	void M_set_Texture(const sf::Texture& value);
	void M_set_Texture_Rectangle(const sf::IntRect& value);
	void M_set_Rotation(float value);
	void M_set_Hit_Points(); // NOT READY
	

	//------------//
	// Get Values //
	//------------//
	sf::Vector2f M_get_position() const;
	float M_get_Rotation() const;
	sf::FloatRect M_get_Bounding_Box() const;
	float M_get_Hit_Points();
	
	//  //
	void M_Rotation(float value);
	void M_Destroy();
protected:

	sf::Sprite P_sprite;
	sf::Vector2f P_origin;
	float Hit_Points; // NOT READY
	void M_update_Origin();
	

};


#endif // !GAMEOBJECT
