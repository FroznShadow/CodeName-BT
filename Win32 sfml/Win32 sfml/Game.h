#ifndef GAME_H
#define GAME_H
#include "sfml.h"
#include <list>
#include "GameObject.h"

class Game
{
public:
	Game::Game(const sf::Vector2u& render_Dimensions);
	Game::~Game();
	void update(const sf::Time& elapsedTime);
	void draw(sf::RenderWindow& window);
private:
	typedef std::list<GameObject> GameObjectList;
	//sf::CircleShape _shape;
	sf::Texture _texture;
	GameObject _player;
	sf::Vector2u render_Dimensions;
	sf::Vector2f _playerVelocity;

	void create_Player();
	void updatePlayerVelocity(const float elapsedTime);
	void updatePlayerMovement(const float elapsedTime);
	static float clamp(const float value, const float min, const float max);
	static float sign(const float value);
};




#endif // !GAME_H
