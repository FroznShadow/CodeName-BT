#ifndef GAME_H
#define GAME_H
#include "sfml.h"
#include <list>
#include "GameObject.h"
#include "World.h"

class Game
{
public:

	Game::Game(const sf::Vector2u& render_Dimensions);
	Game::~Game();

	void M_update(const sf::Time& elapsedTime);
	void M_draw(sf::RenderWindow& window);
private:

	typedef std::list<GameObject> GameObjectList;
	sf::Texture P_texture;
	sf::Vector2u P_render_Dimensions;
	sf::Vector2f P_player_Velocity;

	GameObject P_player;
	GameObject Enemy;
	World map;	

	void M_create_World();
	void M_create_Player();
	void M_create_Enemy();
	void M_create_Area();
	void M_update_Player_Velocity(const float elapsedTime);
	void M_update_Player_Movement(const float elapsedTime);
	void M_update_Enemy_Movement(const float elapsedTime);
	bool M_checkCollision(GameObject P_player, GameObject Target);
	static float M_clamp(const float value, const float min, const float max);
	static float M_sign(const float value);
	
};

#endif // !GAME_H
