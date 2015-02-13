#include "Game.h"
#include <cassert>
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

static const float PLAYER_ACCELERATION = 2000.0f;
static const float PLAYER_DECELERATION = 1000.0f;
static const float PLAYER_MAX_SPEED = 8000.0f;
Game::Game(const sf::Vector2u& renderDimensions)
	: render_Dimensions(renderDimensions)

{
	const bool result = _texture.loadFromFile("content/texture.png");
	assert(result);
	create_Player();
}

Game::~Game()
{
}
void Game::update(const sf::Time& elapsedTime)
{
	const float elapsedSeconds = elapsedTime.asSeconds();
	updatePlayerVelocity(elapsedSeconds);
	updatePlayerMovement(elapsedSeconds);
}
void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(50, 50, 50, 255));
	_player.draw(window);
}
void Game::updatePlayerVelocity(const float elapsedTime)
{
	const float acceleration = PLAYER_ACCELERATION * elapsedTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_playerVelocity.x -= acceleration;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_playerVelocity.x += acceleration;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_playerVelocity.y -= acceleration;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_playerVelocity.y += acceleration;

	_playerVelocity.x = clamp(_playerVelocity.x, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);
	_playerVelocity.y = clamp(_playerVelocity.y, -PLAYER_MAX_SPEED, PLAYER_MAX_SPEED);
}
void Game::updatePlayerMovement(const float elapsedTime)
{
	sf::Vector2f position = _player.position();
	position += _playerVelocity * elapsedTime;
	if (position.x < 0.0f || position.x > render_Dimensions.x)
		position.x = _player.position().x;

	if (position.y < 0.0f || position.y > render_Dimensions.y)
		position.y = _player.position().y;

	_player.setPosition(position);

	if (_playerVelocity.x != 0.0f)
		_playerVelocity.x += -sign(_playerVelocity.x) * PLAYER_DECELERATION * elapsedTime;
	if (_playerVelocity.y != 0.0f)
		_playerVelocity.y += -sign(_playerVelocity.y) * PLAYER_DECELERATION * elapsedTime;
}
void Game::create_Player()
{
	_player.setTexture(_texture);
	const sf::IntRect textureRectangle(0, 0, 100, 118);
	_player.setTextureRectangle(textureRectangle);
	const sf::Vector2f position(0.5f * render_Dimensions.x, 0.5f * render_Dimensions.y);
	_player.setPosition(position);
}
float Game::clamp(const float value, const float min, const float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

float Game::sign(const float value)
{
	return value / abs(value);
}
