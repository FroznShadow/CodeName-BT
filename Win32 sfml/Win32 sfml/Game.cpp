#include "Game.h"
#include <cassert>
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

static const float P_PLAYER_ACCELERATION = 2000.0f;
static const float P_PLAYER_DECELERATION = 1500.0f;
static const float P_PLAYER_MAX_SPEED = 8000.0f;
Game::Game(const sf::Vector2u& renderDimensions)
	: P_render_Dimensions(renderDimensions)

{
	const bool result = P_texture.loadFromFile("content/texture.png");
	assert(result);

	M_create_Player();
	M_create_Enemy();
	M_create_World();

}

Game::~Game()
{
}
void Game::M_update(const sf::Time& elapsedTime)
{
	const float P_elapsedSeconds = elapsedTime.asSeconds();
	M_update_Player_Velocity(P_elapsedSeconds);
	M_update_Player_Movement(P_elapsedSeconds);
	M_update_Enemy_Movement(P_elapsedSeconds);
	M_checkCollision(P_player, Enemy);
}
void Game::M_draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(50, 50, 50, 255));
	window.draw(map);
	P_player.M_draw(window);
	Enemy.M_draw(window);
	
}
void Game::M_update_Player_Velocity(const float elapsedTime)
{
	const float P_acceleration = P_PLAYER_ACCELERATION * elapsedTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		P_player_Velocity.x -= P_acceleration;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		P_player_Velocity.x += P_acceleration;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		P_player_Velocity.y -= P_acceleration;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		P_player_Velocity.y += P_acceleration;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		

	P_player_Velocity.x = M_clamp(P_player_Velocity.x, -P_PLAYER_MAX_SPEED, P_PLAYER_MAX_SPEED);
	P_player_Velocity.y = M_clamp(P_player_Velocity.y, -P_PLAYER_MAX_SPEED, P_PLAYER_MAX_SPEED);
}
void Game::M_update_Player_Movement(const float elapsedTime)
{
	sf::Vector2f position = P_player.M_get_position();
	position += P_player_Velocity * elapsedTime;
	if (position.x < 0.0f || position.x > P_render_Dimensions.x)
		position.x = P_player.M_get_position().x;

	if (position.y < 0.0f || position.y > P_render_Dimensions.y)
		position.y = P_player.M_get_position().y;

	P_player.M_set_Position(position);

	if (P_player_Velocity.x != 0.0f)
		P_player_Velocity.x += -M_sign(P_player_Velocity.x) * P_PLAYER_DECELERATION * elapsedTime;
	if (P_player_Velocity.y != 0.0f)
		P_player_Velocity.y += -M_sign(P_player_Velocity.y) * P_PLAYER_DECELERATION * elapsedTime;
}
void Game::M_update_Enemy_Movement(const float elapsedTime)
{
	sf::Vector2f position = Enemy.M_get_position();
	Enemy.M_Rotation(1);
}
void Game::M_create_Player()
{
	P_player.M_set_Texture(P_texture);
	const sf::IntRect textureRectangle(0, 0, 100, 118);
	P_player.M_set_Texture_Rectangle(textureRectangle);
	const sf::Vector2f position(0.5f * P_render_Dimensions.x, 0.5f * P_render_Dimensions.y);
	P_player.M_set_Position(position);

}
float Game::M_clamp(const float value, const float min, const float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

float Game::M_sign(const float value)
{
	return value / abs(value);
}
void Game::M_create_Enemy()
{

	Enemy.M_set_Texture(P_texture);
	const sf::IntRect texture_Rectangle(0, 0, 100, 118);
	Enemy.M_set_Texture_Rectangle(texture_Rectangle);
	const sf::Vector2f position(0.2f * P_render_Dimensions.x, 0.6f * P_render_Dimensions.y);
	Enemy.M_set_Position(position);
}

void Game::M_create_World()
{
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2,
		1, 1, 1, 3, 3, 3, 2, 2, 3, 3, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

	};
	map.m_load("Tileset.png", sf::Vector2u(200, 200), level, 16, 6);
		
		
}
bool Game::M_checkCollision(GameObject P_player, GameObject Target)
{
	sf::FloatRect PlayerBoundingBox = P_player.M_get_Bounding_Box();
	sf::FloatRect TargetBoundingBox = Target.M_get_Bounding_Box();
	if (PlayerBoundingBox.intersects(TargetBoundingBox))
	{ 
		std::cout << "Collision!" << std::endl;
		return true;
	}
	return false;
}