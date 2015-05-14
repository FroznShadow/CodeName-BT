#ifndef GAME_H
#define GAME_H
#include "sfml.h"
#include <list>
#include "GameObject.h"
#include "World.h"
#include "Explosion.h"
#include "TextureManager.h"
#include "AnimationHandler.h"
class Game
{
public:

	Game::Game(const sf::Vector2u& render_Dimensions );
	Game::~Game();

	void M_update(const sf::Time& elapsedTime, const sf::RenderWindow& window);
	void M_draw(sf::RenderWindow& window);
	TextureManager texmgr;
	AnimationHandler animH;
private:

	GameObject P_player;
	GameObject *Enemy = new GameObject();
	World map;	
	Explosion *explosion = new Explosion();

	//typedef std::list<GameObject> GameObjectList;
	sf::Texture  P_texture;
	sf::Texture P_explosion;
	sf::Vector2u P_render_Dimensions;
	sf::Vector2f P_player_Velocity;
	sf::Vector2f P_enemy_Velocity;
	sf::Vector2f P_stop_Velocity = sf::Vector2f(0.0f, 0.0f);
	sf::View view1;

	bool is_Enemy_Active;
	bool is_Explosion_Active = false;
	bool hitting;
	bool moving;
	float P_elapsedSeconds;
	//float timer = 0;
	float P_explosionTimer = 0;
	float explosiontime = 1;
	
	//----------------//
	// Building things//
	//----------------//
	void M_create_World();
	void M_create_Player();
	void M_create_Enemy(GameObject *Target);
	void M_create_Explosion(Explosion *explosion, GameObject *Target);
	void M_create_Area();
	void M_spawn_Enemy(float x_position, float y_position);
	void M_spawn_explosion(float x_position, float y_position);
	void loadTextures();
	void loadAnimations();

	//--------------//
	// Updating data//
	//--------------//
	void M_update_Hit_Confirmation(GameObject *Target);
	void M_update_Player_Velocity(const float elapsedTime);
	void M_update_Enemy_Velocity(const float elapsedTime, GameObject *Target);
	void M_update_Player_Movement(const float elapsedTime);
	void M_update_Enemy_Movement(const float elapsedTime, GameObject *Target);
	void M_update_Player_Rotation(const sf::RenderWindow& window);
	bool M_checkCollision(GameObject P_player, GameObject *Target); 
	static float M_clamp(const float value, const float min, const float max);
	static float M_sign(const float value);

	//------------------//
	// Destroying things//
	//------------------//
	void M_destroy_Enemy(GameObject *Target);
	void M_destroy_Explosion(Explosion *Target);

	
};

#endif // !GAME_H
