#ifndef GAME_H
#define GAME_H
#include "sfml.h"
#include <list>
#include "GameObject.h"
#include "World.h"

class Game
{
public:

	Game::Game(const sf::Vector2u& render_Dimensions );
	Game::~Game();

	void M_update(const sf::Time& elapsedTime, const sf::RenderWindow& window);
	void M_draw(sf::RenderWindow& window);
private:

	typedef std::list<GameObject> GameObjectList;
	sf::Texture  P_texture;
	sf::Vector2u P_render_Dimensions;
	sf::Vector2f P_player_Velocity;
	sf::Vector2f P_enemy_Velocity;
	bool is_Enemy_Active;

	GameObject P_player;
	GameObject *Enemy = new GameObject();
	World map;	

	void M_create_World();
	void M_create_Player();
	void M_create_Enemy(GameObject *Target);
	void M_create_Area();
	//void M_hit(); // NOT COMPLETED
	void M_update_Hit_Confirmation(GameObject *Target);
	void M_update_Player_Velocity(const float elapsedTime);
	void M_update_Enemy_Velocity(const float elapsedTime, GameObject *Target);
	void M_update_Player_Movement(const float elapsedTime);
	void M_update_Enemy_Movement(const float elapsedTime, GameObject *Target);
	void M_update_Player_Rotation(const sf::RenderWindow& window);
	bool M_checkCollision(GameObject P_player, GameObject *Target); 
	static float M_clamp(const float value, const float min, const float max);
	static float M_sign(const float value);
	void M_destroy_Enemy(GameObject *Target);
	
};

#endif // !GAME_H
